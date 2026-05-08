#pragma once

class Player;

class PlayerController {
public:
	PlayerController() = default;
	~PlayerController() = default;

	void Update();

	void Move();
	inline void SetPortNum(int _index) { padPortNum = _index; }
	inline int GetPortNum() { return padPortNum; }
	inline void SetOwner(Player* _owner) { owner = _owner; }

private:
	int padPortNum = -1;
	Player* owner = nullptr;
	float dashSpan = 2.0f;
	float lastDashTime = dashSpan;
	float dashTime = 0.1f;
	bool isDash = false;
};

