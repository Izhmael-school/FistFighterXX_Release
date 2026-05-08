#include "PlayerManager.h"
#include "../Utility/CollisionUtility.h"

PlayerManager::PlayerManager() { Start(); }

void PlayerManager::Start() {
	generator = std::make_unique<PlayerGenerator>();
}

void PlayerManager::Update() {
	int index = 0;

	for (auto& p : playerArray) {
		if (!p) continue;

		if (p->GetPortNum() == -1)
			p->SetPortNum(index);

		p->Update();

		index++;
	}

	// 非表示のプレイヤーを未使用配列に入れる
	for (int i = 0; i < playerArray.size();) {
		if (playerArray[i]->IsVisible()) i++;
		else {
			UnusePlayer(std::move(playerArray[i]));
			playerArray.erase(playerArray.begin() + i);
		}
	}
}

void PlayerManager::Render() {
	for (auto& p : playerArray) {
		p->Render();
	}
}

void PlayerManager::DeleteData() {
	UnuseAllPlayer();

	for (auto& p : unusePlayerArray) {
		p->DeleteModel();
	}
}

Player* PlayerManager::UsePlayer() {
	std::unique_ptr<Player> _player;

	// 無かったら作る
	if (unusePlayerArray.size() == 0)
		_player = generator->Create();
	else {
		_player = std::move(unusePlayerArray.front());
		unusePlayerArray.erase(unusePlayerArray.begin());
	}

	playerArray.push_back(std::move(_player));
	playerArray.back()->SetPlayerNumber(playerArray.size());
	playerArray.back()->Setup();

	return playerArray.back().get();
}

void PlayerManager::UnusePlayer(std::unique_ptr<Player> _player) {
	if (!_player) return;

	_player->Teardown();
	unusePlayerArray.push_back(std::move(_player));
}

void PlayerManager::UnuseAllPlayer() {
	while (playerArray.size() != 0) {
		std::unique_ptr<Player> _player = std::move(playerArray.front());
		playerArray.erase(playerArray.begin());
		_player->Teardown();
		unusePlayerArray.push_back(std::move(_player));
	}

	playerArray.shrink_to_fit();
}

Player* PlayerManager::GetPlayer(int _playerNum) {
	for (auto& p : playerArray) {
		if (p->GetPlayerNumber() != _playerNum) continue;

		return p.get();
	}

	return nullptr;
}

Player* PlayerManager::GetMostHpPlayer() {
	Player* player = nullptr;

	for (int i = 0; i < playerArray.size(); i++) {
		if (!player) {
			player = playerArray[i].get();
			continue;
		}

		if(playerArray[i]->GetCurrentHP() > player->GetCurrentHP())
			player = playerArray[i].get();
			
	}

	return player;
}

Player* PlayerManager::GetLastOnePlayer() {
	if (playerArray.size() > 1 || playerArray.size() == 0) return nullptr;

	return playerArray.front().get();
}

