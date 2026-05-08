#include "SceneUtility.h"
#include "../Manager/SceneManager.h"

void SceneUtility::SetScene(SceneState _setScene) { SceneManager::GetInstance().SetNextScene(_setScene); }

void SceneUtility::Update() { SceneManager::GetInstance().Update(); }

void SceneUtility::Render() { SceneManager::GetInstance().Render(); }

SceneState SceneUtility::GetCurrentScene() {
    return SceneManager::GetInstance().GetCurrentScene();
}

void SceneUtility::DeleteData() { SceneManager::GetInstance().DeleteData(); }
