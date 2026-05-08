#pragma once
#include <string>
#include "DxLib.h"

class AudioUtility {
public:
	// 読み込み
	static void Load(std::string _filePath, std::string _name, bool _is3D);
	// 音量の変更
	static void ChangeVolume(float _volume, std::string _name = "all");
	// BGMとして再生
	static void PlayBGM(std::string _name, float _v = 255.0f);
	// SEとして再生
	static void PlayOneShot(std::string _name);
	// 3D効果のある効果音を再生
	static void PlayClipAtPoint(std::string _name, VECTOR _pos);
	// 止める
	static void Stop(std::string _name = "all");
	// 更新処理
	static void Update();
	// 読み込んだデータを消す
	static void DeleteData();

	static float GetMasterVolume();

	static float GetBGMVolume();

	static float GetSEVolume();

	static void SetMasterVolume(float _v);

	static void SetBGMVolume(float _v);

	static void SetSEVolume(float _v);

	static void AddMasterVolume(float _v);

	static void AddBGMVolume(float _v);
	
	static void AddSEVolume(float _v);
};

