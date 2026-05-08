#include "StageBase.h"
#include "../../../Component/Collider.h"
#include "../../ColliderObject/ColliderObject.h"
#include "../../../Other/CommonModule/MyVECTOR.h"
#include <vector>
#include "../../../Other/CommonModule/MyMath.h"

StageBase::StageBase(int mHandle)
	:GameObject(mHandle) {
	Start();
}

StageBase::~StageBase() {}

VECTOR StageBase::GetRandomPlayerSpawnPoint() {

	std::vector<int> canSpawnPoint;
	for (int i = 0; i < 4; i++) {
		if (!playerSpawnPoints[i].canSpawn) continue;
		canSpawnPoint.push_back(i);
	}

	int rand = MyMath::Random(0, canSpawnPoint.size() - 1);

	playerSpawnPoints[canSpawnPoint[rand]].canSpawn = false;

	return playerSpawnPoints[canSpawnPoint[rand]].pos;
}

VECTOR StageBase::GetRandomItemSpawnPoint(int& _spawnPointNum) {
	std::vector<int> canSpawnPoint;
	int size = itemSpawnPoints.size();
	for (int i = 0; i < size; i++) {
		if (!itemSpawnPoints[i].canSpawn) continue;
		canSpawnPoint.push_back(i);
	}

	if (canSpawnPoint.empty()) return VMinus;

	int rand = MyMath::Random(0, canSpawnPoint.size() - 1);
	_spawnPointNum = canSpawnPoint[rand];

	itemSpawnPoints[_spawnPointNum].canSpawn = false;

	return itemSpawnPoints[_spawnPointNum].pos;
}

void StageBase::CapRespawnItem(int _pointNum) {

	if (_pointNum == -1) return;

	itemSpawnPoints[_pointNum].canSpawn = true;
}

void StageBase::CapRespawnAllItem() {
	int size = itemSpawnPoints.size();
	for (int i = 0; i < size; i++) {
		itemSpawnPoints[i].canSpawn = true;
	}
}

void StageBase::ResetCanSpawnPlayer() {
	for (int i = 0; i < PLAYER_MAX; i++) {
		playerSpawnPoints[i].canSpawn = true;
	}
}

void StageBase::Setup() {
	ResetCanSpawnPlayer();
	CapRespawnAllItem();

	for (int i = 0; i < 4; i++) {
		walls[i]->GetCollider()->SetActive(true);
	}
}

void StageBase::Teardown() {
	for (int i = 0; i < 4; i++) {
		walls[i]->GetCollider()->SetActive(false);
	}
}

void StageBase::Start() {

	for (int i = 0; i < 4; i++) {
		std::unique_ptr<Collider> null;
 		walls.push_back(std::make_unique<ColliderObject>(null,nullptr, UnmovingWall));
		int frameIndex = MV1SearchFrame(modelHandle, WALL_NAME[i].data());
		int meshIndex = MV1GetFrameMesh(modelHandle,frameIndex, 0);
		VECTOR min = MV1GetMeshMinPosition(modelHandle, meshIndex);
		VECTOR max = MV1GetMeshMaxPosition(modelHandle, meshIndex);
		min = MyVECTOR::ChangeElementYZ(min);
		max = MyVECTOR::ChangeElementYZ(max);
		std::unique_ptr<Collider> box = std::make_unique<BoxCollider>(walls.back().get(), VScale(min, 100), VScale(max, 100));
		walls.back()->SetCollider(box);
		VECTOR pos = MV1GetFramePosition(modelHandle, frameIndex);
		walls.back()->GetTransform().SetPosition(pos);
		// ステージの判定は動かないから最初に一回だけ更新する
		walls.back()->GetCollider()->Update();
	}

	int parentFrameIndex = MV1SearchFrame(modelHandle, EXTRA_WALL_FRAME_PARENT_NAME.data());
	int childNum = MV1GetFrameChildNum(modelHandle, parentFrameIndex);

	for (int i = 0; i < childNum; i++) {
		std::unique_ptr<Collider> null;
		walls.push_back(std::make_unique<ColliderObject>(null, nullptr, Wall));
		int childFrameIndex = MV1GetFrameChild(modelHandle, parentFrameIndex, i);
		int meshIndex = MV1GetFrameMesh(modelHandle, childFrameIndex, 0);
		VECTOR min = MV1GetMeshMinPosition(modelHandle, meshIndex);
		VECTOR max = MV1GetMeshMaxPosition(modelHandle, meshIndex);
		min = MyVECTOR::ChangeElementYZ(min);
		max = MyVECTOR::ChangeElementYZ(max);
		std::unique_ptr<Collider> box = std::make_unique<BoxCollider>(walls.back().get(), VScale(min, 100), VScale(max, 100));
		walls.back()->SetCollider(box);
		VECTOR pos = MV1GetFramePosition(modelHandle, childFrameIndex);
		walls.back()->GetTransform().SetPosition(pos);
		// ステージの判定は動かないから最初に一回だけ更新する
		walls.back()->GetCollider()->Update();
	}

	for (int i = 0; i < 4; i++) {
		int frameIndex = MV1SearchFrame(modelHandle, PLAYER_SPAWN_POINT_NAME[i].data());
		VECTOR pos = MV1GetFramePosition(modelHandle, frameIndex);
		playerSpawnPoints[i].pos = pos;
		playerSpawnPoints[i].canSpawn = true;
	}

	// アイテムの出現位置を取得
	AddItemSpawnPoint();
}

void StageBase::AddItemSpawnPoint() {
	itemSpawnPoints.clear();

	int frameParent = MV1SearchFrame(modelHandle, ITEM_SPAWN_POINT_PARENT_NAME.data());

	if (frameParent == -1) return;

	int childNum = MV1GetFrameChildNum(modelHandle, frameParent);

	for (int i = 0; i < childNum; i++) {
		ItemSpawnPoint s;
		s.canSpawn = true;
		int frameChild = MV1GetFrameChild(modelHandle, frameParent, i);
		s.pos = MV1GetFramePosition(modelHandle, frameChild);
		s.pointNum = i;
		itemSpawnPoints.push_back(s);
	}
}
