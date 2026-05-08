#pragma once
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include <memory>
#include <vector>
#include "../Definition.h"
#include <functional>

class ColliderObject;
class Collider;

class ColliderObjectManager : public Singleton<ColliderObjectManager>,public ManagerBase {
public:
	ColliderObjectManager() = default;
	~ColliderObjectManager() = default;

public:
	void Update() override;

	void Register(std::unique_ptr<Collider>& _pCol, std::function<void(Collider* _pOhter)> _func, float _lifeTime, Tag _tag = NoTag);

private:
	std::vector<std::unique_ptr<ColliderObject>> colliderObjectArray;
};

