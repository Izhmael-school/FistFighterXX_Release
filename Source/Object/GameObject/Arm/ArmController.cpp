#include "ArmController.h"
#include "../../../Utility/InputUtility.h"
#include "../../../Utility/TimeUtility.h"
#include "../../../CommonModule.h"
#include "ArmBase.h"
#include "../../../Other/CommonModule/MyVECTOR.h"
#include "../../../Other/CommonModule/MyMath.h"

void ArmController::Move() {
	if (padPortNum == -1 || !owner) return;
	// スティックの値を取得
	VECTOR stick;
	if (owner->GetArmPos() == Left)
		stick = InputUtility::GetLeftStick(padPortNum);
	else if (owner->GetArmPos() == Right)
		stick = InputUtility::GetRightStick(padPortNum);

	MyVECTOR::ChangeElementXY(stick);
	stick.y *= -1;

    // 常に前方方向へ進む（ロケットパンチ挙動）に、入力は補助的に加える
    float delta = TimeUtility::GetDeltaTime();
	float baseSpeed = owner->GetMoveSpeed();

    float inputInfluence = 1.0f; // 入力による移動の重み（0..1）

	// 発射直後のブースト（最初だけ推進力を上げる）
	const float boostDuration = 0.125f; // 秒（短縮）
	const float boostMultiplier = 2.5f; // 直後のスピード倍率
	float forwardSpeedMultiplier = 1.0f;

	if (owner->IsShot() && owner->GetShotTime() < boostDuration) {
		forwardSpeedMultiplier = boostMultiplier;
	}

	// オーナーの向き（Y回転）から前方ベクトルを作成
	float currentYaw = MyMath::Deg2Rad(owner->GetRotation().y);
	VECTOR forward = VGet(sinf(currentYaw), 0.0f , cosf(currentYaw));

    // 発射直後のみ前方ブーストを与える（それ以外は前方移動しない）
	VECTOR forwardMove = VGet(0.0f, 0.0f, 0.0f);
	if (owner->IsShot() && owner->GetShotTime() < boostDuration) {
		forwardMove = VScale(forward, delta * baseSpeed * forwardSpeedMultiplier);
		inputInfluence = 0.3f;
	}

	// 入力に基づく移動（補助）
	VECTOR inputMove = VScale(stick, delta * baseSpeed * inputInfluence);

	// 合成移動ベクトル（XY平面）
	VECTOR moveDir = VAdd(forwardMove, inputMove);

	// 座標系に合わせて z/y の入れ替え
	moveDir.z = moveDir.y;
	moveDir.y = 0.0f;

	// 移動
	owner->GetTransform().AddPosition(moveDir);

	// 入力が無いなら戻る
	if (MyVECTOR::CompareVECTORToEqual(stick, VZero)) return;

    VECTOR dir = MyMath::Normalize(VGet(moveDir.x,0.0f, moveDir.z));
	float dirYaw = atan2f(dir.x, dir.z);

	float diff = dirYaw - currentYaw;

	while (diff > DX_PI_F) diff -= DX_TWO_PI_F;
	while (diff < -DX_PI_F) diff += DX_TWO_PI_F;

    // 回転速度は deg/sec 指定で扱い、デルタ時間でフレーム当たりのラジアン上限に変換する
    const float maxRotateDegPerSec = 720.0f; // deg/sec
	float rotateSpeed = MyMath::Deg2Rad(maxRotateDegPerSec); // rad/frame
	diff = std::clamp(diff, -rotateSpeed, rotateSpeed);

	// 移動方向に回転
	owner->GetTransform().AddRotation(VScale(VUp, diff));

}

void ArmController::Move_NoShot(VECTOR _dir, float _rotateSpeed) {
  // _rotateSpeed は度/秒で渡される想定にして、デルタ時間でスケーリングして使用する
	float delta = TimeUtility::GetDeltaTime();
	float dirYaw = atan2f(_dir.x, _dir.y);
	float currentYaw = MyMath::Deg2Rad(owner->GetRotation().y);
	float diff = dirYaw - currentYaw;

	while (diff > DX_PI_F) diff -= DX_TWO_PI_F;
	while (diff < -DX_PI_F) diff += DX_TWO_PI_F;

 // 既存コードでは _rotateSpeed はラジアンでの上限値として渡されるため、そのまま使用する
	float rotateSpeed = _rotateSpeed;
	diff = std::clamp(diff, -rotateSpeed, rotateSpeed);

	// 移動方向に回転
	owner->GetTransform().AddRotation(VScale(VUp, diff));
}
