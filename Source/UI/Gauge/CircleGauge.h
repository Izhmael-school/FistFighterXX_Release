#pragma once
#include "../UIBase.h"
#include "../../Definition.h"
#include "../../Utility/TimeUtility.h"
#include "../../Other/CommonModule/MyMath.h"

class UICircleGauge : public UIBase {
private:
	float currentDecreaseAngle;

	// îºåa
	float outerRadius;
	float innerRadius;

	// äpìx
	float startDeg;
	float endDeg;

	// êF
	unsigned int topColor = green;
	unsigned int bottomColor = red;
	unsigned int frameColor = black;
	unsigned int backColor = GetColor(50, 175, 50);

	// å∏è≠ââèo
	float speed;
	bool isDecrease;

	// êj
	bool isNeedle;
	float needleLength;
	unsigned int needleColor;
	int needleThickness;

public:
	UICircleGauge(float _x,float _y,float outerR,float thickness,float _startDeg = -90.0f,float _endDeg = 270.0f,bool _isDecrease = true);
		
	inline void SetSpeed(float s) { speed = s; }

	void ChangeColor(unsigned int _top, unsigned int _bottom, unsigned int _frame, unsigned int _back);

	void DrawRing(float drawEndDeg, unsigned int color, int div = 128);

	inline void EnableNeedle(bool enable) {isNeedle = enable;}

	inline void SetNeedle(float length, unsigned int color, int thickness = 2) {
		needleLength = length;
		needleColor = color;
		needleThickness = thickness;
	}

	void DrawNeedle(float angleDeg);


	void Render(float _currentValue, float _maxValue);
};