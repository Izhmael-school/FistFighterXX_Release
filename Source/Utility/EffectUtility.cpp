#include "EffectUtility.h"
#include "../Manager/EffectManager.h"

void EffectUtility::Load(std::string _filePath, std::string _name, float _magnification) {
	EffectManager::GetInstance().Load(_filePath, _name, _magnification);
}

Effect* EffectUtility::Instantiate(std::string _name, VECTOR _pos) {
	return EffectManager::GetInstance().Instantiate(_name, _pos);
}

void EffectUtility::Update() {
	EffectManager::GetInstance().Update();
}

void EffectUtility::Render() {
	EffectManager::GetInstance().Render();
}

void EffectUtility::DeleteData() {
	EffectManager::GetInstance().DeleteData();
}

void EffectUtility::DeleteAllEffect(){
	EffectManager::GetInstance().DeleteAllEffect();
}
