#pragma once
#include "ArmEffectBase.h"
#include "../../Character/Player/Player.h"
#include "../ArmBase.h"

class PunchEffect : public ArmEffectBase {
public:
	void PlayerHit(Player* _target, ArmBase* _this) override;

	void ArmHit(ArmBase* _target, ArmBase* _this) override;

	void WallHit(ArmBase* _this, Collider* _wall) override;

	void ItemHit(ArmBase* _this) override;
};

