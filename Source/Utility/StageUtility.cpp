#include "StageUtility.h"
#include "../Manager/StageManager.h"
#include "../Object/GameObject/Stage/StageBase.h"

void StageUtility::Update() {
    StageManager::GetInstance().Update();
}

void StageUtility::Render() {
    StageManager::GetInstance().Render();
}

void StageUtility::DeleteData() {
    StageManager::GetInstance().DeleteData();
}

void StageUtility::SetStage(int _stageNum) {
    StageManager::GetInstance().SetStage(_stageNum);
}

StageBase* StageUtility::GetCurrentStage() {
    return StageManager::GetInstance().GetCurrentStage();
}

void StageUtility::CanRespawnItemPoint(int _pointNum) {
    GetCurrentStage()->CapRespawnItem(_pointNum);
}
