#pragma once
#include "../Component/Singleton.h"
#include "../Definition.h"
#include "ManagerBase.h"
#include <memory>
#include <vector>
#include <array>

class ItemGenerator;
class ItemBase;

class ItemManager : public Singleton<ItemManager>,public ManagerBase {
private:
	std::unique_ptr<ItemGenerator> generator;
	std::vector<std::unique_ptr<ItemBase>> useItemArray;
	std::vector<std::vector<std::unique_ptr<ItemBase>>> unuseItemArray;

	bool isSpawn;
public:
	ItemManager();
	~ItemManager();

private:
	void Start() override;
	void Unuse(ItemBase* _item);
	void CreateItem(int _id);

public:
	void Update() override;
	void Render() override;
	void DeleteData() override;
	void UnuseAll();

	ItemBase* Use(int _id, VECTOR _pos = VZero);
};

