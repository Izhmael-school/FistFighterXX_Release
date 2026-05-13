#pragma once
#include <string>
#include "DxLib.h"

class Effect;

class EffectUtility {
public:
	static void Load(std::string _filePath, std::string _name, float _magnification = 1.0f);

	static Effect* Instantiate(std::string _name, VECTOR _pos);

	static void Update();

	static void Render();

	static void DeleteData();

	static void DeleteAllEffect();	
};

