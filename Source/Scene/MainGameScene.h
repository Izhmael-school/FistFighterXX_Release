#pragma once
#include "SceneBase.h"
#include "../Other/Utility/Span.h"
#include <vector>
#include <string>

class Camera;
class Player;
class StageBase;
class UIBase;

const unsigned int poseSelectColor[2] = { white,yellow };

/// <summary>
/// メインゲームシーン
/// </summary>
class MainGameScene : public SceneBase {
private:
	// 生成されたときに一度だけ呼ばれる
	void Start() override;
public:
	MainGameScene();
	~MainGameScene();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
	// 使用前初期化
	void Setup() override;
	// 使用後後処理
	void Teardown() override;

	void DeleteData() override;
private:
	void ChangeState(GameSceneState _state);

private:
	Player* pPlayer;
	int testModel;
	StageBase* test;
	bool isCameraMove;
	bool beforeGameStart;

	float gameTimer;

	GameSceneState currentGameState;

	Span gameStart;
	Span go;
	Span returnMenu;
	Span gameEnd;

	int resultFont;

	int pushStopPlayerNum;

	int currentSelectGameStop;

	bool isPlayGameSetSE;
	bool isPlayWinSE;

	std::vector<std::string> battleBGMList;
	std::string currentBGMName;
};

