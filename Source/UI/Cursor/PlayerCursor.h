#pragma once
#include "../UIBase.h"

class PlayerCursor : public UIBase {
public:
	PlayerCursor(int _portNum);
	~PlayerCursor();

private:
	void Start();

public:
	void Update() override;
	void Render() override;

private:
	int portNum;
	float moveSpeed;
};

