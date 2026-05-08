#include "ColliderObject.h"
#include "../../Component/Collider.h"
#include "../../Utility/TimeUtility.h"

ColliderObject::ColliderObject(std::unique_ptr<Collider>& _pCol, std::function<void(Collider* _pOhter)> _func, Tag _tag)
	:Object(_tag)
	, pCollider(std::move(_pCol))
	, lifeTime(-1)
	, unActiveReasonLifeTime(false)
	, isActive(true)
	, func(_func) {
	Start();
}

ColliderObject::ColliderObject(std::unique_ptr<Collider>& _pCol, std::function<void(Collider* _pOhter)> _func, float _lifeTime, Tag _tag)
	:Object(_tag)
	, pCollider(std::move(_pCol))
	, lifeTime(_lifeTime)
	, unActiveReasonLifeTime(true)
	, isActive(true)
	, func(_func) {
	Start();
}

void ColliderObject::Start() {}

void ColliderObject::Update() {
	if (!isActive) return;

	Object::Update();

	if (pCollider)
		pCollider->Update();

	// ¶‘¶ŠÔ‚ª–³‚¢‚à‚Ì‚Í‚±‚±‚Å‹A‚é
	if (!unActiveReasonLifeTime) return;

	lifeTime -= TimeUtility::GetDeltaTime();

	// ¶‘¶ŠÔ‚ğ‰ß‚¬‚½‚çXV‚µ‚È‚¢
	if (lifeTime <= 0)
		isActive = false;
}

void ColliderObject::Render() {
	if (!isActive) return;

	Object::Render();
}

void ColliderObject::OnTriggerEnter(Collider* _pOther) {
	if (func)
		func(_pOther);
}

void ColliderObject::OnTriggerStay(Collider* _pOther) {}

void ColliderObject::OnTriggerExit(Collider* _pOther) {}
