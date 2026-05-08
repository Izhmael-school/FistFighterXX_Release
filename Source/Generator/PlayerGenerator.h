#pragma once
#include <memory>

class Player;
#define PLAYER_MODEL_FILEPATH(x) ("res/Model/Character/Player/" x ".mv1")
class PlayerGenerator {
private:
	void Start();

public:
	PlayerGenerator();
	~PlayerGenerator();

	// モデルの読み込み
	void LoadModel();

	// 生成
	std::unique_ptr<Player> Create();

	// モデルハンドルの削除
	void DeleteOriginModelHandle();
private:
	int originPlayerMHandle;
};

