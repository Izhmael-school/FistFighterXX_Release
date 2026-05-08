#pragma once
#include "../Data/json.hpp"
#include <vector>

class ItemBase;
class ItemData;

class ItemGenerator {
public:
	// 外部ファイルからデータの読み込み
	void LoadItemData();
	// アイテムの生成
	std::unique_ptr<ItemBase> CreateItem(int _id);

private:
	// 読み取ったデータ
	nlohmann::json_abi_v3_12_0::json itemData;
	// ここからモデルを複製する
	std::vector<int> originItemModelArray;
};

