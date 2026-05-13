#pragma once
#include "../Data/json.hpp"
#include "../Definition.h"
#include <memory>
#include <vector>

class ArmBase;
class Player;
class ArmEffectBase;

class ArmGenerator {
private:
	void Start();

	std::unique_ptr<ArmEffectBase> ReturnEffect(ArmType _type);
public:
	ArmGenerator();
	~ArmGenerator() = default;

	// モデルの読み込み
	void LoadArmModel();

	// 生成
	std::unique_ptr<ArmBase> CreateArm(ArmType _type,Player* _owner);

	// モデルハンドルの削除
	void DeleteOriginModelHandle();

	inline nlohmann::json_abi_v3_12_0::json GetArmData() { return armData; }

private:
	// 読み取ったデータ
	nlohmann::json_abi_v3_12_0::json armData;
	// ここからモデルを複製する
	std::vector<int> originArmModelHandle;
};

