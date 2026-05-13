#include "MainGameScene.h"
#include "../Utility/InputUtility.h"
#include "../Utility/SceneUtility.h"
#include "../Utility/PlayerUtility.h"
#include "../Utility/CollisionUtility.h"
#include "../Utility/ItemUtility.h"
#include "../Utility/EffectUtility.h"
#include "../Utility/FontUtility.h"
#include "../Utility/TimeUtility.h"
#include "../Utility/ArmUtility.h"
#include "../Utility/StageUtility.h"
#include "../Utility/AudioUtility.h"
#include "../Utility/ColliderObjectUtility.h"
#include "../Object/Camera/Camera.h"
#include "../Object/GameObject/Character/Player/Player.h"
#include "../Object/GameObject/Stage/StageBase.h"
#include "../Game/GameCondition.h"
#include "../Game/MainGameTimer.h"
#include "../Other/CommonModule/MyString.h"
#include "../Other/CommonModule/MyMath.h"
#include "../Other/CommonModule/MyDraw.h"
#include "../Manager/UIManager.h"
#include "EffekseerForDXLib.h"
#include "../UI/UIBase.h"
#include "../Object/GameObject/Arm/ArmBase.h"

MainGameScene::MainGameScene()
	:isCameraMove(false)
	, returnMenu()
	, beforeGameStart(true)
	, gameTimer(180.0f)
	, currentSelectGameStop(0)
	, isPlayGameSetSE(false)
	, isPlayWinSE(false)
	, resultFont(FontUtility::UseFontHandle("Super_Bold")) {
	Start();
}

MainGameScene::~MainGameScene() {}

void MainGameScene::Start() {
	returnMenu.SetTargetTime(3.0f);
	gameEnd.SetTargetTime(2.0f);
	gameStart.SetTargetTime(3.0f);
	go.SetTargetTime(2.0f);

	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "GameStart", AUDIO_EXTENSION), "gameStart", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "GameSet", AUDIO_EXTENSION), "gameSet", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "WinResultSE", AUDIO_EXTENSION), "win", false);
	AudioUtility::Load(MyString::MergeString(SE_FILEPATH, "OpenPose", AUDIO_EXTENSION), "OpenPose", false);

	AudioUtility::Load(MyString::MergeString(BGM_FILEPATH, "MainGame/", "Game1", AUDIO_EXTENSION), "game1", false);
	AudioUtility::Load(MyString::MergeString(BGM_FILEPATH, "MainGame/", "Game2", AUDIO_EXTENSION), "game2", false);
	AudioUtility::Load(MyString::MergeString(BGM_FILEPATH, "MainGame/", "Game3", AUDIO_EXTENSION), "game3", false);
	battleBGMList.push_back("game1");
	battleBGMList.push_back("game2");
	battleBGMList.push_back("game3");
}

