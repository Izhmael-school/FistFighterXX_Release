#include "Span.h"
#include "../../Utility/TimeUtility.h"

void Span::UpdateTime() {
	currentTime += TimeUtility::GetDeltaTime();
}

bool Span::IsTime() {
	if (targetTime > currentTime) return false;

	currentTime = 0.0f;
	return true;
}

bool Span::IsTimeNoReset() {
	return targetTime < currentTime;
}
