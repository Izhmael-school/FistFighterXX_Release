#pragma once
#include <memory>
#include "DxLib.h"

class Player;

class PlayerUtility {
public:
	static void Update();
	static void Render();

	static Player* UsePlayer();
	static Player* UsePlayer(VECTOR pos);
	static void UnusePlayer(std::unique_ptr<Player> _player);
	static void UnuseAllPlayer();

	static Player* GetPlayer(int _playerNum);

	static void DeleteData();
	static int ActivePlayerNum();
	static Player* GetLastOnePlayer();
	static Player* GetMostHPPlayer();
};

