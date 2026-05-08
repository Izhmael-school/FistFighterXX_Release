#pragma once
#include "../Object.h"
#include "DxLib.h"
#include "../../Definition.h"
#include <memory>

struct MoveTargetCamera {
	VECTOR startPos;
	VECTOR endPos;
	VECTOR forward;
	VECTOR targetPos;
	VECTOR lookPos;
	float timer;
	float moveTime;
	bool isMove = false;
};

class Camera : public Object{
public:
	Camera(VECTOR _pos);
	~Camera() = default;

	void Start() override;
	void Update() override;

	void ChangeCameraMode_Ortho(float _fov);
	void ChangeCameraMode_Perspective(float _fov);
	 
	void SetTargetCamera(VECTOR _endPos,VECTOR _targetPos,VECTOR _targetForward,float _moveTime);

	inline bool IsTargetCameraMove() { return type == Target && targetCamera.isMove; }

private:
	VECTOR DirToRotation(VECTOR _dir);
	VECTOR CalcLookRotation(VECTOR _from, VECTOR _to);

private:
	bool moveStop;
	CameraType type;

	MoveTargetCamera targetCamera;
public:
	static std::unique_ptr<Camera> main;
};

