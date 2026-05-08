#include "ItemGenerator.h"
#include "../Other/CommonModule/MyJson.h"
#include "../Definition.h"
#include "../Object/GameObject/Item/ItemBase.h"
#include "../Other/CommonModule/MyString.h"
#include <cassert>
#include <string>

void ItemGenerator::LoadItemData() {
	itemData = MyJson::LoadJsonFile(ITEMDATA_FILEPATH.data());

	assert(!itemData.empty() && "ItemDataが無い");

	// モデルデータのロード
	for (auto i : itemData) {
		std::string filePath = MyString::MergeString(ITEMMODEL_FILEPATH, i["modelFileName"], MODEL_FILE_EXTENSION);
		int m = MV1LoadModel(filePath.c_str());
		// モデルが見つからなかったら警告
		assert(m != -1 && "モデルが無い");
		originItemModelArray.push_back(m);
	}
}

std::unique_ptr<ItemBase> ItemGenerator::CreateItem(int _id) {
	
	// データがなければ読み込み
	if (itemData.empty())
		LoadItemData();

	ItemData data;

	for (auto i : itemData) {
		if (i["itemID"] != _id) continue;
		data.id = i["itemID"];
		data.p_effectType = i["p_EffectID"];
		data.a_effectType = i["a_EffectID"];
		data.value = i["value"];
		break;
	}

	int m = MV1DuplicateModel(originItemModelArray[_id]);
	// 複製に失敗したら
	assert(m != -1);

	std::unique_ptr<ItemBase> item = std::make_unique<ItemBase>(m, data);

	return std::move(item);
}