#include "ColliderObjectManager.h"
#include "../Object/ColliderObject/ColliderObject.h"
#include "../Component/Collider.h"

void ColliderObjectManager::Update() {
	for (auto& c : colliderObjectArray) {
		if (!c->IsActive()) continue;

		c->Update();
	}

	std::erase_if(colliderObjectArray, [](std::unique_ptr<ColliderObject>& _pC) {
		if (_pC->IsActive()) return false;

		_pC.reset();
		return true;
		});
}

void ColliderObjectManager::Register(std::unique_ptr<Collider>& _pCol, std::function<void(Collider* _pOhter)> _func, float _lifeTime, Tag _tag) {
	std::unique_ptr<ColliderObject> c = std::make_unique<ColliderObject>(_pCol, _func, _lifeTime, _tag);
	c->GetCollider()->SetOwner(c.get());
	colliderObjectArray.push_back(std::move(c));
}
