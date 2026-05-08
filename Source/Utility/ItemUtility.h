#pragma once
#include "DxLib.h"
#include "../Definition.h"

class ItemBase;

class ItemUtility {
public:
	static void Update();
	static void Render();
	static ItemBase* Use(int _id , VECTOR _pos = VZero);
	static void UnuseAll();
	static void DeleteData();
};

