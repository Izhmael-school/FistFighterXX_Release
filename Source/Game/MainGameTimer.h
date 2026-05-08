#pragma once
class MainGameTimer {
public:
	MainGameTimer() = default;
	~MainGameTimer() = default;

public:
	static void Update();

	static void Reset();

	static inline int GetGameTime() { return static_cast<int>(gameTimer); }
private:
	static float gameTimer;
};

