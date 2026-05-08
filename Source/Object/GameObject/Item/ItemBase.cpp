#include "ItemBase.h"
#include "../../../Component/Collider.h"
#include "ItemEffectObserver.h"
#include "../Character/Player/Player.h"
#include "../Arm/ArmBase.h"
#include "../../../Utility/TimeUtility.h"
#include "../../../Utility/StageUtility.h"

ItemBase::ItemBase(int mHandle, ItemData _data, int _spawnPointNum)
	:GameObject(mHandle,VZero,Item)
	, data(_data)
	,result()
	,currentLifeTime(0.0f)
	,maxLifeTime(15.0f)
	,spawnPointNum(_spawnPointNum)
{ Start(); }

ItemBase::~ItemBase() {}

void ItemBase::Start() {
	pCollider = std::make_unique<SphereCollider>(this, GetTransform().GetPosition(), 100);
}

void ItemBase::Update() {
	if (!isVisible) return;

	GameObject::Update();

	currentLifeTime += TimeUtility::GetDeltaTime();

	GetTransform().AddRotation(VScale(VUp, 5));

	if (currentLifeTime >= maxLifeTime)
		isVisible = false;
}

void ItemBase::Render() {
	if (!isVisible) return;

	GameObject::Render();
}

void ItemBase::Setup() {
	isVisible = true;
	pCollider->SetActive(true);
	currentLifeTime = 0.0f;
}

void ItemBase::Teardown() {
	isVisible = false;
	pCollider->SetActive(false);
	StageUtility::CanRespawnItemPoint(spawnPointNum);
}

void ItemBase::EffectExcute(ItemEffectType _type) {
	switch (_type) {
	case NoItemEffect:
		return;
	case HPHeal:
		ItemEffectObserver::HPHeal(result._target,data.value);
		break;
	case StaminaHeal:
		ItemEffectObserver::StaminaHeal(result._target, data.value);
		break;
	case ArmChange:
		ItemEffectObserver::ArmChange(result._target, result.pos, static_cast<ArmType>(data.value));
		break;
	}

	isVisible = false;
}

void ItemBase::OnTriggerEnter(Collider* _pOther) {
	// プレイヤーの時
	if (_pOther->GetOwner()->GetTag() == PlayerCharacter) {
		result._target = static_cast<Player*>(_pOther->GetOwner());
		EffectExcute(data.p_effectType);
		return;
	}
	// ウデの時
	if (_pOther->GetOwner()->GetTag() == Arm) {
		ArmBase* a = static_cast<ArmBase*>(_pOther->GetOwner());

		result.pos = a->GetArmPos();
		result._target = a->GetOwner();
		EffectExcute(data.a_effectType);
		return;
	}
	result._target = nullptr;
}