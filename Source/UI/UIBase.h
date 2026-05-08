#pragma once
#include "../Definition.h"

class UIBase {
public:
	UIBase(float _x,float _y,float _width = 0.0f, float _height = 0.0f , UITag _tag = NoUITag);
	~UIBase() = default;

public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	inline void SetActive(bool _isActive) { isActive = _isActive; }
	inline bool IsActive() { return isActive; }
	inline float GetX() const { return x; }
	inline float GetY() const { return y; }

	inline UITag GetTag() const { return tag; }
protected:
	float x , y , w , h;
	bool isActive;

	UITag tag;
};