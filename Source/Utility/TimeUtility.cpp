#include "TimeUtility.h"

float TimeUtility::GetDeltaTime() { return TimeManager::GetInstance().GetDeltaTime(); }

void TimeUtility::Update() { return TimeManager::GetInstance().Update(); }
