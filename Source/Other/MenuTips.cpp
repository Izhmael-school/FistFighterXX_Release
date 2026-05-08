#include "MenuTips.h"
#include "CommonModule/MyJson.h"
#include <DxLib.h>
#include "CommonModule/MyString.h"
#include "CommonModule/MyDraw.h"
#include "CommonModule/MyMath.h"
#include "../Utility/FontUtility.h"

MenuTips::MenuTips(float _x, float _y, float _width, float _height)
	:UIBase(_x, _y, _width, _height)
	, tips()
	, changeTipsSpan()
	, tipsFrameHandle(-1)
	, tipsNameFontHandle(-1)
	, tipsTextFontHandle(-1)
{
	Initialize();
}

void MenuTips::Update() {
	if (tips.size() <= 0 || !isActive) return;

	// 一定時間ごとにチップスを変更
	if (!changeTipsSpan.IsTime())
		changeTipsSpan.UpdateTime();
	else
		ChangeTips();
}

void MenuTips::Render() {
	if (!isActive) return;

	DrawGraph(0, 0, tipsFrameHandle, true);

	MyDraw::DrawStringCenterPos(553, 757, 1, 1, tips[currentTipsIndex].armName.c_str(), white, tipsNameFontHandle);
	MyDraw::DrawStringCenterPos(553, 893, 1, 1, tips[currentTipsIndex].tipsText.c_str(), white, tipsTextFontHandle);
	DrawGraph(250, 150, tips[currentTipsIndex].armIconHandle, true);
}

void MenuTips::Initialize() {
	auto data = MyJson::LoadJsonFile("src/Data/ArmData.json");

	// JsonデータをTips構造体に変換
	for (auto d : data) {
		Tips t;

		t.armName = MyJson::Utf8ToString(d["armName"].get<std::string>());
		t.tipsText = MyJson::Utf8ToString(d["tips"].get<std::string>());
		std::string path = MyString::MergeString(ARM_SPRITE_PATH, d["modelFileName"].get<std::string>(), SPRITE_EXTENSION);
		t.armIconHandle = LoadGraph(path.c_str());

		tips.push_back(t);
	}

	ChangeTips();
	// Tipsの変更周期
	changeTipsSpan.SetTargetTime(5.0f);
	// 枠の読み込み
	tipsFrameHandle = LoadGraph("res/Image/MenuScene/TipsFrame.png");
	// フォントの読み込み
	tipsNameFontHandle = FontUtility::UseFontHandle("TipsFont_Name");
	tipsTextFontHandle = FontUtility::UseFontHandle("TipsFont_Text");
}

void MenuTips::ChangeTips() {
	int index;
	do
		index = MyMath::Random(0, static_cast<int>(tips.size() - 1));
	while (index == currentTipsIndex);

	currentTipsIndex = index;
}
