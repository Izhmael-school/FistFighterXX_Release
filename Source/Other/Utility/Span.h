#pragma once
class Span {
public:
	Span() = default;
	~Span() = default;

public:
	// 時間の更新
	void UpdateTime();
	// 指定時間経過したか
	bool IsTime();
	// 指定時間経過したか(経過時間のリセットをしない)
	bool IsTimeNoReset();
	// 指定時間指定
	inline void SetTargetTime(float _t) { targetTime = _t; }
	// 現在の時間を取得
	inline float GetCurrentTime() const { return currentTime; }
	// カウントダウン形式で取得
	inline float GetCountDownTime() const { return targetTime - currentTime; }
	// 経過時間の初期化
	inline void ResetCurrentTime() { currentTime = 0.0f; }

private:
	float currentTime = 0.0f;
	float targetTime = 0.1f;
};

