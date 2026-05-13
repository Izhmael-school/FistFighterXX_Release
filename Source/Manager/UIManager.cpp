#include "UIManager.h"
#include "../UI/UIBase.h"
#include "../UI/Gauge/Gauge.h"
#include "../UI/Gauge/CircleGauge.h"
#include "../UI/Gauge/MoveGauge.h"
#include "../UI/Button/UIButton.h"
#include "../UI/Cursor/PlayerCursor.h"
#include "../Utility/SceneUtility.h"

UIManager::UIManager() { Start(); }

UIManager::~UIManager() {}

void UIManager::Start() {
	uiArray.resize(static_cast<int>(SceneMax));
}

UIGauge* UIManager::CreateUIGauge(SceneState drawScene, float _x, float _y, float _w, float _h, UITag _tag, bool _isDecrease) {
	std::unique_ptr<UIGauge> gauge = std::make_unique<UIGauge>(_x, _y, _w, _h, _tag, _isDecrease);
	int sceneNum = static_cast<int>(drawScene);
	uiArray[sceneNum].push_back(std::move(gauge));
	return static_cast<UIGauge*>(uiArray[sceneNum].back().get());
}

MoveGauge* UIManager::CreateMoveGauge(SceneState drawScene, Object* _sourceObject, float _offsetX, float _offsetY, float _w, float _h, UITag _tag, bool _isDecrease) {
	std::unique_ptr<MoveGauge> gauge = std::make_unique<MoveGauge>(_sourceObject, _offsetX, _offsetY, _w, _h, _tag, _isDecrease);
	int sceneNum = static_cast<int>(drawScene);
	uiArray[sceneNum].push_back(std::move(gauge));
	return static_cast<MoveGauge*>(uiArray[sceneNum].back().get());
}

UIButton* UIManager::CreateUIButton(SceneState drawScene, float _x, float _y, float _width, float _height, std::function<void(void)> _func, std::string _text, unsigned int _idleColor, unsigned int _selectColor, int _fontHandle, float _fontSize, int _backImageHandle, int _frameImageHandle) {
	std::unique_ptr<UIButton> button = std::make_unique<UIButton>(_x, _y, _width, _height, _func, _text, _idleColor, _selectColor, _fontHandle, _fontSize, _backImageHandle, _frameImageHandle);
	int sceneNum = static_cast<int>(drawScene);
	uiArray[sceneNum].push_back(std::move(button));
	return static_cast<UIButton*>(uiArray[sceneNum].back().get());
}

PlayerCursor* UIManager::CreatePlayerCursor(SceneState drawScene, int _portNum) {
	std::unique_ptr<PlayerCursor> cursor = std::make_unique<PlayerCursor>(_portNum);
	int sceneNum = static_cast<int>(drawScene);
	uiArray[sceneNum].push_back(std::move(cursor));
	return static_cast<PlayerCursor*>(uiArray[sceneNum].back().get());
}

void UIManager::Update() {
	int sceneNum = static_cast<int>(SceneUtility::GetCurrentScene());

	for (auto& ui : uiArray[sceneNum]) {
		ui->Update();
	}
}

void UIManager::Render() {
	int sceneNum = static_cast<int>(SceneUtility::GetCurrentScene());

	for (auto& ui : uiArray[sceneNum]) {
		ui->Render();
	}
}

void UIManager::AddUI(SceneState _drawScene, std::unique_ptr<UIBase> _ui, UITag _tag){
	int sceneNum = static_cast<int>(_drawScene);
	uiArray[sceneNum].push_back(std::move(_ui));
}

void UIManager::DeleteAllUIToTag(SceneState _drawScene, UITag _tag) {
	std::erase_if(uiArray[_drawScene], [_tag](std::unique_ptr<UIBase>& _pUI) {
		if (_pUI->GetTag() != _tag) return false;

		_pUI.reset();
		return true;
		});
}

void UIManager::SetActiveUI(SceneState _drawScene, UITag _tag, bool _isActive) {
	for (auto& ui : uiArray[_drawScene]) {
		if (ui->GetTag() != _tag) continue;

		ui->SetActive(_isActive);
	}
}

UIBase* UIManager::GetUIByID(int _id)
{
	for(auto& scene : uiArray) {
		for(auto& ui : scene) {
			if(ui->GetID() == _id) {
				return ui.get();
			}
		}
	}
	return nullptr;
}

void UIManager::DeleteUIByID(int _id)
{
	for(auto& scene : uiArray) {
		auto it = std::remove_if(scene.begin(), scene.end(), [_id](std::unique_ptr<UIBase>& ui) {
			return ui->GetID() == _id;
		});
		if (it != scene.end()) {
			scene.erase(it, scene.end());
			return;
		}
	}
}
