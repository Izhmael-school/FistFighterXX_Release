#include "Audio.h"
#include <DxLib.h>
#include <cassert>

Audio::Audio(int _sHandle, float _volume, bool _isLoop, bool _is3D)
	:soundHandle(_sHandle)
	, volume(_volume)
	, isLoop(_isLoop)
	, is3D(_is3D)
	, distance(0)
	, isPlay(false)
{ Setup(); }

void Audio::Setup() {
	// 上手く読み込めていなかったら
	if (soundHandle == -1) {
		assert(soundHandle == -1);
		return;
	}

	isActive = true;

	// 音量の変更
	SetVolumeSoundMem(static_cast<int>(volume), soundHandle);

	PlayStart();
}

void Audio::PlayStart() {
	if (isLoop)
		PlaySoundMem(soundHandle, DX_PLAYTYPE_LOOP);
	else
		PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);

	isPlay = true;
}

void Audio::Update() {
	if (!isPlay) return;

	// 再生中か
	if (CheckSoundMem(soundHandle) == 0) {
		isActive = false;
		return;
	}


	// 音量の設定
	ChangeVolumeSoundMem((int)volume, soundHandle);

	// 3Dじゃないなら
	if (!is3D) return;

	// 音源の位置を更新
	Set3DPositionSoundMem(GetTransform().GetPosition(), soundHandle);
	// 音の聞こえる範囲を設定
	Set3DRadiusSoundMem(distance, soundHandle);
}