void MainGameScene::Update() {
	bool isLastOne = GameCondition::IsPlayerLastOne();

	switch (currentGameState) {
	case GamePlay:

		gameStart.UpdateTime();

		if (gameStart.IsTimeNoReset() && beforeGameStart) {
			beforeGameStart = false;
			AudioUtility::PlayOneShot("gameStart");
			AudioUtility::PlayBGM(currentBGMName, 125.0f);
		}

		if (!beforeGameStart)
			go.UpdateTime();

		if (isLastOne || gameTimer <= 0.0f)
			gameEnd.UpdateTime();

		if ((isLastOne || gameTimer <= 0.0f) && !isPlayGameSetSE) {
			isPlayGameSetSE = true;
			AudioUtility::PlayOneShot("gameSet");
		}

		// プレイヤーがラス一になって、指定時間たったらカメラ移動
		if (isLastOne && !isCameraMove && gameEnd.IsTime()) {
			UIManager::GetInstance().DeleteAllUIToTag(MainGame, PlayerGauge);
			Player* p = PlayerUtility::GetLastOnePlayer();
			VECTOR cameraPos = p->GetPosition();
			cameraPos.y += 150;
			cameraPos.x -= 1000;
			Camera::main->SetTargetCamera(cameraPos, p->GetPosition(), p->GetTransform().GetForward(), 2);
			isCameraMove = true;
		}
		else if (gameTimer <= 0.0f && !isCameraMove && gameEnd.IsTime()) {
			UIManager::GetInstance().DeleteAllUIToTag(MainGame, PlayerGauge);
			Player* p = PlayerUtility::GetMostHPPlayer();
			VECTOR cameraPos = p->GetPosition();
			cameraPos.y += 150;
			cameraPos.x -= 1000;
			Camera::main->SetTargetCamera(cameraPos, p->GetPosition(), p->GetTransform().GetForward(), 2);
			isCameraMove = true;
		}

		// カメラが移動し終わったら
		if ((isLastOne || gameTimer <= 0.0f) && isCameraMove && !Camera::main->IsTargetCameraMove()) {
			returnMenu.UpdateTime();

			if (!isPlayWinSE) {
				isPlayWinSE = true;
				AudioUtility::PlayOneShot("win");
			}

			if (returnMenu.IsTime() || InputUtility::IsAllPadDown(XINPUT_BUTTON_A))
				SceneUtility::SetScene(Menu);
		}

		// 正式にゲームが始まっているときだけ
		if (!isLastOne && !beforeGameStart && gameTimer >= 0.0f) {

			// カウントダウン
			gameTimer -= TimeUtility::GetDeltaTime();

			// ゲームを一時停止する
			for (int i = 0; i < PLAYER_MAX; i++) {
				if (!InputUtility::IsPadDown(i, XINPUT_BUTTON_START)) continue;
				ChangeState(GameStop);
				UIManager::GetInstance().SetActiveUI(MainGame, PlayerGauge, false);
				AudioUtility::PlayOneShot("OpenPose");
				pushStopPlayerNum = i;
			}
		}

		MainGameTimer::Update();

		Effekseer_Sync3DSetting();
		CollisionUtility::Update();
		ItemUtility::Update();
		StageUtility::Update();
		Camera::main->Update();
		EffectUtility::Update();
		ColliderObjectUtility::Update();



		// ゲーム開始前かラス一になったら動けないように
		if ((!isLastOne && gameTimer >= 0.0f) && !beforeGameStart)
			PlayerUtility::Update();
		break;
	case GameStop:
		if (InputUtility::IsPadDown(pushStopPlayerNum, XINPUT_BUTTON_START)) {
			AudioUtility::PlayOneShot("buttonPush");
			UIManager::GetInstance().SetActiveUI(MainGame, PlayerGauge, true);
			ChangeState(GamePlay);
		}

		if (InputUtility::IsPadDown(pushStopPlayerNum, XINPUT_BUTTON_DPAD_UP)) {
			AudioUtility::PlayOneShot("onButton");
			currentSelectGameStop = std::clamp(currentSelectGameStop - 1, 0, 1);
		}
		if (InputUtility::IsPadDown(pushStopPlayerNum, XINPUT_BUTTON_DPAD_DOWN)) {
			AudioUtility::PlayOneShot("onButton");
			currentSelectGameStop = std::clamp(currentSelectGameStop + 1, 0, 1);
		}

		if (InputUtility::IsPadDown(pushStopPlayerNum, XINPUT_BUTTON_A)) {
			AudioUtility::PlayOneShot("buttonPush");
			if (currentSelectGameStop == 0) {
				UIManager::GetInstance().SetActiveUI(MainGame, PlayerGauge, true);
				ChangeState(GamePlay);
			}
			else {
				SceneUtility::SetScene(Menu);
			}
		}
		break;
	}

}

