#include "MainGameTimer.h"
#include "../Utility/TimeUtility.h"

float MainGameTimer::gameTimer = 0.0f;

void MainGameTimer::Update() {
	gameTimer += TimeUtility::GetDeltaTime();
}

void MainGameTimer::Reset() {
	gameTimer = 0.0f;
}
