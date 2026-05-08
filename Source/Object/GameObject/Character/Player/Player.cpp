#include "Player.h"
#include "../../Arm/ArmBase.h"
#include "../../../../Utility/ArmUtility.h"
#include "../../../../Component/Collider.h"
#include "../../../../Manager/UIManager.h"
#include "../../../../UI/Gauge/Gauge.h"
#include "../../../../UI/Gauge/MoveGauge.h"
#include <algorithm>
#include "../../../../Other/CommonModule/MyMath.h"
#include "../../../../Game/GameCondition.h"

Player::Player(int _mHandle, int _portNum, VECTOR _pos, Tag _tag)
	:Character(_mHandle, _pos, _tag)
	, moveSpeed(1000)
	, useDeadExecute(false) {
	controller.SetPortNum(_portNum);
	Start();
}

Player::~Player() {}

void Player::Start() {
	controller.SetOwner(this);

	modelHandle = MV1LoadModel("res/Model/Character/Player/Player.mv1");

	pCollider = std::make_unique<CapsuleCollider>(this, VZero, VGet(0, 300, 0), 150);
	consumeStamina.SetTargetTime(0.1f);
	healStamina.SetTargetTime(0.1f);
}

void Player::Update() {
	GameObject::Update();

	// スパンの更新
	consumeStamina.UpdateTime();
	healStamina.UpdateTime();

	// 死んだか
	if (IsDead()) {
		DeadExecute();
		return;
	}

	// コントローラの更新
	controller.Update();

	for (auto& a : equipArm) {
		a->Update();
	}

	// 腕の発射状況を確認
	shotNum = 0;
	for (int i = 0; i < ArmMax; i++) {
		if (!equipArm[i]->IsShot())	continue;

		shotNum++;

		if (consumeStamina.IsTime())
			// スタミナ消費
			SubStamina(equipArm[i]->GetConsumeStamina());

		// スタミナ切れならウデを回収
		if (status.currentStamina <= 0) {
			ReturnArm(ArmMax);
		}
	}


	// 発射してなければ
	if (shotNum == 0) {
		if (healStamina.IsTime())
			// スタミナ回復
			AddStamina(2);
	}
}

void Player::Render() {
	GameObject::Render();

	for (auto& a : equipArm) {
		a->Render();
	}
}

void Player::Setup() {
	status.maxHP = 100;
	status.currentHP = status.maxHP;
	status.maxStamina = 100;
	status.currentStamina = status.maxStamina;

	consumeStamina.ResetCurrentTime();
	healStamina.ResetCurrentTime();

	useDeadExecute = false;
	SetVisible(true);
	pCollider->SetActive(true);
	ChangeArm(Left, Star);
	ChangeArm(Right, Cutter);
	VECTOR gaugePos = PLAYER_GAUGE_POS[playerNumber - 1];
	auto hpbar = UIManager::GetInstance().CreateUIGauge(MainGame, gaugePos.x, gaugePos.y, PLAYER_GAUGE_WIDTH, PLAYER_GAUGE_HEIGHT, PlayerGauge);
	hpbar->SetGetterFunc(
		[this]() {return GetCurrentHP(); },
		[this]() {return GetMaxHP(); });

	auto moveHPBar = UIManager::GetInstance().CreateMoveGauge(MainGame, this, -PLAYER_MOVEGAUGE_WIDTH, 0, PLAYER_MOVEGAUGE_WIDTH, PLAYER_MOVEGAUGE_HEIGHT, PlayerGauge);
	moveHPBar->SetGetterFunc(
		[this]() {return GetCurrentHP(); },
		[this]() {return GetMaxHP(); });

	auto staminaBar = UIManager::GetInstance().CreateUIGauge(MainGame, gaugePos.x, gaugePos.y + PLAYER_GAUGE_HEIGHT, PLAYER_GAUGE_WIDTH, PLAYER_GAUGE_HEIGHT, PlayerGauge, false);
	staminaBar->SetGetterFunc(
		[this]() {return GetCurrentStamina(); },
		[this]() {return GetMaxStamina(); }
	);
	staminaBar->ChangeColor(yellow, gray, black, black);

	auto moveStaminaBar = UIManager::GetInstance().CreateMoveGauge(MainGame, this, -PLAYER_MOVEGAUGE_WIDTH, PLAYER_MOVEGAUGE_HEIGHT, PLAYER_MOVEGAUGE_WIDTH, PLAYER_MOVEGAUGE_HEIGHT, PlayerGauge,false);
	moveStaminaBar->SetGetterFunc(
		[this]() {return GetCurrentStamina(); },
		[this]() {return GetMaxStamina(); });
	moveStaminaBar->ChangeColor(yellow, gray, black, black);
}

