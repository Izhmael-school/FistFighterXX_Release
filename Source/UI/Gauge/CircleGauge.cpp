#include "CircleGauge.h"

UICircleGauge::UICircleGauge(float _x, float _y, float outerR, float thickness, float _startDeg, float _endDeg, bool _isDecrease) 
	: UIBase(_x, _y)
	, outerRadius(outerR)
	, innerRadius(outerR - thickness)
	, startDeg(_startDeg)
	, endDeg(_endDeg)
	, speed(5.0f)
	, isDecrease(_isDecrease)
	, isNeedle(false)
	, needleLength(outerRadius)
	, needleColor(white)
	, needleThickness(2) 
	,currentDecreaseAngle(0.0f)
{}

void UICircleGauge::ChangeColor(unsigned int _top, unsigned int _bottom, unsigned int _frame, unsigned int _back) {
	topColor = _top;
	bottomColor = _bottom;
	frameColor = _frame;
	backColor = _back;
}

void UICircleGauge::DrawRing(float drawEndDeg, unsigned int color, int div) {
	for (int i = 0; i < div; i++) {
		float t0 = (float)i / div;
		float t1 = (float)(i + 1) / div;

		float deg0 = startDeg + (drawEndDeg - startDeg) * t0;
		float deg1 = startDeg + (drawEndDeg - startDeg) * t1;

		float r0 = MyMath::Deg2Rad(deg0);
		float r1 = MyMath::Deg2Rad(deg1);

		VECTOR v0 = VGet(x + cosf(r0) * outerRadius, y + sinf(r0) * outerRadius, 0);
		VECTOR v1 = VGet(x + cosf(r1) * outerRadius, y + sinf(r1) * outerRadius, 0);
		VECTOR v2 = VGet(x + cosf(r1) * innerRadius, y + sinf(r1) * innerRadius, 0);
		VECTOR v3 = VGet(x + cosf(r0) * innerRadius, y + sinf(r0) * innerRadius, 0);

		DrawTriangleAA(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y, color, TRUE);
		DrawTriangleAA(v2.x, v2.y, v3.x, v3.y, v0.x, v0.y, color, TRUE);
	}
}

void UICircleGauge::DrawNeedle(float angleDeg) {
	float rad = MyMath::Deg2Rad(angleDeg);

	float nx = x + cosf(rad) * needleLength;
	float ny = y + sinf(rad) * needleLength;

	DrawLineAA(x, y, nx, ny, needleColor, needleThickness);
}

void UICircleGauge::Render(float _currentValue, float _maxValue) {
	float rate = _currentValue / _maxValue;
	if (rate > 1) rate = 1;

	float targetAngle = startDeg + (endDeg - startDeg) * rate;

	float diff = targetAngle - currentDecreaseAngle;
	currentDecreaseAngle += diff * TimeUtility::GetDeltaTime() * speed;

	if (fabs(diff) < 0.1f)
		currentDecreaseAngle = targetAngle;

	// ”wŒi
	DrawRing(endDeg, bottomColor);

	if (isDecrease) {
		if (targetAngle < currentDecreaseAngle) {
			DrawRing(currentDecreaseAngle, backColor);
			DrawRing(targetAngle, topColor);
		}
		else {
			DrawRing(targetAngle, backColor);
			DrawRing(currentDecreaseAngle, topColor);
		}
	}
	else {
		DrawRing(targetAngle, topColor);
	}

	// jiÅŒã‚É•`‰æj
	if (isNeedle) {
		DrawNeedle(currentDecreaseAngle);
	}
}
