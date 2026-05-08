#include "PlayerGenerator.h"
#include "DxLib.h"
#include "../Object/GameObject/Character/Player/Player.h"
#include "../Definition.h"

PlayerGenerator::PlayerGenerator() 
	:originPlayerMHandle(-1)
{ Start(); }

PlayerGenerator::~PlayerGenerator() {}

void PlayerGenerator::Start() {
	LoadModel();
}

void PlayerGenerator::LoadModel() {
	originPlayerMHandle = MV1LoadModel(PLAYER_MODEL_FILEPATH("Player"));
}


std::unique_ptr<Player> PlayerGenerator::Create() {
	int dupMHandle = MV1DuplicateModel(originPlayerMHandle);

	std::unique_ptr<Player> player = std::make_unique<Player>(dupMHandle,-1,VZero,PlayerCharacter);

	return player;
}

void PlayerGenerator::DeleteOriginModelHandle() {
	MV1DeleteModel(originPlayerMHandle);
}
