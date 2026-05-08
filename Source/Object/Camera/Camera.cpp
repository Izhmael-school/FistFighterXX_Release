#include "Camera.h"
#include "../../Other/CommonModule/MyMath.h"
#include "../../Other/CommonModule/MyString.h"
#include "../../Definition.h"
#include "../../Utility/InputUtility.h"
#include "../../Utility/TimeUtility.h"

std::unique_ptr<Camera> Camera::main = std::make_unique<Camera>(VZero);

Camera::Camera(VECTOR _pos)
	:type(Free)
	, moveStop(false)
	, targetCamera() {}

void Camera::Start() {}

void Camera::Update() {
	Object::Update();
	switch (type) {
	case Free:
	{
		if (InputUtility::IsKeyDown(KEY_INPUT_LSHIFT))
			moveStop = !moveStop;

		if (!moveStop) {

			if (InputUtility::IsKey(KEY_INPUT_UP)) transform.AddRotation(VLeft, 2);
			if (InputUtility::IsKey(KEY_INPUT_DOWN)) transform.AddRotation(VRight, 2);
			if (InputUtility::IsKey(KEY_INPUT_RIGHT)) transform.AddRotation(VUp, 2);
			if (InputUtility::IsKey(KEY_INPUT_LEFT)) transform.AddRotation(VDown, 2);


			float speed = 10.0f;

			if (InputUtility::IsKey(KEY_INPUT_W))
				transform.AddPosition(transform.GetForward(), speed);

			if (InputUtility::IsKey(KEY_INPUT_S))
				transform.AddPosition(transform.GetForward(), -speed);

			if (InputUtility::IsKey(KEY_INPUT_D))
				transform.AddPosition(transform.GetRight(), speed);

			if (InputUtility::IsKey(KEY_INPUT_A))
				transform.AddPosition(transform.GetRight(), -speed);

			if (InputUtility::IsKey(KEY_INPUT_Q))
				transform.AddPosition(transform.GetUp(), -speed);

			if (InputUtility::IsKey(KEY_INPUT_SPACE))
				transform.AddPosition(transform.GetUp(), speed);
		}
	}
	break;
	case Fixed:

		break;
	case Target:

		if (!targetCamera.isMove) return;

		targetCamera.timer += TimeUtility::GetDeltaTime();
		float t = targetCamera.timer / targetCamera.moveTime;

		if (t >= 1.0f) {
			targetCamera.isMove = false;
			type = Free;
			t = 1.0f;
		}

		// 移動
		GetTransform().SetPosition(VAdd(targetCamera.startPos, VScale(VSub(targetCamera.endPos, targetCamera.startPos), t)));

		targetCamera.lookPos = VAdd(targetCamera.targetPos, VScale(targetCamera.forward,10));

		VECTOR rot = DirToRotation(VSub(targetCamera.lookPos, GetPosition()));

		GetTransform().SetRotation(rot);

		break;
	}

	VECTOR pos = transform.GetPosition();
	VECTOR rot = transform.GetRotation();

	SetCameraPositionAndAngle(pos, MyMath::Deg2Rad(rot.x), MyMath::Deg2Rad(rot.y), MyMath::Deg2Rad(rot.z));

	Set3DSoundListenerPosAndFrontPos_UpVecY(pos, VAdd(pos, VForward));
}

void Camera::ChangeCameraMode_Ortho(float _fov) {
	SetupCamera_Ortho(_fov);
}

void Camera::ChangeCameraMode_Perspective(float _fov) {
	SetupCamera_Perspective(_fov);
}

void Camera::SetTargetCamera(VECTOR _endPos, VECTOR _targetPos, VECTOR _targetForward, float _moveTime) {
	if (targetCamera.isMove) return;

	targetCamera.startPos = GetPosition();
	targetCamera.endPos = _endPos;
	targetCamera.forward = _targetForward;
	targetCamera.targetPos = _targetPos;
	targetCamera.lookPos = _targetPos;
	targetCamera.timer = 0.0f;
	targetCamera.moveTime = _moveTime;
	targetCamera.isMove = true;
	type = Target;
}

VECTOR Camera::DirToRotation(VECTOR _dir) {
	_dir = VNorm(_dir);

	VECTOR rot;

	// yaw（左右）
	rot.y = atan2f(_dir.z, _dir.x) + 90;

	// pitch（上下）
	rot.x = atan2f(-_dir.y, sqrtf(_dir.x * _dir.x + _dir.z * _dir.z));

	rot.z = 0.0f;

	return rot;
}

VECTOR Camera::CalcLookRotation(VECTOR _from, VECTOR _to) {
	VECTOR dir = VSub(_to, _from);

	// 正規化
	float len = VSize(dir);
	if (len == 0.0f) return GetRotation();

	dir = VScale(dir, 1.0f / len);

	VECTOR rot;

	rot.x = -atanf(dir.y);

	rot.y = atan2f(dir.x, dir.z);

	rot.z = 0.0f;

	return rot;
}
