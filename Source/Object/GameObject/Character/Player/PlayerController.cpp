#include "PlayerController.h"
#include "../../../../Utility/InputUtility.h"
#include "../../../../Utility/TimeUtility.h"
#include "Player.h"
#include "../../Arm/ArmBase.h"
#include "../../../../CommonModule.h"
#include "../../../../Other/CommonModule/MyVECTOR.h"
#include "../../../../Other/CommonModule/MyMath.h"

void PlayerController::Update() {

	// ウデの発射をしていなければ
	if (owner->GetShotNum() == 0) {
		Move();
	}

	if (InputUtility::IsPadDown(padPortNum, XINPUT_BUTTON_LEFT_SHOULDER))
		owner->ShotArm(Left);
	if (InputUtility::IsPadDown(padPortNum, XINPUT_BUTTON_RIGHT_SHOULDER))
		owner->ShotArm(Right);
}

void PlayerController::Move() {
	if (padPortNum == -1 || !owner) return;
	// 左スティックの値を取得
	VECTOR leftStick = InputUtility::GetLeftStick(padPortNum);

	MyVECTOR::ChangeElementXY(leftStick);
	leftStick.y *= -1;

	if (!isDash && lastDashTime < dashSpan)
		lastDashTime += TimeUtility::GetDeltaTime();

	if(isDash)
		dashTime -= TimeUtility::GetDeltaTime();

	if (dashTime <= 0 && isDash) {
		isDash = false;
		lastDashTime = 0.0f;
	}

	if (MyVECTOR::CompareVECTORToEqual(leftStick, VZero)) return;

	if (InputUtility::IsPadDown(padPortNum, XINPUT_BUTTON_B) && lastDashTime >= dashSpan && !isDash) {
		isDash = true;
		dashTime = 0.1f;
	}
	// 移動方向
	VECTOR moveDir = VZero;

 	float _moveSpeed = owner->GetMoveSpeed() * (isDash ? 10 : 1);

	moveDir = VScale(leftStick, TimeUtility::GetDeltaTime() * _moveSpeed);

	VECTOR dir = MyMath::Normalize(moveDir);
	float dirYaw = atan2f(dir.x, dir.y);
	float currentYaw = MyMath::Deg2Rad(owner->GetRotation().y + 180.0f);

	float diff = dirYaw - currentYaw;

	while (diff > DX_PI_F) diff -= DX_TWO_PI_F;
	while (diff < -DX_PI_F) diff += DX_TWO_PI_F;

	float rotateSpeed = (MyMath::Deg2Rad(180.0f) * TimeUtility::GetDeltaTime() * owner->GetMoveSpeed()) * 100;
	diff = std::clamp(diff, -rotateSpeed, rotateSpeed);

	moveDir.z = moveDir.y;
	moveDir.y = 0.0f;

	// 移動方向に回転
	owner->GetTransform().AddRotation(VScale(VUp, diff));

	// 撃ってない腕の回転
	for (int i = 0; i < ArmMax; i++) {
		ArmBase* arm = owner->GetArm(static_cast<ArmPos>(i));
		if (arm->IsShot()) continue;

		arm->GetController().Move_NoShot(dir, rotateSpeed);
	}

	// 移動
	owner->GetTransform().AddPosition(moveDir);
}
