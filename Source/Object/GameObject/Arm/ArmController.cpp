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

    // ロケットパンチ
    float delta = TimeUtility::GetDeltaTime();
	float baseSpeed = owner->GetMoveSpeed();

    float inputInfluence = 1.0f; // 入力による移動の影響度

	// 発射直後ブースト
	const float boostDuration = 0.125f; 
	const float boostMultiplier = 2.5f;
	float forwardSpeedMultiplier = 1.0f;

	if (owner->IsShot() && owner->GetShotTime() < boostDuration) {
		forwardSpeedMultiplier = boostMultiplier;
	}

	// 前方ベクトルを作成
	float currentYaw = MyMath::Deg2Rad(owner->GetRotation().y);
	VECTOR forward = VGet(sinf(currentYaw), 0.0f , cosf(currentYaw));

    // 発射直後のみ前方ブースト
	VECTOR forwardMove = VGet(0.0f, 0.0f, 0.0f);
	if (owner->IsShot() && owner->GetShotTime() < boostDuration) {
		forwardMove = VScale(forward, delta * baseSpeed * forwardSpeedMultiplier);
		inputInfluence = 0.3f;
	}

	// 入力に基づく移動
	VECTOR inputMove = VScale(stick, delta * baseSpeed * inputInfluence);

	// 合成移動ベクトル
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

    const float maxRotateDegPerSec = 720.0f; // deg/sec
	float rotateSpeed = MyMath::Deg2Rad(maxRotateDegPerSec); // rad/frame
	diff = std::clamp(diff, -rotateSpeed, rotateSpeed);

	// 移動方向に回転
	owner->GetTransform().AddRotation(VScale(VUp, diff));

}

void ArmController::Move_NoShot(VECTOR _dir, float _rotateSpeed) {
	float delta = TimeUtility::GetDeltaTime();
	float dirYaw = atan2f(_dir.x, _dir.y);
	float currentYaw = MyMath::Deg2Rad(owner->GetRotation().y);
	float diff = dirYaw - currentYaw;

	while (diff > DX_PI_F) diff -= DX_TWO_PI_F;
	while (diff < -DX_PI_F) diff += DX_TWO_PI_F;

	float rotateSpeed = _rotateSpeed;
	diff = std::clamp(diff, -rotateSpeed, rotateSpeed);

	// 移動方向に回転
	owner->GetTransform().AddRotation(VScale(VUp, diff));
}
