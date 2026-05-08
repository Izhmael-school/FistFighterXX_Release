#pragma once
#include "ArmEffectBase.h"


class DrillEffect : public ArmEffectBase {
public:
	void PlayerHit(Player* _target, ArmBase* _this) override;

	void ArmHit(ArmBase* _target, ArmBase* _this) override;

	void WallHit(ArmBase* _this, Collider* _wall) override;

	void ItemHit(ArmBase* _this) override;
};

