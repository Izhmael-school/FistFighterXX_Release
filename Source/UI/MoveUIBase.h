#pragma once
#include "UIBase.h"

class Object;

class MoveUIBase :public UIBase{
public:
	MoveUIBase(Object* _sourceObject,float _offsetX,float _offsetY, float _width = 0.0f, float _height = 0.0f, UITag _tag = NoUITag);
	~MoveUIBase() = default;

public:
	void Update() override;
	virtual void Render() override = 0;

protected:
	Object* sourceObject;
	float offsetX;
	float offsetY;
};

