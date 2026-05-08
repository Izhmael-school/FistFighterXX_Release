#include "Collider.h"
#include "../Other/CommonModule/MyMath.h"
#include "../Other/CommonModule/MyVECTOR.h"
#include "../Object/Object.h"
#include "../Definition.h"
#include <cmath>
#include "../Utility/CollisionUtility.h"
#include <algorithm>

Collider::Collider(Object* _pObj)
	:isActive(true)
	, pObject(_pObj) {
	Start();
}

Collider::~Collider() {
	CollisionUtility::UnRegister(this);
}

void Collider::Start() {
	CollisionUtility::Register(this);
}

BoxCollider::BoxCollider(Object* _pObj, VECTOR _min, VECTOR _max)
	:Collider(_pObj)
	, originMinPoint(_min)
	, originMaxPoint(_max)
	, originVertex()
	, localVertex()
	, worldVertex() {
	// 無回転状態での各頂点データの初期化
	for (int i = 0; i < vertexNum; i++) {
		// 16進数で〇桁目が1かどうか調べる
		originVertex[i] = VGet(
			(i & 1) ? originMaxPoint.x : originMinPoint.x,
			(i & 2) ? originMaxPoint.y : originMinPoint.y,
			(i & 4) ? originMaxPoint.z : originMinPoint.z
		);
	}
}

void BoxCollider::Update() {
	if (!isActive) return;

	// 座標の取得
	VECTOR pos = pObject->GetTransform().GetPosition();
	VECTOR rot = pObject->GetTransform().GetRotation();

	// Y軸中心の回転行列を取得する
	MATRIX rotY = MGetRotY(MyMath::Deg2Rad(rot.y));
	// 原点からの平行移動行列を取得する
	MATRIX trans = MGetTranslate(pos);

	for (int i = 0; i < vertexNum; i++) {
		// 各頂点のローカルを求める
		// VECTOR * MATRIX で回転後の座標
		localVertex[i] = VTransform(originVertex[i], rotY);
		// 各頂点のワールド座標を求める
		worldVertex[i] = VTransform(localVertex[i], trans);
	}
}

void BoxCollider::Render() {
	if (!isActive) return;

	for (int i = 0; i < 12; i++) {
		DrawLine3D(worldVertex[edges[i][0]], worldVertex[edges[i][1]], green);
	}
}

bool BoxCollider::OverlapCheck(VECTOR minV1, VECTOR maxV1, VECTOR minV2, VECTOR maxV2) {
	if (minV1.x > maxV2.x && minV2.x > maxV1.x) return false;
	if (minV1.y > maxV2.y && minV2.y > maxV1.y) return false;
	if (minV1.z > maxV2.z && minV2.z > maxV1.z) return false;

	return true;
}

bool BoxCollider::CheckHit(Collider* _other) {
	return _other->CheckHitBox(this);
}

bool BoxCollider::CheckHitBox(BoxCollider* _box) {
	// AABB
	return OverlapCheck(this->GetMinPoint(), this->GetMaxPoint(), _box->GetMinPoint(), _box->GetMaxPoint());
}

bool BoxCollider::CheckHitSphere(SphereCollider* _sph) {
	VECTOR sphereCenter = _sph->GetCenter();
	VECTOR boxMin = this->GetMinPoint();
	VECTOR boxMax = this->GetMaxPoint();
	float sphereCenterArray[VMax] = { sphereCenter.x ,sphereCenter.y ,sphereCenter.z };
	float boxMinPointArray[VMax] = { boxMin.x ,boxMin.y ,boxMin.z };
	float boxMaxPointArray[VMax] = { boxMax.x ,boxMax.y ,boxMax.z };

	float d[VMax] = { 0,0,0 };

	for (int i = 0; i < VMax; i++) {
		float max = std::max(boxMinPointArray[i], boxMaxPointArray[i]);
		float min = std::min(boxMinPointArray[i], boxMaxPointArray[i]);
		float closest = std::clamp(sphereCenterArray[i], min,max);
		d[i] = sphereCenterArray[i] - closest;
	}

	float dis = MyMath::Distance(d[X], d[Y], d[Z]);

	return dis <= std::powf(_sph->GetRadius(), 2);
}

