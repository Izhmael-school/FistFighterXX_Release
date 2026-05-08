#include "FadeUtility.h"
#include "../Manager/FadeManager.h"

void FadeUtility::FadeStart(FadeState _state, FadeType _type, float _time) {
	FadeManager::GetInstance().FadeStart(_state, _type, _time);
}

void FadeUtility::Render() {
	FadeManager::GetInstance().Render();
}

FadeState FadeUtility::GetCurrentState() {
	return FadeManager::GetInstance().GetCurrentState();
}
