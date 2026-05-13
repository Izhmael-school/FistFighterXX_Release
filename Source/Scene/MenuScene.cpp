#include "MenuScene.h"
#include "../Utility/InputUtility.h"
#include "../Utility/SceneUtility.h"
#include "../Manager/UIManager.h"
#include "../UI/Button/UIButton.h"
#include "../Utility/FontUtility.h"
#include "../Utility/ArmUtility.h"
#include "../Game/GameSystem.h"
#include "../UI/UIBase.h"
#include "../Other/CommonModule/MyString.h"
#include "../Other/CommonModule/MyDraw.h"
#include "../Other/CommonModule/MyMath.h"
#include "../Other/CommonModule/MyImage.h"
#include "../Utility/AudioUtility.h"
#include "../Object/Camera/Camera.h"
#include "../Other/MenuTips.h"
#include <algorithm>
#include <memory>

MenuScene::MenuScene()
	:buttonOffset(VGet(WINDOW_WIDTH - (WINDOW_WIDTH / 4), (WINDOW_HEIGHT / 4), 0))
	, fontHandle(FontUtility::UseFontHandle("MainFont_Bold"))
	, superBoldFont(FontUtility::UseFontHandle("Super_Bold"))
	, buttonSize(VGet(500, 250, 0))
	, currentMenuState(MenuInvalid)
	, configUITextBasisPos(VGet(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, 0))
	, joinMarkPos(VGet(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, 0))
	, joinNum(0)
	, colorMarkPos(VGet(WINDOW_WIDTH / 4, (WINDOW_HEIGHT / 4), 0))
	, leftArmMarkPos(VGet(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, 0))
	, rightArmMarkPos(VGet(WINDOW_WIDTH / 4, (WINDOW_HEIGHT / 4), 0)) {
	Start();
}

MenuScene::~MenuScene() {}

