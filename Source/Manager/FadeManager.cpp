#include "FadeManager.h"

FadeManager::FadeManager() 
{ Start(); }


void FadeManager::Start() {
	fade[FadeNormal] = std::make_unique<FadeBase>();
}

void FadeManager::Render() {
	if (!currentFade) return;

	currentFade->Render();

	if (currentFade->GetCurrentState() == None)
		FadeEnd();
}

void FadeManager::FadeStart(FadeState _state, FadeType _type, float _time) {
	if (currentFade || _state == None || _type == FadeMax || _time <= 0) return;

	currentFade = std::move(fade[_type]);
	currentFade->FadeStart(_state, _time);
	currentFadeType = _type;
	currentFadeState = _state;
}

void FadeManager::FadeEnd() {
	fade[currentFadeType] = std::move(currentFade);
	currentFadeState = None;
}
