#include "DrillEffect.h"
#include "../../../../Utility/AudioUtility.h"
#include "../../../../Utility/EffectUtility.h"
#include "../ArmBase.h"
#include "../../../Effect/Effect.h"
#include "../../../../Component/Collider.h"

void DrillEffect::PlayerHit(Player* _target, ArmBase* _this) {
	ArmEffectBase::PlayerHit(_target, _this);

	if (_this->GetOwner() == _target) return;

	AudioUtility::PlayOneShot("HitDrill");
	Effect* e = EffectUtility::Instantiate("HitDrill", _this->GetPosition());
	e->GetTransform().SetRotation(_this->GetRotation());
}

void DrillEffect::ArmHit(ArmBase* _target, ArmBase* _this) {
	ArmEffectBase::ArmHit(_target, _this);
}

void DrillEffect::WallHit(ArmBase* _this, Collider* _wall) {
	// •ÇŠÑ’Ê‚·‚é
	if (_wall->GetTag() == UnmovingWall)
		ArmEffectBase::WallHit(_this, _wall);
}

void DrillEffect::ItemHit(ArmBase* _this) {
	ArmEffectBase::ItemHit(_this);
}
