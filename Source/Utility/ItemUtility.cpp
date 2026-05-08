#include "ItemUtility.h"
#include "../Manager/ItemManager.h"

void ItemUtility::Update() {
	ItemManager::GetInstance().Update();
}

void ItemUtility::Render() {
	ItemManager::GetInstance().Render();
}

ItemBase* ItemUtility::Use(int _id, VECTOR _pos) {
	return ItemManager::GetInstance().Use(_id,_pos);
}

void ItemUtility::UnuseAll() {
	ItemManager::GetInstance().UnuseAll();
}

void ItemUtility::DeleteData() {
	ItemManager::GetInstance().DeleteData();
}