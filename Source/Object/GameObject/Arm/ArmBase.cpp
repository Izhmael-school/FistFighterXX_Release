#include "ArmBase.h"
#include "../../../Utility/TimeUtility.h"
#include "../../../Utility/InputUtility.h"
#include "../../../Utility/FontUtility.h"
#include "../Character/Player/Player.h"
#include "../../../Component/Collider.h"
#include "../../../Other/CommonModule/MyMath.h"
#include "../../../Other/CommonModule/MyDraw.h"
#include "../../../Other/CommonModule/MyString.h"
#include "../../../Manager/UIManager.h"
#include "../../../UI/Gauge/MoveGauge.h"
#include "ArmEffect/ArmEffectBase.h"

#include <cassert>

ArmBase::ArmBase(int _mHandle, VECTOR _pos, Player* _owner, std::unique_ptr<ArmEffectBase> _effect)
	:GameObject(_mHandle, _pos, Arm)
	, owner(_owner)
	, isShot(false)
	, armType(Punch)
	, correctionMat(MGetIdent())
	,effect(std::move(_effect))
{
	Start();
}

void ArmBase::Start() {
	controller.SetOwner(this);
	controller.SetPortNum(owner->GetPortNum());
	pCollider = std::make_unique<SphereCollider>(this, VZero, 150);
}

void ArmBase::Update() {

	if (!isShot) {
		auto boneMat = MV1GetFrameLocalWorldMatrix(attachModelHandle, attachFrameHandle);

		// ç¿ïWÇÇ‡ÇÁÇ§
		correctionMat.m[3][0] = boneMat.m[3][0];
		correctionMat.m[3][1] = boneMat.m[3][1];
		correctionMat.m[3][2] = boneMat.m[3][2];

		// ëÃÇ…Ç¬Ç¢ÇƒÇ¢Ç≠ÇÊÇ§Ç…ç¿ïWÇè„èëÇ´
		GetTransform().SetPosition(VGet(boneMat.m[3][0], boneMat.m[3][1], boneMat.m[3][2]));

		VECTOR pos = GetPosition();

		GetTransform().SetMatrix(correctionMat);
	}
	else {
		controller.Move();
		shotTime += TimeUtility::GetDeltaTime();
	}

	GameObject::Update();
}

void ArmBase::Render() {
	GameObject::Render();

	if (isShot) {
		VECTOR pos = ConvWorldPosToScreenPos(GetPosition());
		Player* p = GetOwner();
		MyDraw::DrawStringCenterPos(pos.x, pos.y - 50, 2, 2, (armPos == Left ? "L" : "R"), p->GetMatColor(), FontUtility::UseFontHandle("MainFont"), white);

	}
}

void ArmBase::Setup() {
	isShot = false;
}

void ArmBase::Teardown() {
	pCollider->SetActive(false);
	isShot = false;
}

void ArmBase::ShotStart() {
	if (isShot) return;

	isShot = true;
	shotTime = 0.0f;
	pCollider->SetActive(true);

	status.currentDurability = status.maxDurability;

	gauge = UIManager::GetInstance().CreateMoveGauge(MainGame, this, -ARM_MOVEGAUGE_WIDTH, 0, ARM_MOVEGAUGE_WIDTH, ARM_MOVEGAUGE_HEIGHT, PlayerGauge,false);
	gauge->SetGetterFunc(
		[this]() {return GetCurrentDurability(); },
		[this]() {return GetMaxDurability(); });
}

void ArmBase::ShotEnd() {
	if (!isShot) return;
	effect->ShotEnd(this);

	isShot = false;
	shotTime = 0.0f;
	gauge->SetActive(false);
	pCollider->SetActive(false);

}

void ArmBase::OnTriggerEnter(Collider* _pOther) {
	if (!effect || !isShot) return;

	if (_pOther->GetTag() == PlayerCharacter)
		effect->PlayerHit(static_cast<Player*>(_pOther->GetOwner()), this);
	if (_pOther->GetTag() == Arm)
		effect->ArmHit(static_cast<ArmBase*>(_pOther->GetOwner()), this);
	if (_pOther->GetTag() == UnmovingWall || _pOther->GetTag() == Wall)
		effect->WallHit(this,_pOther);
	if (_pOther->GetTag() == Item)
		effect->ItemHit(this);
}

void ArmBase::OnTriggerStay(Collider* _pOther) {
	if (!isShot) return;

	if (_pOther->GetTag() == PlayerCharacter)
		effect->PlayerHit(static_cast<Player*>(_pOther->GetOwner()), this);
	if (_pOther->GetTag() == UnmovingWall || _pOther->GetTag() == Wall)
		effect->WallHit(this, _pOther);
}

void ArmBase::OnTriggerExit(Collider* _pOther) {}

void ArmBase::ArmAttach(std::string _frameName) {
	attachModelHandle = owner->GetModelHandle();
	attachFrameHandle = MV1SearchFrame(attachModelHandle, _frameName.c_str());

	if (attachFrameHandle == -1) {
		assert(attachFrameHandle != -1);
		return;
	}

	// èâä˙à íuçáÇÌÇπ
	MATRIX mat = MV1GetFrameLocalWorldMatrix(attachModelHandle, attachFrameHandle);
	int r = MV1SetMatrix(modelHandle, mat);
}