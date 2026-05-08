#include "SceneManager.h"
#include "../Scene/TitleScene.h"
#include "../Scene/MenuScene.h"
#include "../Scene/MainGameScene.h"
#include "../Utility/FadeUtility.h"
#include "UIManager.h"

SceneManager::SceneManager()
	:currentState(Title) 
	,sceneChanged(false)
{
	Start();
}

void SceneManager::Start() {
	// シーンを作る
	pSceneArray[static_cast<int>(SceneState::Title)] = std::make_unique<TitleScene>();
	pSceneArray[static_cast<int>(SceneState::Menu)] = std::make_unique<MenuScene>();
	pSceneArray[static_cast<int>(SceneState::MainGame)] = std::make_unique<MainGameScene>();

	// 最初のシーン
	pCurrentScene = std::move(pSceneArray[currentState]);
	pCurrentScene->Setup();
}

void SceneManager::SetNextScene(SceneState _setScene) {
	FadeUtility::FadeStart(FadeOut,FadeNormal);
	sceneChanged = true;
	nextScene = _setScene;
}

void SceneManager::DeleteData() {

}

void SceneManager::ChangeScene() {
	sceneChanged = false;
	// 今のシーンが残っていれば処理する
	if (pCurrentScene)TeardownScene();
	// シーンを持ってくる
	pCurrentScene = std::move(pSceneArray[static_cast<int>(nextScene)]);
	// 使用前初期化
	pCurrentScene->Setup();
	currentState = nextScene;
	FadeUtility::FadeStart(FadeIn, FadeNormal);
}


void SceneManager::TeardownScene() {
	if (!pCurrentScene) return;

	// 使用後後処理
	pCurrentScene->Teardown();
	// シーンを戻す
	pSceneArray[static_cast<int>(currentState)] = std::move(pCurrentScene);
	currentState = Invalid;
}

void SceneManager::Update() {
	// シーンを変える
	if (sceneChanged && FadeUtility::GetCurrentState() == None)
		ChangeScene();
	
	// フェード中なら更新しない
	if (FadeUtility::GetCurrentState() != None)
		return;

	if (pCurrentScene)
		pCurrentScene->Update();

	UIManager::GetInstance().Update();
}

void SceneManager::Render() {
	if (pCurrentScene)
		pCurrentScene->Render();

	UIManager::GetInstance().Render();
	FadeUtility::Render();
}