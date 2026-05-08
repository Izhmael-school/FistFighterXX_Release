#include "StageManager.h"
#include "../Generator/StageGenerator.h"
#include "../Object/GameObject/Stage/StageBase.h"

StageManager::StageManager()
	:currentStage()
	, stageArray() {
	Start();
}

StageManager::~StageManager() {}

void StageManager::Start() {
	generator = std::make_unique<StageGenerator>();

	for (int i = 0; i < STAGE_NUM; i++) {
		stageArray.push_back(generator->Create(i));
	}
}

void StageManager::Update() {
	if (!currentStage) return;

	currentStage->Update();
}

void StageManager::Render() {
	if (!currentStage) return;

	currentStage->Render();
}

void StageManager::DeleteData() {
	generator->DeleteOriginModelHandle();

	for (auto& s : stageArray) {
		s->DeleteModel();
	}
}

void StageManager::SetStage(int _stageNum) {
	if (_stageNum >= STAGE_NUM) return;
	if (currentStage)
		currentStage->Teardown();
	currentStage = stageArray[_stageNum].get();
	currentStage->Setup();
}