void MenuScene::Start() {
	uiArray.resize(MenuStateMax);
	join.resize(PLAYER_MAX);
	battle.resize(PLAYER_MAX);

	backGroundHandle = LoadGraph(MENU_SPRITE_PATH.data());
	buttonGraphHandle = LoadGraph(MENUBUTTON_SPRITE_PATH.data());
	stageGraphHandle = LoadGraph("res/Image/MenuScene/Stage/Stage1.png");

	AudioUtility::Load(MyString::MergeString(BGM_FILEPATH, "Menu/", "Menu", AUDIO_EXTENSION), "menu", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "MoveMenu", AUDIO_EXTENSION), "moveMenu", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "JoinPlayer", AUDIO_EXTENSION), "joinPlayer", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "RemovePlayer", AUDIO_EXTENSION), "removePlayer", false);

	std::unique_ptr<MenuTips> menuTips = std::make_unique<MenuTips>(0, 0, 0, 0);
	uiArray[MenuSelect].push_back(menuTips.get());
	UIManager::GetInstance().AddUI(Menu, std::move(menuTips));
	uiArray[MenuSelect].push_back(UIManager::GetInstance().CreateUIButton(Menu, buttonOffset.x, buttonOffset.y, buttonSize.x, buttonSize.y, [this] {ChangeState(MenuStageSelect); }, "対戦開始", white, red, fontHandle, 1, buttonGraphHandle));
	uiArray[MenuSelect].push_back(UIManager::GetInstance().CreateUIButton(Menu, buttonOffset.x, buttonOffset.y * 2, buttonSize.x, buttonSize.y, [this] {ChangeState(MenuConfig); }, "コンフィグ", white, red, fontHandle, 1, buttonGraphHandle));
	uiArray[MenuSelect].push_back(UIManager::GetInstance().CreateUIButton(Menu, buttonOffset.x, buttonOffset.y * 3, buttonSize.x, buttonSize.y, [] { GameSystem::SetEnd(true); }, "ゲームをやめる", white, red, fontHandle, 1, buttonGraphHandle));
	uiArray[MenuConfig].push_back(UIManager::GetInstance().CreateUIButton(Menu, 1690, 965, 380, 150, [this] {ChangeState(MenuSelect); }, "戻る", black, red, fontHandle, 1));
	uiArray[MenuConfig].push_back(UIManager::GetInstance().CreateUIButton(Menu, 1100, 400, 75, 75, [this] {AudioUtility::AddMasterVolume(-0.05f); }, "‐", black, red, fontHandle, 1));
	uiArray[MenuConfig].push_back(UIManager::GetInstance().CreateUIButton(Menu, 1100, 550, 75, 75, [this] {AudioUtility::AddBGMVolume(-0.05f); }, "‐", black, red, fontHandle, 1));
	uiArray[MenuConfig].push_back(UIManager::GetInstance().CreateUIButton(Menu, 1100, 700, 75, 75, [this] {AudioUtility::AddSEVolume(-0.05f); }, "‐", black, red, fontHandle, 1));
	uiArray[MenuConfig].push_back(UIManager::GetInstance().CreateUIButton(Menu, 1400, 400, 75, 75, [this] {AudioUtility::AddMasterVolume(0.05f); }, "＋", black, red, fontHandle, 1));
	uiArray[MenuConfig].push_back(UIManager::GetInstance().CreateUIButton(Menu, 1400, 550, 75, 75, [this] {AudioUtility::AddBGMVolume(0.05f); }, "＋", black, red, fontHandle, 1));
	uiArray[MenuConfig].push_back(UIManager::GetInstance().CreateUIButton(Menu, 1400, 700, 75, 75, [this] {AudioUtility::AddSEVolume(0.05f); }, "＋", black, red, fontHandle, 1));
	uiArray[MenuPlayerRegister].push_back(UIManager::GetInstance().CreateUIButton(Menu, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 200, 200, [this] {
		if (joinNum <= 1) return;
		GameCondition::SetJoinNum(joinNum);
		for (int i = 0; i < PLAYER_MAX; i++) {
			if (!join[i].isJoin) continue;
			battle[i].portNum = join[i].portNum;
			GameCondition::AddBattleSetting(battle[i]);
		}
		AudioUtility::PlayOneShot("moveMenu");
		SceneUtility::SetScene(MainGame);
		}, "GO!", black, red, fontHandle, 1));
	uiArray[MenuPlayerRegister].push_back(UIManager::GetInstance().CreateUIButton(Menu, 50, 25, 100, 50, [this] { ChangeState(MenuStageSelect); }, "←", black, red, fontHandle, 1));
	uiArray[MenuStageSelect].push_back(UIManager::GetInstance().CreateUIButton(Menu, 50, 25, 100, 50, [this] { ChangeState(MenuSelect); }, "←", black, red, fontHandle, 1));
	uiArray[MenuStageSelect].push_back(UIManager::GetInstance().CreateUIButton(Menu, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, 300, 200, [this] { GameCondition::SetStageNum(0), ChangeState(MenuPlayerRegister); }, "", black, red, fontHandle, 1, stageGraphHandle));

	ChangeState(MenuSelect);

}

void MenuScene::Update() {
	CursorInfo::Update();


	switch (currentMenuState) {
	case MenuSelect:
		break;
	case MenuPlayerRegister:
		// 登録
		RegistPlayer();

		// プレイヤーのウデ変更等
		PlayerSetting();

		break;
	case MenuConfig:
		break;
	default:
		break;
	}
}

