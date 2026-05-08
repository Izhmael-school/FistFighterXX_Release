#pragma once
#include "DxLib.h"

class ArmBase;

class ArmController {
public:
	ArmController() = default;
	~ArmController() = default;

	void Move();
	// Œ‚‚Á‚Ä‚È‚¢ó‘Ô‚Ì‰ñ“]§Œä“™
	void Move_NoShot(VECTOR _dir, float _rotateSpeed);
	inline void SetPortNum(int _index) { padPortNum = _index; }
	inline void SetOwner(ArmBase* _owner) { owner = _owner; }

private:
	int padPortNum = -1;
	ArmBase* owner;
};

