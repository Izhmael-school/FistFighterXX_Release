#include "ColliderObjectUtility.h"
#include "../Manager/ColliderObjectManager.h"
#include "../Component/Collider.h"
#include "../Object/ColliderObject/ColliderObject.h"

void ColliderObjectUtility::Update() {
	ColliderObjectManager::GetInstance().Update();
}

void ColliderObjectUtility::Register(std::unique_ptr<Collider> _pCol, float _lifeTime, std::function<void(Collider* _pOhter)> _func, Tag _tag) {
	ColliderObjectManager::GetInstance().Register(_pCol,_func,_lifeTime,_tag);
}
