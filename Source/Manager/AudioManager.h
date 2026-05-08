#pragma once
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include <list>
#include <string>
#include <map>
#include <memory>
#include <DxLib.h>
#include <algorithm>
#include <cmath>

class Audio;

class AudioManager : public Singleton<AudioManager>, public ManagerBase {
private:
	std::map<std::string, int> audioResourceMap;
	std::list<std::unique_ptr<Audio>> pAudioArray;

	double masterVolume;
	double bgmVolume;
	double seVolume;

public:
	AudioManager();
	~AudioManager();

private:
	void Start();

public:
	// 読み込み
	void Load(std::string _filePath, std::string _name, bool _is3D);
	// 音量の変更
	void ChangeVolume(float _volume, std::string _name = "all");
	// BGMとして再生
	void PlayBGM(std::string _name, float _v = 255.0f);
	// SEとして再生
	void PlayOneShot(std::string _name);
	// 3D効果のある効果音を再生
	void PlayClipAtPoint(std::string _name, VECTOR _pos);
	// 止める
	void Stop(std::string _name = "all");
	// 更新処理
	void Update() override;
	// 読み込んだデータを消す
	void DeleteData() override;

	inline void SetMasterVolume(float _v) { masterVolume = std::clamp(_v, 0.0f, 1.0f); }
	inline void SetBGMVolume(float _v) { bgmVolume = std::clamp(_v, 0.0f, 1.0f); }
	inline void SetSEVolume(float _v) { seVolume = std::clamp(_v, 0.0f, 1.0f); }

	inline float GetMasterVolume() const { return masterVolume; }
	inline float GetBGMVolume() const { return bgmVolume; }
	inline float GetSEVolume() const { return seVolume; }

	inline void AddMasterVolume(double _v) { masterVolume = std::clamp(std::round(masterVolume * 100.0) / 100.0 + _v, 0.0, 1.0); }
	inline void AddBGMVolume(double _v) { bgmVolume = std::clamp(std::round(bgmVolume * 100.0) / 100.0 + _v, 0.0, 1.0); }
	inline void AddSEVolume(double _v) { seVolume = std::clamp(std::round(seVolume * 100.0) / 100.0 + _v, 0.0, 1.0); }
};

