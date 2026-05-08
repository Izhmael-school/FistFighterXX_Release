#include "PlayerUtility.h"
#include "../Manager/PlayerManager.h"

void PlayerUtility::Update() {
    PlayerManager::GetInstance().Update();
}

void PlayerUtility::Render() {
    PlayerManager::GetInstance().Render();
}

Player* PlayerUtility::UsePlayer() {
    return PlayerManager::GetInstance().UsePlayer();
}

Player* PlayerUtility::UsePlayer(VECTOR pos) {
    Player* p = PlayerManager::GetInstance().UsePlayer();
    p->GetTransform().SetPosition(pos);
    p->GetTransform().Update();
    MV1SetMatrix(p->GetModelHandle(), p->GetTransform().GetMatrix());
    return p;
}

void PlayerUtility::UnusePlayer(std::unique_ptr<Player> _player) {
    PlayerManager::GetInstance().UnusePlayer(std::move(_player));
}

void PlayerUtility::UnuseAllPlayer() {
    PlayerManager::GetInstance().UnuseAllPlayer();
}

Player* PlayerUtility::GetPlayer(int _playerNum) {
    return PlayerManager::GetInstance().GetPlayer(_playerNum);
}

void PlayerUtility::DeleteData() {
    PlayerManager::GetInstance().DeleteData();
}

int PlayerUtility::ActivePlayerNum() {
    return PlayerManager::GetInstance().ActivePlayerNum();
}

Player* PlayerUtility::GetLastOnePlayer() {
    return PlayerManager::GetInstance().GetLastOnePlayer();
}

Player* PlayerUtility::GetMostHPPlayer() {
    return PlayerManager::GetInstance().GetMostHpPlayer();
}
