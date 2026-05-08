#include "StarEffect.h"
#include "../../../../Utility/AudioUtility.h"
#include "../../../../Utility/EffectUtility.h"
#include "../ArmBase.h"

void StarEffect::PlayerHit(Player* _target, ArmBase* _this) {
	ArmEffectBase::PlayerHit(_target, _this);

	if (_this->GetOwner() == _target) return;

	AudioUtility::PlayOneShot("HitStar");
	EffectUtility::Instantiate("HitStar", _this->GetPosition());
}

void StarEffect::ArmHit(ArmBase* _target, ArmBase* _this) {
	ArmEffectBase::ArmHit(_target, _this);
}

void StarEffect::WallHit(ArmBase* _this,Collider* _wall) {
	ArmEffectBase::WallHit(_this,_wall);
}

void StarEffect::ItemHit(ArmBase* _this) {
	ArmEffectBase::ItemHit(_this);
}
