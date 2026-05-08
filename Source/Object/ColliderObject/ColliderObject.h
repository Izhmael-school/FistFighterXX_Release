#pragma once
#include "../Object.h"
#include "../../Definition.h"
#include <memory>
#include <functional>

class Collider;

/// <summary>
/// 当たり判定だけのオブジェクトクラス
/// </summary>
class ColliderObject : public Object {
public:
	ColliderObject(std::unique_ptr<Collider>& _pCol, std::function<void(Collider* _pOhter)> _func, Tag _tag = NoTag);
	ColliderObject(std::unique_ptr<Collider>& _pCol, std::function<void(Collider* _pOhter)> _func, float _lifeTime, Tag _tag = NoTag);
	~ColliderObject() = default;

private:
	void Start() override;

public:
	void Update() override;
	void Render() override;

	void OnTriggerEnter(Collider* _pOther) override;
	void OnTriggerStay(Collider* _pOther) override;
	void OnTriggerExit(Collider* _pOther) override;

	inline std::unique_ptr<Collider>& GetCollider() { return pCollider; }
	inline void SetCollider(std::unique_ptr<Collider>& _pCol) { pCollider = std::move(_pCol); }

	inline bool IsActive() const { return isActive; }

	inline void SetFunction(std::function<void(Collider* _pOhter)> _func) { func = _func; }
private:
	std::unique_ptr<Collider> pCollider;
	float lifeTime;
	bool unActiveReasonLifeTime;
	bool isActive;
	std::function<void(Collider* _pOhter)> func;
};

