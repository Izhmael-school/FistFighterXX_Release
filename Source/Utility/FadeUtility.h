#pragma once
#include "../Definition.h"

class FadeUtility {
public:

	static void FadeStart(FadeState _state, FadeType _type, float _time = 1.0f);

	static void Render();
	
	static FadeState GetCurrentState();
};