#pragma once
#include "../GameObject.h"
#include "../../../Definition.h"

class Collider;
class Player;

struct ItemData {
	int id;
	ItemEffectType p_effectType;
	ItemEffectType a_effectType;
	int value;
};

struct HitResult {
	class Player* _target;
	ArmPos pos;
};

class ItemBase : public GameObject {
public:
	ItemBase(int mHandle,ItemData _data,int _spawnPointNum = -1);
	~ItemBase();

private:
	void Start() override;

public:
	void OnTriggerEnter(Collider* _pOther) override;

	void Update() override;
	void Render() override;
	void Setup() override;
	void Teardown() override;

	void EffectExcute(ItemEffectType _type);

	inline int GetItemID() const { return data.id; }

	inline void SetSpawnPointNum(int _spawnPointNum) { spawnPointNum = _spawnPointNum; }
private:
	ItemData data;
	HitResult result;
	float maxLifeTime;
	float currentLifeTime;
	int spawnPointNum;
};

