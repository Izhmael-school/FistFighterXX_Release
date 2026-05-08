#pragma once
#include <memory>
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include "../Definition.h"
#include "../Scene/SceneBase.h"

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager : public Singleton<SceneManager> ,public ManagerBase{
private:
	// 初期化処理
	void Start() override;
	// シーンを消す
	void TeardownScene();
	// シーンの変更
	void ChangeScene();
public:
	SceneManager();
	~SceneManager() = default;
	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

	// 次のシーンをセットしてフェードする
	void SetNextScene(SceneState _setScene);

	void DeleteData() override;

	inline SceneState GetCurrentScene() { return currentState; }
private:
	// 今のシーン
	std::unique_ptr<class SceneBase> pCurrentScene;
	SceneState currentState;
	// シーンのリスト
	std::unique_ptr <class SceneBase> pSceneArray[SceneState::SceneMax];
	bool sceneChanged;
	SceneState nextScene;
};

