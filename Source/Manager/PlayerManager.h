#pragma once
#include "../Component/Singleton.h"
#include "ManagerBase.h"
#include "../Definition.h"
#include <memory>
#include <vector>
#include "../Object/GameObject/Character/Player/Player.h"
#include "../Generator/PlayerGenerator.h"

class PlayerManager : public Singleton<PlayerManager>,public ManagerBase {
private:
	void Start();

public:
	PlayerManager();
	~PlayerManager() = default;

	void Update() override;
	void Render() override;
	void DeleteData() override;

	Player* UsePlayer();
	void UnusePlayer(std::unique_ptr<Player> _player);
	void UnuseAllPlayer();

	inline int ActivePlayerNum() {return playerArray.size(); }

	Player* GetPlayer(int _playerNum);
	Player* GetMostHpPlayer();
	Player* GetLastOnePlayer();


private:
	std::vector<std::unique_ptr<Player>> playerArray;
	std::vector<std::unique_ptr<Player>> unusePlayerArray;
	std::unique_ptr<PlayerGenerator> generator;
};

