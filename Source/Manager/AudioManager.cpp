#include "AudioManager.h"
#include "../Object/Audio/Audio.h"
#include "../Other/CommonModule/MyString.h"

AudioManager::AudioManager()
	:audioResourceMap()
	, pAudioArray()
	, masterVolume(1.0f)
	, bgmVolume(1.0f)
	, seVolume(1.0f) 
{Start();}

AudioManager::~AudioManager() {
	pAudioArray.clear();
	audioResourceMap.clear();
}

void AudioManager::Start() {
	SetMasterVolume(0.7f);

	Load(MyString::MergeString(SE_FILEPATH, "ButtonPush", AUDIO_EXTENSION), "buttonPush", false);
	Load(MyString::MergeString(SE_FILEPATH, "OnButton", AUDIO_EXTENSION), "onButton", false);
}

void AudioManager::Load(std::string _filePath, std::string _name, bool _is3D) {
	SetCreate3DSoundFlag(_is3D);

	// ‚·‚Å‚É‚ ‚ê‚Î“o˜^‚µ‚È‚¢
	if (audioResourceMap.find(_name.c_str()) != audioResourceMap.end()) return;

	int resNum = LoadSoundMem(_filePath.c_str());

	audioResourceMap.emplace(_name.c_str(), resNum);
}

void AudioManager::ChangeVolume(float _volume, std::string _name) {
	if (_name == "all") {
		for (auto& a : pAudioArray) {
			a->SetVolume(_volume);
		}
	}
	else {
		for (auto& a : pAudioArray) {
			if (a->GetName() != _name) continue;
			a->SetVolume(_volume);
		}
	}
}

void AudioManager::PlayBGM(std::string _name, float _v) {
	int sound = -1;

	sound = DuplicateSoundMem(audioResourceMap[_name]);

	if (sound == -1) return;

	std::unique_ptr<Audio> audio = std::make_unique<Audio>(sound, _v * (masterVolume * bgmVolume));
	audio->SetName(_name);
	audio->SetLoop(true);
	audio->Setup();
	pAudioArray.push_back(std::move(audio));
}

void AudioManager::PlayOneShot(std::string _name) {
	int sound = -1;

	sound = DuplicateSoundMem(audioResourceMap[_name]);

	if (sound == -1) return;

	std::unique_ptr<Audio> audio = std::make_unique<Audio>(sound, 255.0f * (masterVolume * seVolume));
	audio->SetName(_name);
	audio->Setup();
	pAudioArray.push_back(std::move(audio));
}

void AudioManager::PlayClipAtPoint(std::string _name, VECTOR _pos) {
	int sound = -1;

	sound = DuplicateSoundMem(audioResourceMap[_name]);

	if (sound == -1) return;

	std::unique_ptr<Audio> audio = std::make_unique<Audio>(sound);
	audio->SetName(_name);
	audio->GetTransform().SetPosition(_pos);
	audio->Setup();
	pAudioArray.push_back(std::move(audio));
}

void AudioManager::Stop(std::string _name) {
	if (_name == "all") {
		for (auto& a : pAudioArray) {
			StopSoundMem(a->GetSoundHandle());
		}
	}
	else {
		for (auto& a : pAudioArray) {
			if (a->GetName() != _name) continue;
			StopSoundMem(a->GetSoundHandle());
		}
	}
}

void AudioManager::Update() {
	for (auto& a : pAudioArray) {
		if (!a) continue;

		a->Update();
	}

	std::erase_if(pAudioArray, [](const std::unique_ptr<Audio>& a) {return !a->IsActive(); });
}

void AudioManager::DeleteData() {
	
}
