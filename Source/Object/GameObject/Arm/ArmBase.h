#pragma once
#include "../GameObject.h"
#include "ArmController.h"
#include <string>
#include <memory>

class Player;
class ArmEffectBase;
class MoveGauge;

struct ArmStatus {
	int attackValue;
	int speedValue;
	int consumeStaminaValue;
	int maxDurability;
	int currentDurability;
	int strength;
};

class ArmBase : public GameObject {
private:
	void Start() override;
public:
	ArmBase(int _mHandle,VECTOR _pos,Player* _owner, std::unique_ptr<ArmEffectBase> _effect);
	~ArmBase() = default;

	void Update() override;
	void Render() override;
	void Setup() override;
	void Teardown() override;

	void ShotStart();
	void ShotEnd();

	void OnTriggerEnter(Collider* _pOther) override;
	void OnTriggerStay(Collider* _pOther) override;
	void OnTriggerExit(Collider* _pOther) override;

	inline bool IsShot() const { return isShot; }
	inline void SetShot(bool _isShot) { isShot = _isShot; }
	// ステータスの取得
	inline int GetBaseAttackValue() const { return status.attackValue; }
	inline int GetAttackValue() const { return status.attackValue * shotTime; }
	inline float GetShotTime() const { return shotTime; }
	inline float GetMoveSpeed() const { return static_cast<float>(status.speedValue); }
	inline int GetConsumeStamina() const { return status.consumeStaminaValue; }
	inline int GetCurrentDurability() const { return status.currentDurability; }
	inline int GetStrength() const { return status.strength; }

	inline void SetArmType(ArmType _type) { armType = _type; }
	inline ArmType GetArmType() const { return armType; }
	inline Player* GetOwner() const { return owner; }
	inline void SetOwner(Player* _owner) { owner = _owner; }
	void ArmAttach(std::string _frameName);
	inline ArmPos GetArmPos() const { return armPos; }
	inline void SetArmPos(ArmPos _armPos) { armPos = _armPos; }
	inline void SetStatus(ArmStatus _status) { status = _status; }
	inline void SetPortNum(int _portNum) { controller.SetPortNum(_portNum); }

	inline int GetMaxDurability() const { return status.maxDurability; }
	inline void SubDurability(int _v = 1) { status.currentDurability -= _v; }
	inline ArmController GetController() const { return controller; }
private:
	ArmStatus status;
	ArmController controller;
	std::unique_ptr<ArmEffectBase> effect;
	Player* owner;

	ArmPos armPos;

	ArmType armType;

	MATRIX correctionMat;

	MoveGauge* gauge;

	float shotTime;
	bool isShot;
	int attachFrameHandle;
	int attachModelHandle;
};

