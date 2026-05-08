#pragma once
#include "../GameObject.h"
class Character : public GameObject {
public:
	Character(int _mHandle, VECTOR _pos = VZero, Tag _tag = NoTag);
	~Character() = default;

	virtual void Start() override = 0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
};

