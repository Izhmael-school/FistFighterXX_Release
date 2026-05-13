#pragma once
#include <memory>
#include "../Definition.h"
#include <string>
#include "../Manager/ArmManager.h"

class ArmBase;
class Player;

class ArmUtility {
public:
	// ウデの未使用化
	static void UnuseArm(ArmBase* _arm);
	// ウデの取得
	static ArmBase* UseArm(ArmType _type, Player* _owner, ArmPos pos, std::string _attachFrameName);

	static int GetArmGraphHandle(ArmType _arm);

	static ArmData GetArmData(ArmType _arm);

	static void DeleteData();
};