void MainGameScene::Render() {

	StageUtility::Render();
	PlayerUtility::Render();
	ItemUtility::Render();
	EffectUtility::Render();

#if _DEBUG
	CollisionUtility::Render();
#endif
	VECTOR pos;
	std::string string;
	int join;
	switch (currentGameState) {
	case GamePlay:
		string = std::to_string(static_cast<int>(gameTimer));
		pos = MyString::StringCenterPos(string.c_str(), resultFont, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 16, 1.5f, 1.5f);
		DrawExtendStringToHandle(pos.x, pos.y, 1.5f, 1.5f, string.c_str(), black, resultFont,white);

		join = GameCondition::GetJoinNum();
		for (int i = 0; i < join; i++) {
			BattleSetting b = GameCondition::GetBattleSetting(i);
			VECTOR gaugePos = PLAYER_GAUGE_POS[i];
			Player* p = PlayerUtility::GetPlayer(i + 1);

			if (!p) continue;

			MyDraw::DrawStringCenterPos(gaugePos.x - 50, gaugePos.y, 1, 1, MyString::MergeString(std::to_string(i + 1), "P").c_str(), colorPreset[b.color], resultFont, white);
			MyDraw::DrawExtendGraphCenterPos(gaugePos.x + PLAYER_GAUGE_WIDTH / 2, gaugePos.y, ArmUtility::GetArmGraphHandle(p->GetArm(Left)->GetArmType()), -0.3f, 0.3f);
			MyDraw::DrawExtendGraphCenterPos(gaugePos.x + PLAYER_GAUGE_WIDTH, gaugePos.y, ArmUtility::GetArmGraphHandle(p->GetArm(Right)->GetArmType()), 0.3f, 0.3f);
		}
		break;
	case GameStop:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawFillBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, black);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, -1);

		string = "ポーズ";
		pos = MyString::StringCenterPos(string.c_str(), resultFont, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 16, 2, 2);
		DrawExtendStringToHandle(pos.x, pos.y, 2, 2, string.c_str(), white, resultFont);

		string = "再開";
		pos = MyString::StringCenterPos(string.c_str(), resultFont, WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 8) * 3, 2, 2);
		DrawExtendStringToHandle(pos.x, pos.y, 2, 2, string.c_str(), poseSelectColor[currentSelectGameStop == 0 ? 1 : 0], resultFont);

		string = "試合をやめる";
		pos = MyString::StringCenterPos(string.c_str(), resultFont, WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 8) * 6, 2, 2);
		DrawExtendStringToHandle(pos.x, pos.y, 2, 2, string.c_str(), poseSelectColor[currentSelectGameStop == 1 ? 1 : 0], resultFont);

		break;
	}
	// ゲーム開始前のカウントダウン
	if (!gameStart.IsTimeNoReset() && beforeGameStart) {
		std::string countDown = std::to_string(static_cast<int>(gameStart.GetCountDownTime() + 1));
		pos = MyString::StringCenterPos(countDown.c_str(), resultFont, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3, 3);
		DrawExtendFormatStringToHandle(pos.x, pos.y, 3, 3, red, resultFont, countDown.c_str());
	}

	if (!go.IsTimeNoReset() && !beforeGameStart) {
		std::string start = "Start!";
		pos = MyString::StringCenterPos(start.c_str(), resultFont, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3, 3);
		DrawExtendFormatStringToHandle(pos.x, pos.y, 3, 3, red, resultFont, start.c_str());
	}

	// ゲーム終了後の処理
	if ((GameCondition::IsPlayerLastOne() || gameTimer <= 0.0f) && !gameEnd.IsTimeNoReset()) {
		std::string gameSet = "GameSet";
		pos = MyString::StringCenterPos(gameSet.c_str(), resultFont, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 2, 2);
		DrawExtendFormatStringToHandle(pos.x, pos.y, 2, 2, yellow, resultFont, gameSet.c_str());
	}

	if ((GameCondition::IsPlayerLastOne() || gameTimer <= 0.0f) && !Camera::main->IsTargetCameraMove() && gameEnd.IsTimeNoReset()) {
		std::string winner = "WINNER";
		pos = MyString::StringCenterPos(winner.c_str(), resultFont, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
		DrawStringToHandle(pos.x, pos.y, winner.c_str(), yellow, resultFont);
		int playerNum = -1;
		if (GameCondition::IsPlayerLastOne())
			playerNum = PlayerUtility::GetLastOnePlayer()->GetPlayerNumber();
		else if (gameTimer <= 0.0f)
			playerNum = PlayerUtility::GetMostHPPlayer()->GetPlayerNumber();
		std::string playerNumString = MyString::MergeString(std::to_string(playerNum), "P");
		pos = MyString::StringCenterPos(playerNumString.c_str(), resultFont, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3);
		DrawStringToHandle(pos.x, pos.y, playerNumString.c_str(), colorPreset[GameCondition::GetBattleSetting(playerNum - 1).color], resultFont);
	}

#if _DEBUG 線

	// オブジェクトの位置関係がわかるように地面にラインを描画する
	{
		VECTOR pos1, pos2;

		// XZ平面 100.0f毎に1本ライン引き
		{
			pos1 = VGet(-5000.0f, 0, -5000.0f);
			pos2 = VGet(-5000.0f, 0, 5000.0f);

			for (int i = 0; i < 100; i++) {
				DrawLine3D(pos1, pos2, gray);

				pos1.x += 100.0f;
				pos2.x += 100.0f;
			}

			pos1 = VGet(-5000.0f, 0, -5000.0f);
			pos2 = VGet(5000.0f, 0, -5000.0f);
			for (int i = 0; i < 100; i++) {
				DrawLine3D(pos1, pos2, gray);

				pos1.z += 100.0f;
				pos2.z += 100.0f;
			}
		}

		// X軸
		{
			pos1 = VZero;
			pos2 = VScale(VRight, 5000);	// VRight * 5000 をしてる
			DrawLine3D(pos1, pos2, red);
		}

		// Y軸
		{
			pos1 = VZero;
			pos2 = VScale(VUp, 5000);	    // VUp * 5000 をしてる
			DrawLine3D(pos1, pos2, green);
		}

		// Z軸
		{
			pos1 = VZero;
			pos2 = VScale(VForward, 5000);	// VRight * 5000 をしてる
			DrawLine3D(pos1, pos2, blue);
		}
	}
#endif
}

