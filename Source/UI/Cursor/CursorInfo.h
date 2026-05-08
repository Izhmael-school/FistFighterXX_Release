#pragma once
#include <vector>

class PlayerCursor;

class CursorInfo {
public:
	CursorInfo();
	~CursorInfo() = default;

public:
	static void Update();
	static void Render();

	// 指定の範囲内にいるか(主にボタン用)
	static bool InPoint(float x1 ,float y1,float x2,float y2);
private:
	static std::vector<PlayerCursor*> cursorArray;
};

