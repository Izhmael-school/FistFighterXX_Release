#pragma once
#include "../Object.h"
#include <algorithm>
#include <string>

class Audio : public Object {
private:
	bool is3D;
	bool isLoop;
	int soundHandle;
	float volume;
	float distance;
	bool isPlay;

	std::string name;
	bool isActive;

public:
	Audio(int _sHandle,float _volume = 255.0f,bool _isLoop = false, bool _is3D = false);
	~Audio() = default;


	void Setup();

	void PlayStart();

	void Update();

	inline int GetSoundHandle() const { return soundHandle; }
	inline void SetLoop(bool _isLoop) { isLoop = _isLoop; }
	inline void SetDistance(float _dis) { distance = _dis; }
	inline void SetVolume(float _v) { SetVolumeSoundMem( static_cast<int>(std::clamp(_v, 0.0f, 255.0f)),soundHandle); }
	inline void SetName(std::string _name) { name = _name; }
	inline std::string GetName() const { return name; }
	inline bool IsActive() const { return isActive; }
};

