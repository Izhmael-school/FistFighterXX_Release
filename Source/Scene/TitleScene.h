#pragma once
#include "SceneBase.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public SceneBase {
private:
	// 生成されたときに一度だけ呼ばれる
	void Start() override;
public :
	TitleScene();
	~TitleScene();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
	// 使用前初期化
	void Setup() override;
	// 使用後後処理
	void Teardown() override;

	void DeleteData() override;
private:
	int titleSprite;
	VECTOR textPos;
	int useFontHandle;
};

