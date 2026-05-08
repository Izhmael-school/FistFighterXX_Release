#pragma once
#include "DxLib.h"
#include "../Definition.h"

class Object;
class SphereCollider;
class CapsuleCollider;
class BoxCollider;


/// <summary>
/// ìñÇΩÇËîªíËÇÃäÓíÍÉNÉâÉX
/// </summary>
class Collider {
protected:
	bool isActive;
	Object* pObject;

private:
	void Start();
public:
	Collider(Object* _pObj);
	virtual ~Collider();

	virtual void Update() = 0;
	virtual void Render() = 0;

	inline bool IsActive() const { return isActive; }
	inline void SetActive(bool _isActive) { isActive = _isActive; }
	inline Object* GetOwner() const { return pObject; }
	inline void SetOwner(Object* _obj) { pObject = _obj; }
	Tag GetTag();

	virtual bool CheckHit(Collider* _other) = 0;
	virtual bool CheckHitSphere(SphereCollider* _sph) = 0;
	virtual bool CheckHitCapsule(CapsuleCollider* _cap) = 0;
	virtual bool CheckHitBox(BoxCollider* _box) = 0;
};

constexpr int vertexNum = 8;
constexpr int edges[12][2] = {
	{0,1}, {1,3}, {3,2}, {2,0}, // íÍñ 
	{4,5}, {5,7}, {7,6}, {6,4}, // è„ñ 
	{0,4}, {1,5}, {2,6}, {3,7}  // ècï˚å¸
};

/// <summary>
/// Boxå^ìñÇΩÇËîªíË
/// </summary>
class BoxCollider : public Collider {
private:
	VECTOR originMinPoint;
	VECTOR originMaxPoint;


	VECTOR originVertex[vertexNum];
	VECTOR localVertex[vertexNum];
	VECTOR worldVertex[vertexNum];

private:
	bool OverlapCheck(VECTOR minV1, VECTOR maxV1, VECTOR minV2, VECTOR maxV2);

public:
	BoxCollider(Object* _pObj, VECTOR _min, VECTOR _max);
	~BoxCollider() = default;

	void Update() override;
	void Render() override;

	inline VECTOR GetMinPoint() const { return worldVertex[0]; }
	inline VECTOR GetMaxPoint() const { return worldVertex[7]; }

	bool CheckHit(Collider* _other) override;
	bool CheckHitBox(BoxCollider* _box) override;
	bool CheckHitSphere(SphereCollider* _sph) override;
	bool CheckHitCapsule(CapsuleCollider* _cap) override;
};

/// <summary>
/// Sphereå^ìñÇΩÇËîªíË
/// </summary>
class SphereCollider : public Collider {
private:
	VECTOR localCenter;
	VECTOR worldCenter;
	float radius;

public:
	SphereCollider(Object* _pObj, VECTOR _offset, float _radius);
	~SphereCollider() = default;

	void Update() override;
	void Render() override;

	inline float GetRadius() const { return radius; }
	inline void SetRadius(float _r) { radius = _r; }
	inline void SetOffset(VECTOR _offset) { localCenter = _offset; }
	inline VECTOR GetCenter() const { return worldCenter; }

	bool CheckHit(Collider* _other) override;
	bool CheckHitBox(BoxCollider* _box) override;
	bool CheckHitSphere(SphereCollider* _sph) override;
	bool CheckHitCapsule(CapsuleCollider* _cap) override;
};

/// <summary>
/// Capsuleå^ìñÇΩÇËîªíË
/// </summary>
class CapsuleCollider : public Collider {
private:
	VECTOR originPoint1, originPoint2;
	float radius;
	VECTOR offset;
	VECTOR localPoint1, localPoint2;
	VECTOR worldPoint1, worldPoint2;

public:
	CapsuleCollider(Object* _pObj, VECTOR _p1, VECTOR _p2, float _r);
	~CapsuleCollider() = default;

	void Update() override;
	void Render() override;

	inline VECTOR GetWorldPoint1() const { return worldPoint1; }
	inline VECTOR GetWorldPoint2() const { return worldPoint2; }

	inline float GetRadius() const { return radius; }
	inline void SetRadius(float _r) { radius = _r; }

	bool CheckHit(Collider* _other) override;
	bool CheckHitBox(BoxCollider* _box) override;
	bool CheckHitSphere(SphereCollider* _sph) override;
	bool CheckHitCapsule(CapsuleCollider* _cap) override;
};