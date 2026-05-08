#pragma once
#include "DxLib.h"
#include "../Definition.h"

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase {
private:
	// 生成されたときに一度だけ呼ばれる
	virtual void Start() = 0;

public:
	SceneBase() = default;
	~SceneBase() = default;

	// 更新処理
	virtual void Update() = 0;
	// 描画処理
	virtual void Render() = 0;
	// 使用前初期化
	virtual void Setup() = 0;
	// 使用後後処理
	virtual void Teardown() = 0;

	// 終了前削除
	virtual void DeleteData() = 0;
};

