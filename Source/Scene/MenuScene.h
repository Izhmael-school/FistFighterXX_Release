#pragma once
#include "SceneBase.h"
#include <vector>
#include "../UI/Cursor/CursorInfo.h"
#include "../Game/GameCondition.h"
#include <array>
#include <memory>

class UIBase;

const unsigned int selectColor[2] = { white,yellow };
const int armPreset[ArmTypeMax] = { Punch,Drill,Star,Bomb,Cutter };

struct JoinSetting {
	int portNum;
	bool isJoin = false;
};

/// <summary>
/// メニューシーン
/// </summary>
class MenuScene : public SceneBase {
private:
	// 生成されたときに一度だけ呼ばれる
	void Start() override;
public:
	MenuScene();
	~MenuScene();

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
	void ChangeState(MenuSceneState _state);

	int ChoiceColor(int _portNum,int _colorNum);

	void RegistPlayer();

	void PlayerSetting();

	void DrawPlayerSetting();

	void DrawArmStatus();

	void DrawArmStatusWindow(int index,bool isLeft);
private:
	std::vector<std::vector<UIBase*>> uiArray;
	MenuSceneState currentMenuState;

	std::vector<JoinSetting> join;
	std::vector<BattleSetting> battle;

	int joinNum;

	int backGroundHandle;
	int buttonGraphHandle;
	int stageGraphHandle;

	// UIの座標やサイズ等
	int fontHandle;
	int superBoldFont;

	VECTOR buttonOffset;
	VECTOR buttonSize;
	VECTOR configUITextBasisPos;
	VECTOR joinMarkPos;

	VECTOR colorMarkPos;
	VECTOR leftArmMarkPos;
	VECTOR rightArmMarkPos;	

};

