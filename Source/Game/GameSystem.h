#pragma once
class GameSystem {
private:
	static bool isEnd;

public:
	static bool IsEnd() { return isEnd; }
	static void SetEnd(bool _isEnd) { isEnd = _isEnd; }
};

