#include "AudioUtility.h"
#include "../Manager/AudioManager.h"

void AudioUtility::Load(std::string _filePath, std::string _name, bool _is3D) {
	AudioManager::GetInstance().Load(_filePath, _name, _is3D);
}

void AudioUtility::ChangeVolume(float _volume, std::string _name) {
	AudioManager::GetInstance().ChangeVolume(_volume, _name);
}

void AudioUtility::PlayBGM(std::string _name, float _v) {
	AudioManager::GetInstance().PlayBGM(_name, _v);
}

void AudioUtility::PlayOneShot(std::string _name) {
	AudioManager::GetInstance().PlayOneShot(_name);
}

void AudioUtility::PlayClipAtPoint(std::string _name, VECTOR _pos) {
	AudioManager::GetInstance().PlayClipAtPoint(_name, _pos);
}

void AudioUtility::Stop(std::string _name) {
	AudioManager::GetInstance().Stop(_name);
}

void AudioUtility::Update() {
	AudioManager::GetInstance().Update();
}

void AudioUtility::DeleteData() {
	AudioManager::GetInstance().DeleteData();
}

float AudioUtility::GetMasterVolume() {
	return AudioManager::GetInstance().GetMasterVolume();
}

float AudioUtility::GetBGMVolume() {
	return AudioManager::GetInstance().GetBGMVolume();
}

float AudioUtility::GetSEVolume() {
	return AudioManager::GetInstance().GetSEVolume();
}

void AudioUtility::SetMasterVolume(float _v) {
	AudioManager::GetInstance().SetMasterVolume(_v);
}

void AudioUtility::SetBGMVolume(float _v) {
	AudioManager::GetInstance().SetBGMVolume(_v);
}

void AudioUtility::SetSEVolume(float _v) {
	AudioManager::GetInstance().SetSEVolume(_v);
}

void AudioUtility::AddMasterVolume(float _v) {
	AudioManager::GetInstance().AddMasterVolume(_v);
}

void AudioUtility::AddBGMVolume(float _v) {
	AudioManager::GetInstance().AddBGMVolume(_v);
}

void AudioUtility::AddSEVolume(float _v) {
	AudioManager::GetInstance().AddSEVolume(_v);
}
