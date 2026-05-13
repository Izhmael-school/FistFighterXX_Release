#include "ArmGenerator.h"
#include "../Object/GameObject/Arm/ArmBase.h"
#include "../Other/CommonModule/MyJson.h"
#include "../Other/CommonModule/MyString.h"
#include "../Include/IncludeArmEffect.h"
#include "DxLib.h"
#include <cassert>

ArmGenerator::ArmGenerator() 
	:originArmModelHandle()
	,armData()
{ Start(); }

void ArmGenerator::Start() {
	LoadArmModel();
}

std::unique_ptr<ArmEffectBase> ArmGenerator::ReturnEffect(ArmType _type) {
	std::unique_ptr<ArmEffectBase> effect;
	switch (_type) {
	case Punch:
		effect = std::make_unique<PunchEffect>();
		break;
	case Drill:
		effect = std::make_unique<DrillEffect>();
		break;
	case Star:
		effect = std::make_unique<StarEffect>();
		break;
	case Bomb:
		effect = std::make_unique<BombEffect>();
		break;
	case Cutter:
		effect = std::make_unique<CutterEffect>();
		break;
	}
	return std::move(effect);
}

void ArmGenerator::LoadArmModel() {
	armData = MyJson::LoadJsonFile(ARMDATA_FILEPATH.data());

	assert(!armData.empty() && "ArmDataが無い");

	for (auto& d : armData) {
		std::string mPath = MyString::MergeString(ARMMODEL_FILEPATH, d["modelFileName"], MODEL_FILE_EXTENSION);
		int mHandle = MV1LoadModel(mPath.c_str());

		assert(mHandle != -1 && "モデルが無い");

		originArmModelHandle.push_back(mHandle);
	}
}

std::unique_ptr<ArmBase> ArmGenerator::CreateArm(ArmType _type, Player* _owner) {
	if (_type == ArmTypeMax) return nullptr;

	// データがなければ読み込む
	if (armData.empty())
		LoadArmModel();

	// モデルの複製
	int mHandle = MV1DuplicateModel(originArmModelHandle[_type]);

	// ウデの効果を作成
	std::unique_ptr<ArmEffectBase> effect = ReturnEffect(_type);

	// ウデの生成
	std::unique_ptr<ArmBase> cArm = std::make_unique<ArmBase>(mHandle, VZero,_owner, std::move(effect));

	// ステータスの読み込み
	auto data = armData[_type];
	ArmStatus status;
	status.attackValue = data["atkValue"];
	status.consumeStaminaValue = data["cStmValue"];
	status.speedValue = data["spdValue"];
	status.strength = data["strength"];
	status.maxDurability = data["maxDurability"];
	status.currentDurability = status.maxDurability;

	cArm->SetStatus(status);
	cArm->SetArmType(static_cast<ArmType>(data["armID"]));

	return cArm;
}

void ArmGenerator::DeleteOriginModelHandle() {
	for (int i = 0, max = ArmTypeMax; i < max; i++) {
		MV1DeleteModel(originArmModelHandle[i]);
	}
}
