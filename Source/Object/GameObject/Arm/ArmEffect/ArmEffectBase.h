#pragma once
#include <string>

class Player;
class ArmBase;
class Collider;

class ArmEffectBase {
public:
	virtual void PlayerHit(Player* _target,ArmBase* _this);

	virtual void ArmHit(ArmBase* _target,ArmBase* _this);

	virtual void WallHit(ArmBase* _this , Collider* _wall);

	virtual void ItemHit(ArmBase* _this);

	virtual void ShotEnd(ArmBase* _this);
};

