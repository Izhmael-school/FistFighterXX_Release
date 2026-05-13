#pragma once
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include <memory>
#include "../Definition.h"
#include "../Generator/ArmGenerator.h"
#include <vector>
#include <array>
#include <string>

class ArmBase;
class Player;

struct ArmData {
	std::string armName;
	int atkValue;
	int spdValue;
	int staminaValue;
	int durabirity;
	int strength;
	std::string tips;
};

class ArmManager : public Singleton<ArmManager>, public ManagerBase {
private:
	void Start();
public:
	ArmManager();
	~ArmManager() = default;

	void DeleteData() override;
	void UnuseArm(ArmBase* _arm);
	ArmBase* UseArm(ArmType _type,Player* _owner, ArmPos pos, std::string _attachFrameName);

	int GetArmGraphHandle(ArmType _arm);

	ArmData GetArmData(int _armID);
private:
	std::array<std::vector<std::unique_ptr<ArmBase>>,ArmTypeMax> unuseArmArray;
	std::array<std::vector<std::unique_ptr<ArmBase>>,ArmTypeMax> useArmArray;
	std::array<int, ArmTypeMax> armImage;
	std::unique_ptr<ArmGenerator> generator;
};

