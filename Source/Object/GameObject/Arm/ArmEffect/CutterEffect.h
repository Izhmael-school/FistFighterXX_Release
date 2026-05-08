#pragma once
#include "ArmEffectBase.h"
class CutterEffect : public ArmEffectBase {
public:
	void PlayerHit(Player* _target, ArmBase* _this) override;

	void ArmHit(ArmBase* _target, ArmBase* _this) override;

	void WallHit(ArmBase* _this, Collider* _wall) override;

	void ItemHit(ArmBase* _this) override;

private:
	float hitSpan = 0.1f;
	float lastHitTime = 0.0f;
};

