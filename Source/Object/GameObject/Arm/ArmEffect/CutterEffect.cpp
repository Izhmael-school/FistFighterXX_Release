#include "CutterEffect.h"
#include "../../Character/Player/Player.h"
#include "../ArmBase.h"
#include "../../../../Utility/AudioUtility.h"
#include "../../../../Utility/TimeUtility.h"
#include "../../../../Utility/EffectUtility.h"
#include "../ArmBase.h"


void CutterEffect::PlayerHit(Player* _target, ArmBase* _this) {
	// “–‚½‚Á‚½‚Ì‚ªƒEƒf‚ÌŽ‚¿Žå‚È‚ç‹A‚é
	if (_this->GetOwner() == _target) return;

	if (hitSpan <= lastHitTime) {
		_target->SubHP(_this->GetAttackValue());
		AudioUtility::PlayOneShot("HitCutter");
		EffectUtility::Instantiate("HitCutter", _this->GetPosition());
		lastHitTime = 0.0f;
	}
	else {
		lastHitTime += TimeUtility::GetDeltaTime();
	}
}

void CutterEffect::ArmHit(ArmBase* _target, ArmBase* _this) {
	ArmEffectBase::ArmHit(_target, _this);
}

void CutterEffect::WallHit(ArmBase* _this, Collider* _wall) {
	ArmEffectBase::WallHit(_this, _wall);
}

void CutterEffect::ItemHit(ArmBase* _this) {
	ArmEffectBase::ItemHit(_this);
}