void MenuScene::Render() {


	DrawGraph(0, 0, backGroundHandle, FALSE);


	switch (currentMenuState) {
	case MenuSelect:
		break;
	case MenuPlayerRegister:

		// プレイヤーの設定描画
		DrawPlayerSetting();

		// ウデの情報
		DrawArmStatus();

		// 仕切り線
		DrawLine(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, gray,5);
		DrawLine(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, gray,5);

		MyDraw::DrawStringCenterPos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8, 1.0f, 1.0f, "参加", black, superBoldFont, white);

		break;
	case MenuConfig:
		// 透過黒背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawFillBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, black);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, -1);

		MyDraw::DrawStringCenterPos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8, 1.5f, 1.5f, "コンフィグ", black, superBoldFont, white);
		MyDraw::DrawStringCenterPos(configUITextBasisPos.x, configUITextBasisPos.y - 150, 1.0f, 1.0f, "MasterVolume", black, fontHandle, white);
		MyDraw::DrawStringCenterPos(1250, configUITextBasisPos.y - 150, 1.0f, 1.0f, MyString::MergeString(std::to_string(static_cast<int>(AudioUtility::GetMasterVolume() * 100.0f)), "%").c_str(), black, fontHandle, white);

		MyDraw::DrawStringCenterPos(configUITextBasisPos.x, configUITextBasisPos.y, 1.0f, 1.0f, "BGMVolume", black, fontHandle, white);
		MyDraw::DrawStringCenterPos(1250, configUITextBasisPos.y, 1.0f, 1.0f, MyString::MergeString(std::to_string(static_cast<int>(AudioUtility::GetBGMVolume() * 100.0f)), "%").c_str(), black, fontHandle, white);

		MyDraw::DrawStringCenterPos(configUITextBasisPos.x, configUITextBasisPos.y + 150, 1.0f, 1.0f, "SEVolume", black, fontHandle, white);
		MyDraw::DrawStringCenterPos(1250, configUITextBasisPos.y + 150, 1.0f, 1.0f, MyString::MergeString(std::to_string(static_cast<int>(AudioUtility::GetSEVolume() * 100.0f)), "%").c_str(), black, fontHandle, white);

		break;
	case MenuStageSelect:
		MyDraw::DrawStringCenterPos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8, 1.0f, 1.0f, "ステージ選択", black, superBoldFont, white);
		break;
	}
}

void MenuScene::Setup() {
	for (int i = 0; i < PLAYER_MAX; i++) {
		join[i].isJoin = false;
		join[i].portNum = i;
	}
	joinNum = 0;
	GameCondition::ResetBattleSetting();

	AudioUtility::PlayBGM("menu", 125.0f);

	ChangeState(MenuSelect);
}

void MenuScene::Teardown() {
	AudioUtility::Stop("menu");
}

void MenuScene::DeleteData() {}

void MenuScene::ChangeState(MenuSceneState _state) {
	if (_state == currentMenuState) return;

	// 対応するUIの有効化
	for (int i = 0; i < MenuStateMax; i++) {
		for (auto& b : uiArray[i]) {
			if (static_cast<int>(_state) == i)
				b->SetActive(true);
			else
				b->SetActive(false);
		}
	}

	currentMenuState = _state;
}

int MenuScene::ChoiceColor(int _portNum, int _colorNum) {
	int index = 0;
	for (auto j : join) {
		if (j.portNum == _portNum) break;

		index++;
	}

	std::vector<int> otherPlayerColor;
	for (int i = 0; i < battle.size(); i++) {
		if (index == i || !join[i].isJoin) continue;

		// ほかのプレイヤーの色を保存
		otherPlayerColor.push_back(battle[i].color);
	}

	if (otherPlayerColor.size() == 0) return _colorNum;;

	while (true) {
		int j = 0;
		for (auto i : otherPlayerColor) {
			if (i == _colorNum) break;

			j++;

			// どのプレイヤーとも被らなければ
			if (otherPlayerColor.size() == j)
				return _colorNum;
		}

		int moveDir = std::clamp(_colorNum - battle[index].color, -1, 1);
		if (moveDir == 0) moveDir = 1;
		_colorNum += moveDir;

		// 変えれる色が無ければそのままで返す
		if (_colorNum == -1 || _colorNum == PLAYER_COLOR_MAX)
			return battle[index].color;
	}

}

