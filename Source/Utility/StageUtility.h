#pragma once

class StageBase;

class StageUtility {
public:

	static void Update();
	static void Render();

	static void DeleteData();

	static void SetStage(int _stageNum);

	static StageBase* GetCurrentStage();

	static void CanRespawnItemPoint(int _pointNum);
};

