#pragma once
#include "../GameObject.h"
#include <array>
#include <vector>
#include <memory>
#include <string_view>

class ColliderObject;

struct PlayerSpawnPoint {
	VECTOR pos = VZero;
	bool canSpawn = false;
};

struct ItemSpawnPoint {
	VECTOR pos = VZero;
	bool canSpawn = false;
	int pointNum = -1;
};

constexpr std::string_view WALL_NAME[4] = {
	"BottomWall",
	"TopWall",
	"RightWall",
	"LeftWall"
};

constexpr std::string_view PLAYER_SPAWN_POINT_NAME[4] = {
	"PlayerSpawnPoint1",
	"PlayerSpawnPoint2",
	"PlayerSpawnPoint3",
	"PlayerSpawnPoint4"
};

constexpr std::string_view ITEM_SPAWN_POINT_PARENT_NAME = "ItemSpawn";

constexpr std::string_view EXTRA_WALL_FRAME_PARENT_NAME = "ExtraWall";

class StageBase : public GameObject{
public:
	StageBase(int mHandle);
	~StageBase();

	VECTOR GetRandomPlayerSpawnPoint();

	VECTOR GetRandomItemSpawnPoint(int& _spawnPointNum);

	// 指定のポジションにアイテムが再スポーンできるようになる
	void CapRespawnItem(int _pointNum);
	// 全てのポジションにイテムが再スポーンできるようになる
	void CapRespawnAllItem();

	void ResetCanSpawnPlayer();

	void Setup() override;

	void Teardown() override;
private:
	void Start() override;

	void AddItemSpawnPoint();
private:
	std::vector<std::unique_ptr<ColliderObject>> walls;
	std::array<PlayerSpawnPoint, 4> playerSpawnPoints;
	std::vector<ItemSpawnPoint> itemSpawnPoints;
};

