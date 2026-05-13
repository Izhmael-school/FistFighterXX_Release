#include "ArmEffectBase.h"
#include "../../Character/Player/Player.h"
#include "../ArmBase.h"
#include "../../../../Component/Collider.h"
#include "../../../../Other/CommonModule/MyVECTOR.h"


void ArmEffectBase::PlayerHit(Player* _target, ArmBase* _this) {
	// 当たったのがウデの持ち主なら帰る
	if (_this->GetOwner() == _target) return;

	_target->SubHP(_this->GetAttackValue());

	_this->ShotEnd();
}

void ArmEffectBase::ArmHit(ArmBase* _target, ArmBase* _this) {
	// 持ち主が同じかどちらかがが発射して無ければ帰る
	if (_target->GetOwner() == _this->GetOwner() || !_target->IsShot() || !_this->IsShot()) return;

	_target->SubDurability(_this->GetStrength());
	_this->SubDurability(_target->GetStrength());

	if (_target->GetCurrentDurability() <= 0)
	// 耐久力が無くなったらショットを終わらす
	_target->ShotEnd();

	if (_this->GetCurrentDurability() <= 0)
	// 耐久力が無くなったらショットを終わらす
	_this->ShotEnd();
}

void ArmEffectBase::WallHit(ArmBase* _this, Collider* _wall) {
	SphereCollider* sph = static_cast<SphereCollider*>(_this->GetCollider());
	BoxCollider* box = static_cast<BoxCollider*>(_wall);

	VECTOR min = box->GetMinPoint();
	VECTOR max = box->GetMaxPoint();
	VECTOR center = sph->GetCenter();

	VECTOR closest;
	// ウデから見て一番近いBoxの点を探す
	closest.x = std::clamp(center.x, min.x, max.x);
	closest.y = std::clamp(center.y, min.y, max.y);
	closest.z = std::clamp(center.z, min.z, max.z);

	// 最近点のベクトル
	VECTOR vec = VSub(center, closest);
	// 中心までの距離
	float dis = VSize(vec);
	float radius = sph->GetRadius();
	if (dis > radius) return;

	// めり込んでる量
	float penetration = radius - dis;
	VECTOR dir = VNorm(vec);
	VECTOR pos = VScale(dir, penetration);
	_this->GetTransform().AddPosition(pos);
}

void ArmEffectBase::ItemHit( ArmBase* _this) {
	// ショットを終わらす
	_this->ShotEnd();
}

void ArmEffectBase::ShotEnd(ArmBase* _this) {}
