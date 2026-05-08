#include "ItemEffectObserver.h"
#include "../Character/Player/Player.h"
#include "../Arm/ArmBase.h"
#include "../../../Utility/AudioUtility.h"

void ItemEffectObserver::HPHeal(Player* _target, int _v) {
	_target->AddHP(_v);
	AudioUtility::PlayOneShot("HPHeal");
}

void ItemEffectObserver::StaminaHeal(Player* _target, int _v) {
	_target->AddStamina(_v);
	AudioUtility::PlayOneShot("StaminaHeal");
}

void ItemEffectObserver::ArmChange(Player* _target, ArmPos _pos, ArmType _type) {
	_target->ChangeArm(_pos, _type);
	AudioUtility::PlayOneShot("ChangeArm");
}

