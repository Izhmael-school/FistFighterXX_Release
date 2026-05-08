#pragma once
#include <vector>
#include "../Definition.h"
#include <string_view>

struct BattleSetting {
	int currentSelect = 0;
	int color = 0;
	ArmType left = Punch;
	ArmType right = Punch;
	int portNum;
};

const unsigned int colorPreset[PLAYER_COLOR_MAX] = { red,blue,green,cyan,magenta,yellow,white,black };


// ゲームの参加状況管理クラス
class GameCondition {
private:
	static int joinNum;
	static int deadNum;
	static std::vector<BattleSetting> battleSetting;
	static int stageNum;
public:
	GameCondition() = default;
	~GameCondition() = default;

	inline static int GetJoinNum() { return joinNum; }
	inline static void SetJoinNum(int _joinNum) { joinNum = _joinNum; }
	inline static int GetStageNum() { return stageNum; }
	inline static void SetStageNum(int _stageNum) { stageNum = _stageNum; }
	inline static void AddDeadNum() { deadNum++; }
	inline static void ResetDeadNum() { deadNum = 0; }
	inline static bool IsPlayerLastOne() { return joinNum - deadNum == 1; }
	inline static void AddBattleSetting(BattleSetting _b) { battleSetting.push_back(_b); }
	inline static BattleSetting GetBattleSetting(int i) { return battleSetting[i]; }
	inline static void ResetBattleSetting() { battleSetting.clear(); }
};

