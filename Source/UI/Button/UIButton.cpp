#include "UIButton.h"
#include "DxLib.h"
#include "../../Other/CommonModule/MyString.h"
#include "../../Utility/InputUtility.h"
#include "../../Utility/AudioUtility.h"
#include "../../Other/CommonModule/MyImage.h"
#include "../Cursor/CursorInfo.h"

UIButton::UIButton(float _x, float _y, float _width, float _height, std::function<void(void)> _func, std::string _text, unsigned int _idleColor, unsigned int _selectColor, int _fontHandle, float _fontSize, int _backImageHandle, int _frameImageHandle)
	:UIBase(_x, _y, _width, _height)
	, func(_func)
	, backImageHandle(_backImageHandle)
	, frameImageHandle(_frameImageHandle)
	, buttonText(_text)
	, textIdleColor(_idleColor)
	, textSelectColor(_selectColor)
	, textFontHandle(_fontHandle)
	, fontSize(_fontSize)
	, isSelect(false)
	, isPush(false)
	, textPosX(-1)
	, textPosY(-1)
	, useSound(false) {
	Start();
}

UIButton::~UIButton() {
	//DeleteGraph(backImageHandle);
	//DeleteGraph(frameImageHandle);
}

void UIButton::Start() {
	VECTOR p;
	if (backImageHandle != -1) {
		p = MyImage::ImageCenterPos(backImageHandle, VGet(x, y, 0));
		x = p.x;
		y = p.y;
	}
	else {
		x -= (w / 2);
		y -= (h / 2);
	}
	p = MyString::StringCenterPos(buttonText.c_str(), textFontHandle, x, y, fontSize, fontSize);
	textPosX = p.x + (w / 2);
	textPosY = p.y + (h / 2);
}

void UIButton::Update() {
	if (!isActive) return;

	// マウスがボタンの範囲内なら
	if (CursorInfo::InPoint(x, y, x + w, y + h)) {
		isSelect = true;

		if (!useSound) {
			useSound = true;
			AudioUtility::PlayOneShot("onButton");
		}

	}
	else {
		useSound = false;
		isSelect = false;
		isPush = false;
	}

	if (!isSelect) return;

	// 押されていたら
	if (InputUtility::IsPad(0, XINPUT_BUTTON_A))
		isPush = true;

	if (!isPush) return;

	// 離したら設定した関数の呼び出し
	if (InputUtility::IsPadUp(0, XINPUT_BUTTON_A)) {
		AudioUtility::PlayOneShot("buttonPush");
		func();
		isPush = false;
	}

}

void UIButton::Render() {
	if (!isActive) return;

	// 下地画像の描画
	if (backImageHandle != -1)
		DrawExtendGraphF(x, y, x + w, y + h, backImageHandle, TRUE);
	else {
		if (!isPush)
			DrawBoxAA(x, y, x + w, y + h, white, TRUE);
		else
			DrawBoxAA(x, y, x + w, y + h, gray, TRUE);
	}

	// テキストの描画
	if (isSelect)
		DrawExtendStringToHandle(textPosX, textPosY, fontSize, fontSize, buttonText.c_str(), textSelectColor, textFontHandle);
	else
		DrawExtendStringToHandle(textPosX, textPosY, fontSize, fontSize, buttonText.c_str(), textIdleColor, textFontHandle);

	// 枠の描画
	if (backImageHandle != -1)
		DrawExtendGraphF(x, y, x + w, y + h, frameImageHandle, TRUE);
	else
		DrawBoxAA(x, y, x + w, y + h, black, FALSE);
}
