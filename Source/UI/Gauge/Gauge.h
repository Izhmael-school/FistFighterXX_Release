#pragma once
#include "../UIBase.h"
#include "../../Definition.h"
#include "../../Utility/TimeUtility.h"
#include <functional>
#include "DxLib.h"

class UIGauge : public UIBase {
private:
	// 徐々に減る演出用
	float currentDecreaseValue;

	float barWidth;

	// 色
	unsigned int topColor = green;
	unsigned int bottomColor = red;
	unsigned int frameColor = black;

	// 徐々に減るゲージの色
	unsigned int backColor = GetColor(50, 175, 50);
	// 徐々に減るスピード
	float speed;
	// 徐々に減るか
	bool isDecrease;

	std::function<int()> currentValue;
	std::function<int()> maxValue;

public:
	UIGauge( float _x, float _y, float _w, float _h,UITag _tag = NoUITag, bool _isDecrease = true)
		:UIBase(_x,_y,_w,_h,_tag)
		,currentDecreaseValue(-1)
		, speed(1)
		,barWidth(0.0f)
		, isDecrease(_isDecrease) {}

	~UIGauge() = default;

	void ChangeColor(unsigned int _top, unsigned int _bottom, unsigned int _frame, unsigned int _back);

	inline void SetSpeed(float _speed) { speed = _speed; }

	inline void SetGetterFunc(std::function<int()> _current, std::function<int()> _max) {
		currentValue = _current;
		maxValue = _max;
	}

	void Update() override;
	void Render() override;
};