#include "CollisionManager.h"
#include "../Component/Collider.h"
#include"../Object/Object.h"

CollisionManager::CollisionManager()
	:pColliderArray() {}

CollisionManager::~CollisionManager() {
	UnRegisterAll();
}

void CollisionManager::Update() {
	int size = static_cast<int>(pColliderArray.size());

	// “¯‚¶‚Æ‚±‚ë‚ğXV‚µ‚È‚¢‚½‚ß‚É j ‚Í i + 1
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			Collider* c1 = pColliderArray[i];
			Collider* c2 = pColliderArray[j];

			// Null‚©—LŒø‚¶‚á‚È‚¯‚ê‚ÎŸ
			if (!c1 || !c2) continue;
			if (!c1->IsActive() || !c2->IsActive()) continue;

			// Õ“ËŒ‹‰Ê‚ÌXV
			result[i][j].current = CheckHit(c1, c2);

			// “–‚½‚Á‚½uŠÔ
			if (result[i][j].current && !result[i][j].prev) {
				c1->GetOwner()->OnTriggerEnter(c2);
				c2->GetOwner()->OnTriggerEnter(c1);
			}
			// “–‚½‚Á‚Ä‚éŠÔ
			if (result[i][j].current && result[i][j].prev) {
				c1->GetOwner()->OnTriggerStay(c2);
				c2->GetOwner()->OnTriggerStay(c1);
			}
			// —£‚ê‚½uŠÔ
			if (!result[i][j].current && result[i][j].prev) {
				c1->GetOwner()->OnTriggerExit(c2);
				c2->GetOwner()->OnTriggerExit(c1);
			}

			// ‘O‚ÌƒtƒŒ[ƒ€‚É“ü‚ê‘Ö‚¦‚é
			result[i][j].prev = result[i][j].current;
		}
	}

}

void CollisionManager::Render() {
	for (auto& pCol : pColliderArray) {
		if (!pCol || !pCol->IsActive()) continue;
		pCol->Render();
	}
}

void CollisionManager::Register(Collider* _pCol) {
	// Šù‚É“o˜^‚µ‚Ä‚¢‚ê‚Î–ß‚é
	if (std::find(pColliderArray.begin(), pColliderArray.end(), _pCol) != pColliderArray.end()) return;

	pColliderArray.push_back(_pCol);

	// “o˜^‚³‚ê‚½ƒRƒ‰ƒCƒ_[—p‚Ìs‚ğ’Ç‰Á
	result.push_back(std::vector<CollisionResult>());

	int size = static_cast<int>(pColliderArray.size());

	for (int i = 0; i < size; i++) {
		CollisionResult r;
		while (result[i].size() < size) {
			result[i].push_back(r);
		}
	}
}

void CollisionManager::UnRegister(Collider* _pCol) {
	// “o˜^‚µ‚Ä–³‚¯‚ê‚Î–ß‚é
	auto itr = std::find(pColliderArray.begin(), pColliderArray.end(), _pCol);
	if (itr == pColliderArray.end()) return;

	int index = static_cast<int>(std::distance(pColliderArray.begin(), itr));
	for (auto& r : result) {
		r.erase(r.begin() + index);
	}

	// —v‘f‚Ìíœ
	pColliderArray.erase(itr);
	result.erase(result.begin() + index);
}

void CollisionManager::UnRegisterAll() {
	pColliderArray.clear();
	pColliderArray.shrink_to_fit();
	result.clear();
	result.shrink_to_fit();
}

bool CollisionManager::CheckHit(Collider* _pCol1, Collider* _pCol2) {
	return _pCol1->CheckHit(_pCol2);
}
