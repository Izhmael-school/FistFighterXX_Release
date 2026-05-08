#pragma once
#include <memory>
#include <vector>
#include <string_view>


class StageBase;

constexpr int STAGE_NUM = 3;

constexpr std::string_view STAGE_FILENAME[STAGE_NUM] = {
	"Stage1",
	"Stage2",
	"Stage3"
};

constexpr std::string_view STAGE_FILEPATH = "res/Model/Stage/";

class StageGenerator {
public:
	StageGenerator();
	~StageGenerator() = default;

public:
	// モデルの読み込み
	void LoadModel();

	// 生成
	std::unique_ptr<StageBase> Create(int _stageNum);

	// モデルハンドルの削除
	void DeleteOriginModelHandle();

private:
	std::vector<int> originModelHandleArray;
};

