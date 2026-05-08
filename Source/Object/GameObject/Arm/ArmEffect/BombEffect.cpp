#include "BombEffect.h"
#include "../../Character/Player/Player.h"
#include "../ArmBase.h"
#include "../../../../Utility/AudioUtility.h"
#include "../../../../Utility/EffectUtility.h"
#include "../../../../Utility/ColliderObjectUtility.h"
#include "../../../../Component/Collider.h"
#include <memory>

void BombEffect::PlayerHit(Player* _target, ArmBase* _this) {
	// 当たったのがウデの持ち主なら帰る
	if (_this->GetOwner() == _target) return;

	_this->ShotEnd();
}

void BombEffect::ArmHit(ArmBase* _target, ArmBase* _this) {
	// 持ち主が同じなら帰る
	if (_target->GetOwner() == _this->GetOwner()) return;

	_target->SubDurability(_this->GetStrength());

	if (_target->GetCurrentDurability() <= 0) 
	// 耐久力が無くなったらショットを終わらす
	_target->ShotEnd();
}

void BombEffect::WallHit(ArmBase* _this, Collider* _wall) {
	ArmEffectBase::WallHit(_this, _wall);

	_this->ShotEnd();
}

void BombEffect::ItemHit(ArmBase* _this) {
	ArmEffectBase::ItemHit(_this);

	_this->ShotEnd();
}

void BombEffect::ShotEnd(ArmBase* _this) {
	// 広範囲の爆発
	float time = _this->GetShotTime();
	ColliderObjectUtility::Register(std::make_unique<SphereCollider>(nullptr, _this->GetPosition(), 500), 0.5f,
		[_this, time](Collider* _pOther) {
			if (_pOther->GetTag() == PlayerCharacter) {
				Player* p = static_cast<Player*>(_pOther->GetOwner());
				p->SubHP(_this->GetBaseAttackValue() * time);
			}
			_this->ShotEnd();
		});

	AudioUtility::PlayOneShot("HitBomb");
	EffectUtility::Instantiate("HitBomb", _this->GetPosition());
}
