#include "ItemManager.h"
#include "../Generator/ItemGenerator.h"
#include "../Object/GameObject/Item/ItemBase.h"
#include "../Game/MainGameTimer.h"
#include "../Utility/StageUtility.h"
#include "../Utility/AudioUtility.h"
#include "../Utility/EffectUtility.h"
#include "../Object/GameObject/Stage/StageBase.h"
#include "../Other/CommonModule/MyMath.h"
#include "../Other/CommonModule/MyVECTOR.h"
#include "../Other/CommonModule/MyString.h"

ItemManager::ItemManager()
	:generator()
	, unuseItemArray{}
	, useItemArray{}
	, isSpawn(false) {
	Start();
}

ItemManager::~ItemManager() {}

void ItemManager::Start() {
	generator = std::make_unique<ItemGenerator>();
	generator->LoadItemData();
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "HPHeal", AUDIO_EXTENSION), "HPHeal", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "StaminaHeal", AUDIO_EXTENSION), "StaminaHeal", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "ChangeArm", AUDIO_EXTENSION), "ChangeArm", false);
	EffectUtility::Load(MyString::MergeString(EFFECTMODEL_FILEPATH, "ItemSpawnEffect", EFFECT_FILE_EXTENSION), "ItemSpawn", 50.0f);
}

void ItemManager::Update() {
	// 非表示のものを参照
	std::vector<ItemBase*> deleteBox;

	if (MainGameTimer::GetGameTime() % 10 == 0 && MainGameTimer::GetGameTime() != 0 && !isSpawn) {
		int rand = MyMath::Random(0, ITEM_NUM - 1);
		int spawnPointNum = -1;
		ItemBase* item = Use(rand, StageUtility::GetCurrentStage()->GetRandomItemSpawnPoint(spawnPointNum));
		if (spawnPointNum != -1)
			item->SetSpawnPointNum(spawnPointNum);
		isSpawn = true;
	}

	if (MainGameTimer::GetGameTime() % 10 != 0 && isSpawn)
		isSpawn = false;

	for (auto& i : useItemArray) {
		i->Update();

		if (i->IsVisible()) continue;

		deleteBox.push_back(i.get());
	}

	// 非表示のものを未使用配列に移す
	for (auto& i : deleteBox) {
		Unuse(i);
	}
}

void ItemManager::Render() {
	for (auto& i : useItemArray) {
		i->Render();
	}
}

ItemBase* ItemManager::Use(int _id, VECTOR _pos) {
	if (MyVECTOR::CompareVECTORToEqual(_pos, VMinus)) return nullptr;

	// サイズが小さかったらその分追加する
	if (unuseItemArray.size() <= _id)
		unuseItemArray.resize(_id + 1);

	// 無ければ作る
	if (unuseItemArray[_id].empty())
		CreateItem(_id);

	std::unique_ptr<ItemBase> item = std::move(unuseItemArray[_id].back());
	unuseItemArray[_id].pop_back();

	item->Setup();

	item->GetTransform().SetPosition(_pos);
	item->GetTransform().AddPosition(VScale(VUp, 100));

	useItemArray.push_back(std::move(item));

	EffectUtility::Instantiate("ItemSpawn", _pos);

	return useItemArray.back().get();
}

void ItemManager::Unuse(ItemBase* _item) {
	int _id = _item->GetItemID();

	// 配列の中から同じもののunique_ptrを参照
	auto itr = std::find_if(useItemArray.begin(), useItemArray.end(), [_item](const std::unique_ptr<ItemBase>& i) {return i.get() == _item; });

	// 無ければ帰る
	if (itr == useItemArray.end()) return;

	(*itr)->Teardown();

	unuseItemArray[_item->GetItemID()].push_back(std::move((*itr)));
	useItemArray.erase(itr);
}

void ItemManager::UnuseAll() {
	for (int i = 0; useItemArray.size() != i;) {
		std::unique_ptr<ItemBase> item = std::move(useItemArray[i]);
		useItemArray.erase(useItemArray.begin());
		item->Teardown();
		unuseItemArray[item->GetItemID()].push_back(std::move(item));
	}
}

void ItemManager::CreateItem(int _id) {
	unuseItemArray[_id].push_back(generator->CreateItem(_id));
}

void ItemManager::DeleteData() {
	for (auto& i : useItemArray) {
		i->DeleteModel();
	}
	for (auto& itemArray : unuseItemArray) {
		for (auto& i : itemArray) {
			i->DeleteModel();
		}
	}
}