void MainGameScene::Setup() {
	Camera::main->GetTransform().SetPosition(VGet(0, 5000, 0));
	Camera::main->GetTransform().SetRotation(VGet(90, 0, -90));

	Camera::main->Update();
	gameTimer = 180.0f;
	ChangeState(GamePlay);

	StageUtility::SetStage(GameCondition::GetStageNum());
	for (int i = 0; i < GameCondition::GetJoinNum(); i++) {
		Player* p = PlayerUtility::UsePlayer(StageUtility::GetCurrentStage()->GetRandomPlayerSpawnPoint());
		p->SetPortNum(GameCondition::GetBattleSetting(i).portNum);
		p->ChangeMaterialColor(0, colorPreset[GameCondition::GetBattleSetting(i).color]);
		p->ChangeArm(Left, GameCondition::GetBattleSetting(i).left);
		p->ChangeArm(Right, GameCondition::GetBattleSetting(i).right);
		p->Update();
		p->Render();
	}

	currentBGMName = battleBGMList[MyMath::Random(0, battleBGMList.size() - 1)];

	GameCondition::ResetDeadNum();
	isPlayGameSetSE = false;
	isPlayWinSE = false;
	isCameraMove = false;
	beforeGameStart = true;
	gameStart.ResetCurrentTime();
	go.ResetCurrentTime();
	returnMenu.ResetCurrentTime();
	gameEnd.ResetCurrentTime();
}

void MainGameScene::Teardown() {
	PlayerUtility::UnuseAllPlayer();
	ItemUtility::UnuseAll();
	AudioUtility::Stop(currentBGMName);
	EffectUtility::DeleteAllEffect();
}

void MainGameScene::DeleteData() {}

void MainGameScene::ChangeState(GameSceneState _state) {
	if (_state == currentGameState) return;

	currentGameState = _state;
}