void Player::Teardown() {
	SetVisible(false);
	pCollider->SetActive(false);
	ArmUtility::UnuseArm(equipArm[Left]);
	ArmUtility::UnuseArm(equipArm[Right]);
}

void Player::SetPortNum(int _portNum) {
	controller.SetPortNum(_portNum);

	if (equipArm[Left])
		equipArm[Left]->SetPortNum(_portNum);

	if (equipArm[Right])
		equipArm[Right]->SetPortNum(_portNum);
}

void Player::ChangeArm(ArmPos _armPos, ArmType _type) {
	if (equipArm) {

		ArmUtility::UnuseArm(equipArm[_armPos]);
	}
	equipArm[_armPos] = ArmUtility::UseArm(_type, this, _armPos, std::string(attachFrameName[_armPos]));
	equipArm[_armPos]->SetPortNum(GetPortNum());
	equipArm[_armPos]->SetOwner(this);
}

void Player::ShotArm(ArmPos _armPos) {
	// 不正値ならリターン
	if (_armPos == ArmMax) return;

	// すでに発射していれば回収する
	if (equipArm[_armPos]->IsShot()) {
		ReturnArm(_armPos);
		return;
	}

	// 発射開始
	equipArm[_armPos]->ShotStart();
}

void Player::ReturnArm(ArmPos _armPos) {

	// ArmMaxなら両方回収
	if (_armPos == ArmMax) {
		for (int i = 0; i < ArmMax; i++) {
			if (!equipArm[i]->IsShot()) continue;

			// ウデを回収
			equipArm[i]->ShotEnd();
		}
		return;
	}

	// 発射していなければリターン
	if (!equipArm[_armPos]->IsShot()) return;

	// ウデを回収
	equipArm[_armPos]->ShotEnd();
}

void Player::DeadExecute() {
	if (useDeadExecute) return;
	useDeadExecute = true;

	// 死亡後の処理を書く
	GameCondition::AddDeadNum();
	SetVisible(false);
}

void Player::WallHit(Collider* _wall) {
	CapsuleCollider* cap = static_cast<CapsuleCollider*>(GetCollider());
	BoxCollider* box = static_cast<BoxCollider*>(_wall);

	VECTOR boxMin = box->GetMinPoint();
	VECTOR boxMax = box->GetMaxPoint();
	float boxMinPointArray[VMax] = { boxMin.x ,boxMin.y ,boxMin.z };
	float boxMaxPointArray[VMax] = { boxMax.x ,boxMax.y ,boxMax.z };
	VECTOR center1 = cap->GetWorldPoint1();
	VECTOR center2 = cap->GetWorldPoint2();
	VECTOR segment = VSub(center2, center1);
	VECTOR boxCenter = VScale(VAdd(boxMin, boxMax), 0.5f);
	float t = VDot(VSub(boxCenter, center1), segment) / VDot(segment, segment);
	t = std::clamp(t, 0.0f, 1.0f);
	VECTOR capsulePoint = VAdd(center1, VScale(segment, t));
	float capsulePointF[VMax] = { capsulePoint.x,capsulePoint.y, capsulePoint.z };
	float closestF[VMax];
	for (int i = 0; i < VMax; i++) {
		float max = std::max(boxMinPointArray[i], boxMaxPointArray[i]);
		float min = std::min(boxMinPointArray[i], boxMaxPointArray[i]);
		// ウデから見て一番近いBoxの点を探す
		closestF[i] = std::clamp(capsulePointF[i], min, max);
	}

	VECTOR closest = VGet(closestF[X], closestF[Y], closestF[Z]);

	// 最近点のベクトル
	VECTOR vec = VSub(capsulePoint, closest);
	// 中心までの距離
	float dis = VSize(vec);
	float radius = cap->GetRadius();
	if (dis > radius) return;

	// めり込んでる量
	float penetration = radius - dis;
	VECTOR dir = VNorm(vec);
	VECTOR pos = VScale(dir, penetration);
	GetTransform().AddPosition(pos);
}

void Player::OnTriggerEnter(Collider* _pOther) {
	if (_pOther->GetTag() == UnmovingWall || _pOther->GetTag() == Wall) {
		WallHit(_pOther);
	}
}

void Player::OnTriggerStay(Collider* _pOther) {
	if (_pOther->GetTag() == UnmovingWall || _pOther->GetTag() == Wall) {
		WallHit(_pOther);
	}
}

void Player::ChangeMaterialColor(int _matIndex, unsigned int _color) {
	GameObject::ChangeMaterialColor(_matIndex, _color);
	matColor = _color;
}

