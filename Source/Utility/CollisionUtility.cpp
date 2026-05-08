#include "CollisionUtility.h"
#include "../Manager/CollisionManager.h"

void CollisionUtility::Update() {
	CollisionManager::GetInstance().Update();
}

void CollisionUtility::Render() {
	CollisionManager::GetInstance().Render();
}

void CollisionUtility::Register(Collider* _pCol) {
	CollisionManager::GetInstance().Register(_pCol);
}

void CollisionUtility::UnRegister(Collider* _pCol) {
	CollisionManager::GetInstance().UnRegister(_pCol);
}

void CollisionUtility::UnRegisterAll() {
	CollisionManager::GetInstance().UnRegisterAll();
}

