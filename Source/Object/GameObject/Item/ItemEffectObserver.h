#pragma once
#include "../../../Definition.h"

class Player;
class ItemBase;

class ItemEffectObserver {
public:
	ItemEffectObserver() = default;
	~ItemEffectObserver() = default;

	static void HPHeal(Player* _target,int _v);
	static void StaminaHeal(Player* _target,int _v);
	static void ArmChange(Player* _target,ArmPos _pos, ArmType _type);

};

