#include "Gauge.h"


void UIGauge::ChangeColor(unsigned int _top, unsigned int _bottom, unsigned int _frame, unsigned int _back) {
	topColor = _top;
	bottomColor = _bottom;
	frameColor = _frame;
	backColor = _back;
}

void UIGauge::Update() {
	if (!currentValue || !maxValue) return;

	float value = static_cast<float>(currentValue()) / static_cast<float>(maxValue());
	if (value > 1) value = 1;

	barWidth = w * value;

	float diff = barWidth - currentDecreaseValue;

	currentDecreaseValue += diff * TimeUtility::GetDeltaTime() * speed;

	// î˜êUìÆñhé~
	if (fabs(diff) < 0.1f) {
		currentDecreaseValue = barWidth;
	}
}

void UIGauge::Render() {
	// îwåi
	DrawBoxAA(x, y, x + w, y + h, bottomColor, true);
	// èôÅXÇ…å∏ÇÈÇ©
	if (isDecrease) {
		// ëOÇÊÇËÉQÅ[ÉWÇ™å∏Ç¡ÇƒÇ¢ÇÈÇ©
		if (barWidth < currentDecreaseValue) {
			// èôÅXÇ…å∏ÇÈ
			DrawBoxAA(x, y, x + currentDecreaseValue, y + h, backColor, true);
			DrawBoxAA(x, y, x + barWidth, y + h, topColor, true);
		}
		else {
			DrawBoxAA(x, y, x + barWidth, y + h, backColor, true);
			// èôÅXÇ…ëùÇ¶ÇÈ
			DrawBoxAA(x, y, x + currentDecreaseValue, y + h, topColor, true);
		}
	}
	else {
		DrawBoxAA(x, y, x + barWidth, y + h, topColor, true);
	}

	// òg
	DrawBoxAA(x, y, x + w, y + h, frameColor, false);
}