#include "PlayerCursor.h"
#include "../../Definition.h"
#include "../../Utility/InputUtility.h"
#include "../../Utility/TimeUtility.h"
#include <algorithm>

PlayerCursor::PlayerCursor(int _portNum)
	:UIBase(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 50, 50)
	, portNum(_portNum)
	, moveSpeed(500) {}

PlayerCursor::~PlayerCursor() {}

void PlayerCursor::Start() {}

void PlayerCursor::Update() {
	if (portNum == -1 || !isActive) return;

	VECTOR dir = InputUtility::GetLeftStick(portNum);
	dir = VScale(dir, moveSpeed * TimeUtility::GetDeltaTime());
	x = std::clamp(dir.x + x, 0.0f, static_cast<float>(WINDOW_WIDTH));
	y = std::clamp((dir.y * -1) + y, 0.0f, static_cast<float>(WINDOW_HEIGHT));
}

void PlayerCursor::Render() {
	if (!isActive) return;

	DrawTriangleAA(x - 10, y - 10, x + w + 10, y + h / 2, x + w / 2, y + h + 10, white, TRUE);
	DrawTriangleAA(x, y, x + w, y + h / 2, x + w / 2, y + h, red, TRUE);
}
