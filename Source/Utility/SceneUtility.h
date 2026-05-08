#pragma once
#include "../Definition.h"

/// <summary>
/// シーン管理クラスを使いやすくした便利クラス
/// </summary>
class SceneUtility {
public:
	/**
	  シーンの変更
	*/
	static void SetScene(SceneState _setScene);
	/**
	  更新処理
	*/
	static void Update();
	/**
	  描画処理
	*/
	static void Render();

	static SceneState GetCurrentScene();

	static void DeleteData();
};

