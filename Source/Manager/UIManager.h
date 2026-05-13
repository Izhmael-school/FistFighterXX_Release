#pragma once
#include <vector> 
#include <memory>
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include "../Definition.h"
#include <functional>
#include <string>

class Object;
class UIBase;
class UIGauge;
class MoveGauge;
class UIButton;
class PlayerCursor;

class UIManager : public Singleton<UIManager> , public ManagerBase {
public:
	UIManager();
	~UIManager();

private:
	void Start() override;

public:
	UIGauge* CreateUIGauge(SceneState drawScene,float _x, float _y, float _w , float _h ,UITag _tag = NoUITag,bool _isDecrease = true);
	MoveGauge* CreateMoveGauge(SceneState drawScene, Object* _sourceObject, float _offsetX, float _offsetY, float _w, float _h, UITag _tag = NoUITag, bool _isDecrease = true);
	UIButton* CreateUIButton(SceneState drawScene,float _x, float _y, float _width, float _height, std::function<void(void)> _func, std::string _text = "Text", unsigned int _idleColor = black, unsigned int _selectColor = yellow, int _fontHandle = -1, float _fontSize = 1.0f, int _backImageHandle = -1, int _frameImageHandle = -1);
	PlayerCursor* CreatePlayerCursor(SceneState drawScene,int _portNum);
	void Update() override;
	void Render() override;

	void AddUI(SceneState _drawScene, std::unique_ptr<UIBase> _ui, UITag _tag = NoUITag);

	// タグ指定ですべてのUIを消す
	void DeleteAllUIToTag(SceneState _drawScene, UITag _tag);
	// タグ指定ですべてのUIの状態を変える
	void SetActiveUI(SceneState _drawScene, UITag _tag,bool _isAtive);

	UIBase* GetUIByID(int _id);

	void DeleteUIByID(int _id);
private:
	std::vector<std::vector<std::unique_ptr<UIBase>>> uiArray;
};

