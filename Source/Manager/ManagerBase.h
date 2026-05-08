#pragma once
/// <summary>
/// 管理クラスの既定
/// </summary>
class ManagerBase {
public:
	ManagerBase() = default;
	~ManagerBase() = default;

	// 生成したときにだけ呼ぶ
	virtual void Start(){}
	// 更新処理
	virtual void Update(){}
	// 描画処理
	virtual void Render(){}
	// 使用前準備
	virtual void Setup(){}
	// 使用後処理
	virtual void Teardown(){}

protected:
	// Start関数を呼んだか
	bool calledStart = false;
};

