#include "InputUtility.h"
#include "../Manager/InputManager.h"
#include "../Other/Pad/PadBase.h"

void InputUtility::Update() { InputManager::GetInstance().Update(); }

bool InputUtility::IsKey(int _key) { return InputManager::GetInstance().IsKey(_key); }

bool InputUtility::IsKeyDown(int _key) { return InputManager::GetInstance().IsKeyDown(_key); }

bool InputUtility::IsKeyUp(int _key) { return InputManager::GetInstance().IsKeyUp(_key); }

bool InputUtility::IsMouse(int _mouse) { return InputManager::GetInstance().IsMouse(_mouse); }

bool InputUtility::IsMouseDown(int _mouse) { return InputManager::GetInstance().IsMouseDown(_mouse); }

bool InputUtility::IsMouseUp(int _mouse) { return InputManager::GetInstance().IsMouseUp(_mouse); }

bool InputUtility::IsAllPad(int _pad) {
	for (int i = 0; i < MAX_PAD_PORT; i++) {
		PadBase* pad = InputManager::GetInstance().GetPad(i);

		if (!pad) continue;

		if (!pad->IsPad(_pad)) continue;
		return true;
	}
	return false;
}

bool InputUtility::IsPad(int _index, int _pad) {
	PadBase* pad = InputManager::GetInstance().GetPad(_index);
	if (!pad) return false;
	return pad->IsPad(_pad);
}

bool InputUtility::IsAllPadDown(int _pad) {
	for (int i = 0; i < MAX_PAD_PORT; i++) {
		PadBase* pad = InputManager::GetInstance().GetPad(i);

		if (!pad) continue;

		if (!pad->IsPadDown(_pad)) continue;

		return true;
	}
	return false;
}

bool InputUtility::IsPadDown(int _index, int _pad) {
	PadBase* pad = InputManager::GetInstance().GetPad(_index);
	if (!pad) return false;
	return pad->IsPadDown(_pad);
}

bool InputUtility::IsAllPadUp(int _pad) {
	for (int i = 0; i < MAX_PAD_PORT; i++) {
		PadBase* pad = InputManager::GetInstance().GetPad(i);

		if (!pad) continue;

		if (!pad->IsPadUp(_pad)) continue;

		return true;
	}
	return false;
}

bool InputUtility::IsPadUp(int _index, int _pad) {
	PadBase* pad = InputManager::GetInstance().GetPad(_index);
	if (!pad) return false;
	return pad->IsPadUp(_pad);
}

VECTOR InputUtility::GetLeftStick(int _index) {
	PadBase* pad = InputManager::GetInstance().GetPad(_index);
	if (!pad) return VMinus;
	return pad->GetLStick();
}

VECTOR InputUtility::GetRightStick(int _index) {
	PadBase* pad = InputManager::GetInstance().GetPad(_index);
	if (!pad) return VZero;
	return pad->GetRStick();
}

PadBase* InputUtility::GetPad(int _portNum) {
	return InputManager::GetInstance().GetPad(_portNum);
}
