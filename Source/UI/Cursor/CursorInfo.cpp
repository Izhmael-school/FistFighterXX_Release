#include "CursorInfo.h"
#include "PlayerCursor.h"
#include "../../Utility/InputUtility.h"
#include "../../Manager/UIManager.h"

std::vector<PlayerCursor*> CursorInfo::cursorArray;

CursorInfo::CursorInfo() {}

void CursorInfo::Update() {
	int padNum = GetJoypadNum();
	int size = cursorArray.size();

	// •¡”‘Î‰‚µ‚Ä‚¢‚é‚ª‘¼‚ğ‚»‚ê—p‚É‚·‚é‚Ì‚Í‚ß‚ñ‚Ç‚­‚³‚¢‚½‚ßˆê‚Â‚¾‚¯
	if (size < padNum && size != 1) {

		cursorArray.push_back(UIManager::GetInstance().CreatePlayerCursor(Menu, 0));

	}
	else if (size == padNum) {
		if (padNum > 0) {

			for (int i = 0; i < padNum; i++) {
				if (!InputUtility::GetPad(i))
					cursorArray[i]->SetActive(false);
				else
					cursorArray[i]->SetActive(true);
			}
		}

	}
	else if (size > 0 && padNum == 0) {
		for (int i = 0; i < size; i++) {
			cursorArray[i]->SetActive(false);
		}
	}
}

void CursorInfo::Render() {

}

bool CursorInfo::InPoint(float x1, float y1, float x2, float y2) {

	for (auto& c : cursorArray) {
		float x = c->GetX();
		float y = c->GetY();
		if (x1 <= x && x <= x2 && y1 <= y && y <= y2)
			return true;
	}

	return false;
}
