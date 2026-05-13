#include "ArmManager.h"
#include "../Object/GameObject/Arm/ArmBase.h"
#include "../Utility/EffectUtility.h"
#include "../Utility/AudioUtility.h"
#include "../Other/CommonModule/MyString.h"
#include "../Other/CommonModule/MyJson.h"
#include <cassert>

ArmManager::ArmManager() { Start(); }

void ArmManager::Start() {
	generator = std::make_unique<ArmGenerator>();
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "PunchHit", AUDIO_EXTENSION), "HitPunch", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "DrillHit", AUDIO_EXTENSION), "HitDrill", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "StarHit", AUDIO_EXTENSION), "HitStar", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "BombHit", AUDIO_EXTENSION), "HitBomb", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "CutterHit", AUDIO_EXTENSION), "HitCutter", false);
	EffectUtility::Load("res/Model/Effect/PunchHit.efkefc", "HitPunch", 75.0f);
	EffectUtility::Load("res/Model/Effect/DrillHit.efkefc", "HitDrill", 50.0f);
	EffectUtility::Load("res/Model/Effect/StarHit.efkefc", "HitStar", 75.0f);
	EffectUtility::Load("res/Model/Effect/BombHit.efkefc", "HitBomb", 50.0f);
	EffectUtility::Load("res/Model/Effect/CutterHit.efkefc", "HitCutter", 50.0f);
	armImage[Punch] = LoadGraph(MyString::MergeString(ARM_SPRITE_PATH, "Punch", SPRITE_EXTENSION).c_str());
	armImage[Drill] = LoadGraph(MyString::MergeString(ARM_SPRITE_PATH, "Drill", SPRITE_EXTENSION).c_str());
	armImage[Star] = LoadGraph(MyString::MergeString(ARM_SPRITE_PATH, "MorningStar", SPRITE_EXTENSION).c_str());
	armImage[Bomb] = LoadGraph(MyString::MergeString(ARM_SPRITE_PATH, "Bomb", SPRITE_EXTENSION).c_str());
	armImage[Cutter] = LoadGraph(MyString::MergeString(ARM_SPRITE_PATH, "Cutter", SPRITE_EXTENSION).c_str());
}

void ArmManager::DeleteData() {
	for (auto& armArray : unuseArmArray) {
		for (auto& a : armArray) {
			a->DeleteModel();
		}
	}
}

void ArmManager::UnuseArm(ArmBase* _arm) {

	if (!_arm) return;

	_arm->Teardown();

	ArmType _type = _arm->GetArmType();

	// ’T‚·
	auto itr = std::find_if(
		useArmArray[_type].begin(),
		useArmArray[_type].end(),
		[_arm](const std::unique_ptr<ArmBase>& a) {
			return a.get() == _arm;
		});

	if (itr == useArmArray[_type].end()) return;

	unuseArmArray[_type].push_back(std::move(*itr));

	useArmArray[_type].erase(itr);

	_arm = nullptr;
}

ArmBase* ArmManager::UseArm(ArmType _type, Player* _owner, ArmPos pos, std::string _attachFrameName) {
	if (_type == ArmTypeMax) {
		assert(_type == ArmTypeMax);
		return nullptr;
	}

	ArmBase* arm = nullptr;
	// –³‚¯‚ê‚Îì‚é
	if (unuseArmArray[_type].size() == 0)
		unuseArmArray[_type].push_back(generator->CreateArm(_type, _owner));

	// ƒEƒf‚ÌŽæ“¾
	useArmArray[_type].push_back(std::move(unuseArmArray[_type].back()));
	unuseArmArray[_type].pop_back();

	arm = useArmArray[_type].back().get();
	arm->SetOwner(_owner);

	arm->ArmAttach(_attachFrameName);
	arm->SetArmPos(pos);
	arm->Setup();

	return arm;
}

int ArmManager::GetArmGraphHandle(ArmType _arm) {
	return armImage[_arm];
}

ArmData ArmManager::GetArmData(int _armID) {
	ArmData armData;

	for (auto d : generator->GetArmData()) {
		if (d["armID"] != _armID) continue;

		armData.armName = MyJson::Utf8ToString(d["armName"].get<std::string>());
		armData.atkValue = d["atkValue"];
		armData.spdValue = d["spdValue"] / 100;
		armData.staminaValue = d["cStmValue"];
		armData.strength = d["strength"];
		armData.durabirity = d["maxDurability"];
		armData.tips = MyJson::Utf8ToString(d["tips2"].get<std::string>());

		break;
	}

	return armData;
}