void MenuScene::RegistPlayer() {
	for (int i = 0; i < PLAYER_MAX; i++) {
		if (InputUtility::IsPadDown(join[i].portNum, XINPUT_BUTTON_X) && !join[i].isJoin) {
			joinNum++;
			battle[i].color = ChoiceColor(i, 0);
			join[i].isJoin = true;
			AudioUtility::PlayOneShot("joinPlayer");
		}
		else if (InputUtility::IsPadDown(join[i].portNum, XINPUT_BUTTON_B) && join[i].isJoin) {
			joinNum--;
			join[i].isJoin = false;
			AudioUtility::PlayOneShot("removePlayer");
		}
	}
}

void MenuScene::PlayerSetting() {
	for (int i = 0; i < PLAYER_MAX; i++) {
		if (InputUtility::IsPadDown(i, XINPUT_BUTTON_DPAD_DOWN))
			battle[i].currentSelect = std::clamp(battle[i].currentSelect + 1, 0, 2);
		if (InputUtility::IsPadDown(i, XINPUT_BUTTON_DPAD_UP))
			battle[i].currentSelect = std::clamp(battle[i].currentSelect - 1, 0, 2);

		switch (battle[i].currentSelect) {
		case 0:
			if (InputUtility::IsPadDown(i, XINPUT_BUTTON_DPAD_LEFT))
				battle[i].color = ChoiceColor(i, std::clamp(battle[i].color - 1, 0, 7));
			if (InputUtility::IsPadDown(i, XINPUT_BUTTON_DPAD_RIGHT))
				battle[i].color = ChoiceColor(i, std::clamp(battle[i].color + 1, 0, 7));
			break;
		case 1:
			if (InputUtility::IsPadDown(i, XINPUT_BUTTON_DPAD_LEFT))
				battle[i].left = static_cast<ArmType>(std::clamp(battle[i].left - 1, 0, static_cast<int>(ArmTypeMax - 1)));
			if (InputUtility::IsPadDown(i, XINPUT_BUTTON_DPAD_RIGHT))
				battle[i].left = static_cast<ArmType>(std::clamp(battle[i].left + 1, 0, static_cast<int>(ArmTypeMax - 1)));
			break;
		case 2:
			if (InputUtility::IsPadDown(i, XINPUT_BUTTON_DPAD_LEFT))
				battle[i].right = static_cast<ArmType>(std::clamp(battle[i].right - 1, 0, static_cast<int>(ArmTypeMax - 1)));
			if (InputUtility::IsPadDown(i, XINPUT_BUTTON_DPAD_RIGHT))
				battle[i].right = static_cast<ArmType>(std::clamp(battle[i].right + 1, 0, static_cast<int>(ArmTypeMax - 1)));
			break;
		}
	}
}

