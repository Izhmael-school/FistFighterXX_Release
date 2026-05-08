#pragma once
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include <vector>
#include <memory>

class StageBase;
class StageGenerator;

class StageManager : public Singleton<StageManager>, public ManagerBase {
public:
	StageManager();
	~StageManager();

private:
	void Start() override;

public:
	void Update() override;
	void Render() override;

	void DeleteData() override;

	void SetStage(int _stageNum);

	inline StageBase* GetCurrentStage() const { return currentStage; }
private:
	std::vector<std::unique_ptr<StageBase>> stageArray;
	StageBase* currentStage;
	std::unique_ptr<StageGenerator> generator;
};

