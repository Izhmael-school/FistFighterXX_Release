#pragma once
#include "../Character.h"
#include "PlayerController.h"
#include <memory>
#include <algorithm>
#include <string_view>
#include "../../../../Other/Utility/Span.h"
#include <vector>

class ArmBase;
constexpr std::string_view attachFrameName[ArmMax] = { "RightArmPoint" , "LeftArmPoint" };

struct PlayerStatus {
	int currentHP;
	int maxHP;
	int currentStamina;
	int maxStamina;
	int currentOCValue;
	int maxOCValue;
};

class Player : public Character {

public:
	Player(int _mHandle,  int _portNum, VECTOR _pos = VZero, Tag _tag = NoTag);
	~Player();

	void Start() override;
	void Update() override;
	void Render() override;

	void Setup() override;
	void Teardown() override;

	float GetMoveSpeed() const { return moveSpeed; }

	void SetPortNum(int _portNum);
	inline int GetPortNum() { return controller.GetPortNum(); }

	void ChangeArm(ArmPos _armPos, ArmType _type);
	void ShotArm(ArmPos _armPos);
	void ReturnArm(ArmPos _armPos);

	inline int GetShotNum() const { return shotNum; }

	inline ArmBase* GetArm(ArmPos _pos) { return equipArm[_pos]; }

	bool IsDead() const { return status.currentHP <= 0; }
	void DeadExecute();

	// ‘‰Á
	inline void AddHP(int _value) { status.currentHP = std::clamp(status.currentHP + _value, 0, status.maxHP); }
	inline void AddStamina(int _value) { status.currentStamina = std::clamp(status.currentStamina + _value, 0, status.maxStamina); }
	inline void AddOC(int _value) { status.currentOCValue = std::clamp(status.currentOCValue + _value, 0, status.maxOCValue); }

	inline void SubHP(int _value) { status.currentHP = std::clamp(status.currentHP - _value, 0, status.maxHP); }
	inline void SubStamina(int _value) { status.currentStamina = std::clamp(status.currentStamina - _value, 0, status.maxStamina); }
	inline void SubOC(int _value) { status.currentOCValue = std::clamp(status.currentOCValue - _value, 0, status.maxOCValue); }

	inline int GetCurrentHP() const { return status.currentHP; }
	inline int GetMaxHP() const { return status.maxHP; }

	inline int GetCurrentStamina() const { return status.currentStamina; }
	inline int GetMaxStamina() const { return status.maxStamina; }

	inline void SetPlayerNumber(int _num) { playerNumber = _num; }
	inline int GetPlayerNumber() { return playerNumber; }

	void WallHit(Collider* _wall);

	void OnTriggerEnter(Collider* _pOther) override;
	void OnTriggerStay(Collider* _pOther) override;

	inline unsigned int GetMatColor() { return matColor; }

	void ChangeMaterialColor(int _matIndex, unsigned int _color) override;
private:
	PlayerStatus status;
	float moveSpeed;
	ArmBase* equipArm[ArmMax];
	int shotNum;

	int playerNumber;
	bool useDeadExecute;

	Span healStamina;
	Span consumeStamina;
	unsigned int matColor;
	std::vector<int> moveUIIDArray;

public:
	PlayerController controller;
};

