#pragma once
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include <vector>
#include <unordered_set>
#include <array>

class Collider;

struct CollisionResult {
	bool prev = false;
	bool current = false;
};

class CollisionManager : public Singleton<CollisionManager>, public ManagerBase {
private:
	std::vector<Collider*> pColliderArray;
	std::vector<std::vector<CollisionResult>> result;
private:
	bool CheckHit(Collider* _pCol1, Collider* _pCol2);

public:
	CollisionManager();
	~CollisionManager();

	void Update() override;
	void Render() override;

	void Register(Collider* _pCol);
	
	void UnRegister(Collider* _pCol);
	void UnRegisterAll();

};

