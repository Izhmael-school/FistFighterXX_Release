#pragma once
#include "../Component/Singleton.h"
#include "ManagerBase.h"

/// <summary>
/// 時間管理クラス
/// </summary>
class TimeManager : public Singleton<TimeManager> ,public ManagerBase{
private:
	// 初期化処理
	void Start() override;
public:
	TimeManager();
	~TimeManager() = default;
	// 更新処理
	void Update() override;
	// 時間の取得
	float GetDeltaTime() const { return deltaTime; }

private:
	int prevTime;
	int currentTime;

	float deltaTime;
};

