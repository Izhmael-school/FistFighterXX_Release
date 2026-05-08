#include "PunchEffect.h"
#include "../../Character/Player/Player.h"
#include "../../../../Utility/AudioUtility.h"
#include "../../../../Utility/EffectUtility.h"
#include "../ArmBase.h"

void PunchEffect::PlayerHit(Player* _target, ArmBase* _this) {
	ArmEffectBase::PlayerHit(_target,_this);

	if (_this->GetOwner() == _target) return;

	AudioUtility::PlayOneShot("HitPunch");
	EffectUtility::Instantiate("HitPunch", _this->GetPosition());
}

void PunchEffect::ArmHit(ArmBase* _target, ArmBase* _this) {
	ArmEffectBase::ArmHit(_target,_this);
}

void PunchEffect::WallHit(ArmBase* _this, Collider* _wall) {
	ArmEffectBase::WallHit(_this,_wall);
}

void PunchEffect::ItemHit(ArmBase* _this) {
	ArmEffectBase::ItemHit(_this);
}
