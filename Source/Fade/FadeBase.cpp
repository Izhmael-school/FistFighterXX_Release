#include "FadeBase.h"
#include "DxLib.h"
#include "../Utility/TimeUtility.h"

void FadeBase::Render() {
	if (currentState == None)return;

	// アルファの増減
	alpha += (BLEND_MAX * TimeUtility::GetDeltaTime() / time) * static_cast<int>(currentState);

	switch (currentState) {
	case FadeIn:
		if (alpha > 0.0f) break;
		alpha = 0;
		currentState = None;
		break;
	case FadeOut:
		if (alpha < BLEND_MAX) break;
		alpha = BLEND_MAX;
		currentState = None;
		break;
	}

	//	透明度を変化させてフェード処理とする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);
	DrawFillBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, black);
	// ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, -1);
}

void FadeBase::FadeStart(FadeState _state, float _time) {
	if (_state == None || currentState != None) return;
	currentState = _state;
	time = _time;
	alpha = currentState == FadeIn ? BLEND_MAX : 0.0f;
}