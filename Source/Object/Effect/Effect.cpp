#include "Effect.h"
#include <EffekseerForDXLib.h>

Effect::Effect(int& _resourceHandle)
	:Object(EffectTag)
	, resourceHandle(_resourceHandle)
	, playingHandle(-1)
	,isActive(true)
{

}

Effect::~Effect() {
	// オブジェクトが消えるときはエフェクトも強制停止させる
	if (playingHandle != -1) {
		StopEffekseer3DEffect(playingHandle);
		playingHandle = -1;
	}
}

void Effect::Start() {
	
}

void Effect::Update() {
	//非表示なら更新しない
	if (!isActive)
		return;

	Object::Update();

	//エフェクトの再生
	if (playingHandle == -1)
		playingHandle = PlayEffekseer3DEffect(resourceHandle);

	//再生が終わったら非表示に
	if (IsEffekseer3DEffectPlaying(playingHandle) == -1)
		isActive = false;

	//エフェクトの座標等変更
	VECTOR pos = GetPosition();
	VECTOR rot = GetRotation();
	SetPosPlayingEffekseer3DEffect(playingHandle, pos.x, pos.y, pos.z);
	SetRotationPlayingEffekseer3DEffect(playingHandle, rot.x, rot.y, rot.z);
}

void Effect::Stop()
{
	if (playingHandle != -1) {
		StopEffekseer3DEffect(playingHandle);
		playingHandle = -1;
	}
	isActive = false;
}

void Effect::Render() {
	//非表示なら描画しない
	if (!isActive)
		return;



}