#pragma once
#include "../Definition.h"



class FadeBase {

public:
	FadeBase() = default;
	~FadeBase() = default;
	virtual void Render();

	void FadeStart(FadeState _state, float _time = 1.0f);

	inline FadeState GetCurrentState() const { return currentState; }
private:


private:
	FadeState currentState;
	float alpha;
	float time;


};