bool BoxCollider::CheckHitCapsule(CapsuleCollider* _cap) {
	VECTOR capsulePoint1 = _cap->GetWorldPoint1();
	VECTOR capsulePoint2 = _cap->GetWorldPoint2();

	VECTOR dir = MyMath::Dir(capsulePoint2, capsulePoint1);
	
	VECTOR boxMaxAddRadius = MyVECTOR::VAddFloat(this->GetMaxPoint(), _cap->GetRadius());
	VECTOR boxMinSubRadius = MyVECTOR::VSubFloat(this->GetMinPoint(), _cap->GetRadius());

	VECTOR t1 = MyVECTOR::VDiv(VSub(boxMaxAddRadius, capsulePoint1), dir);
	VECTOR t2 = MyVECTOR::VDiv(VSub(boxMinSubRadius, capsulePoint1), dir);

	VECTOR tMin = VGet(std::min(t1.x, t2.x), std::min(t1.y, t2.y), std::min(t1.z, t2.z));
	VECTOR tMax = VGet(std::max(t1.x, t2.x), std::max(t1.y, t2.y), std::max(t1.z, t2.z));

	if (capsulePoint1.x < boxMinSubRadius.x || capsulePoint1.x > boxMaxAddRadius.x) return false;
	if (capsulePoint1.y < boxMinSubRadius.y || capsulePoint1.y > boxMaxAddRadius.y) return false;
	if (capsulePoint1.z < boxMinSubRadius.z || capsulePoint1.z > boxMaxAddRadius.z) return false;

	float enter = MyMath::MaxF(tMin.x, tMin.y, tMin.z);
	float exit = MyMath::MinF(tMax.x, tMax.y, tMax.z);
	
	return 0 <= exit && enter <= 1 && enter <= exit;
}

SphereCollider::SphereCollider(Object* _pObj, VECTOR _offset, float _radius)
	:Collider(_pObj)
	, localCenter(_offset)
	, worldCenter(VZero)
	, radius(_radius) {}

void SphereCollider::Update() {
	if (!isActive || !pObject) return;

	worldCenter = VAdd(pObject->GetTransform().GetPosition(), localCenter);
}

void SphereCollider::Render() {
	if (!isActive) return;

	DrawSphere3D(worldCenter, radius, 16, green, green, false);
}

bool SphereCollider::CheckHit(Collider* _other) {
	return _other->CheckHitSphere(this);
}

bool SphereCollider::CheckHitBox(BoxCollider* _box) {
	return _box->CheckHitSphere(this);
}

bool SphereCollider::CheckHitSphere(SphereCollider* _sph) {
	// 二点間の差分を求める
	VECTOR delta = VSub(this->GetCenter(), _sph->GetCenter());

	if (VSize(delta) <= this->GetRadius() + _sph->GetRadius())
		return true;

	return false;
}

bool SphereCollider::CheckHitCapsule(CapsuleCollider* _cap) {
	// 線分と点の最近点間の距離を求める
	float dis = Segment_Point_MinLength(
		_cap->GetWorldPoint1(),
		_cap->GetWorldPoint2(),
		this->GetCenter());

	if (dis <= _cap->GetRadius() + this->GetRadius())
		return true;

	return false;
}

CapsuleCollider::CapsuleCollider(Object* _pObj, VECTOR _p1, VECTOR _p2, float _r)
	:Collider(_pObj)
	, originPoint1(_p1)
	, originPoint2(_p2)
	, radius(_r)
	, offset(VScale(VUp, _r))
	, localPoint1(VZero)
	, localPoint2(VZero)
	, worldPoint1(VZero)
	, worldPoint2(VZero) {}

void CapsuleCollider::Update() {
	if (!isActive) return;

	MATRIX mat = pObject->GetTransform().GetMatrix();

	// 回転・移動を行列から取得
	MATRIX rot = MGetRotElem(mat);
	VECTOR trans = MGetTranslateElem(mat);

	// ローカル → ワールド変換
	localPoint1 = VTransform(originPoint1, rot);
	localPoint2 = VTransform(originPoint2, rot);

	worldPoint1 = VAdd(localPoint1, trans);
	worldPoint2 = VAdd(localPoint2, trans);
}

void CapsuleCollider::Render() {
	if (!isActive) return;

	DrawCapsule3D(worldPoint1, worldPoint2, radius, 16, green, green, false);
}

bool CapsuleCollider::CheckHit(Collider* _other) {
	return _other->CheckHitCapsule(this);
}

bool CapsuleCollider::CheckHitBox(BoxCollider* _box) {
	return _box->CheckHitCapsule(this);
}

bool CapsuleCollider::CheckHitSphere(SphereCollider* _sph) {
	return _sph->CheckHitCapsule(this);
}

bool CapsuleCollider::CheckHitCapsule(CapsuleCollider* _cap) {
	// 二線分同士の最近点の距離を求める
	float dis = Segment_Segment_MinLength(
		this->GetWorldPoint1(),
		this->GetWorldPoint2(),
		_cap->GetWorldPoint1(),
		_cap->GetWorldPoint2());

	if (dis <= this->GetRadius() + _cap->GetRadius())
		return true;

	return false;
}

Tag Collider::GetTag() {
	return pObject->GetTag();
}