void MenuScene::DrawPlayerSetting() {
	int index = 0;

	for (int y = 0; y <= 2; y += 2) {
		for (int x = 0; x <= 2; x += 2) {
			if (join[index].isJoin) {
				float px, py;
				float fx, fy;
				float graphSize = 0.7f;
				float space = 300;
				DrawFillBox(x * (WINDOW_WIDTH / 4), y * (WINDOW_HEIGHT / 4), (x + 2) * (WINDOW_WIDTH / 4), (y + 2) * (WINDOW_HEIGHT / 4), colorPreset[battle[index].color]);
				MyDraw::DrawStringCenterPos((WINDOW_WIDTH / 4) * (x + 1), (WINDOW_HEIGHT / 8) * ((y * 2) + 1), 1.0f, 1.0f, "カラー", selectColor[battle[index].currentSelect == 0 ? 1 : 0], fontHandle, black);
				px = fx = colorMarkPos.x * (x + 1) - space;
				py = fy = colorMarkPos.y * (y + 1) + 100;
				MyDraw::DrawStringCenterPos(fx + 100, fy + 50, 1.0f, 1.0f, "ヒダリウデ", selectColor[battle[index].currentSelect == 1 ? 1 : 0], fontHandle, black);
				MyDraw::DrawExtendGraphCenterPos(px, py, ArmUtility::GetArmGraphHandle(battle[index].left), -graphSize, graphSize);
				px = fx = colorMarkPos.x * (x + 1) + space;
				MyDraw::DrawStringCenterPos(fx - 100, fy + 50, 1.0f, 1.0f, "ミギウデ", selectColor[battle[index].currentSelect == 2 ? 1 : 0], fontHandle, black);
				MyDraw::DrawExtendGraphCenterPos(px, py, ArmUtility::GetArmGraphHandle(battle[index].right), graphSize, graphSize);
			}
			else {
				DrawFillBox(x * (WINDOW_WIDTH / 4), y * (WINDOW_HEIGHT / 4), (x + 2) * (WINDOW_WIDTH / 4), (y + 2) * (WINDOW_HEIGHT / 4), gray);
				DrawString(joinMarkPos.x * (x + 1), joinMarkPos.y * (y + 1), "Xで参加!", red);
			}


			index++;
		}
	}
}

void MenuScene::DrawArmStatus() {
	for (int i = 0; i < PLAYER_MAX; i++) {
		// 未参加かウデを選択してなければ次
		if (!join[i].isJoin || battle[i].currentSelect == 0) continue;

		bool isLeft = battle[i].currentSelect == 1 ? true : false;

		DrawArmStatusWindow(i, isLeft);
	}
}

void MenuScene::DrawArmStatusWindow(int index, bool isLeft) {
	int x = (isLeft ? 550 : 150) + (index % 2 != 0 ? 960 : 0);
	int y = 100 + (index > 1 ? 540 : 0);

	int windowWidth = 300;
	int windowHeight = 400;

	// 黒背景
	DrawFillBox(x, y, x + windowWidth, y + windowHeight, black);
	DrawLineBox(x, y, x + windowWidth, y + windowHeight, white);
	ArmType arm = isLeft ? battle[index].left : battle[index].right;

	ArmData data = ArmUtility::GetArmData(arm);

	int nameFont = FontUtility::UseFontHandle("StatusFont_Name");
	int textFont = FontUtility::UseFontHandle("StatusFont_Text");

	unsigned int userColor = battle[index].color;

	MyDraw::DrawStringCenterPos(x + (windowWidth / 2), y + 30, 1, 1, data.armName.c_str(), white, nameFont, userColor);

	MyDraw::DrawStringCenterPos(x + (windowWidth / 2), y + 120, 1, 1, MyString::MergeString("攻撃力：", std::to_string(data.atkValue)).c_str(), white, textFont, userColor);
	MyDraw::DrawStringCenterPos(x + (windowWidth / 2), y + 160, 1, 1, MyString::MergeString("移動速度：", std::to_string(data.spdValue)).c_str(), white, textFont, userColor);
	MyDraw::DrawStringCenterPos(x + (windowWidth / 2), y + 200, 1, 1, MyString::MergeString("スタミナ消費量：", std::to_string(data.staminaValue)).c_str(), white, textFont, userColor);
	MyDraw::DrawStringCenterPos(x + (windowWidth / 2), y + 240, 1, 1, MyString::MergeString("体力：", std::to_string(data.durabirity)).c_str(), white, textFont, userColor);
	MyDraw::DrawStringCenterPos(x + (windowWidth / 2), y + 280, 1, 1, MyString::MergeString("対抗力：", std::to_string(data.strength)).c_str(), white, textFont, userColor);
	MyDraw::DrawStringCenterPos(x + (windowWidth / 2), y + 320, 1, 1, MyString::MergeString("特殊能力：", data.tips).c_str(), white, textFont, userColor);
}
