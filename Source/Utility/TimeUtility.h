#pragma once
#include "../Manager/TimeManager.h"

/// <summary>
/// 時間管理クラスを使いやすくした便利クラス
/// </summary>
class TimeUtility {
public:
	/**
	  時間の取得
	*/
	static float GetDeltaTime();

	/**
	  更新処理
	*/
	static void Update();
};

