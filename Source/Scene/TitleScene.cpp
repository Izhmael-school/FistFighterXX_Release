#include "TitleScene.h"
#include "../Utility/InputUtility.h"
#include "../Utility/SceneUtility.h"
#include "../Utility/FontUtility.h"
#include "../Utility/AudioUtility.h"
#include "../Other/CommonModule/MyString.h"

TitleScene::TitleScene() 
	:titleSprite(-1)
{ Start(); }

TitleScene::~TitleScene() {}

void TitleScene::Start() {
	titleSprite = LoadGraph(TITLE_SPRITE_PATH.data());
	useFontHandle = FontUtility::UseFontHandle("MainFont_Bold");
	textPos = MyString::StringCenterPos("Aボタンを押せ！", useFontHandle, WINDOW_WIDTH / 2, WINDOW_HEIGHT - (WINDOW_HEIGHT / 12));
	AudioUtility::Load("res/Audio/BGM/Title/Title.mp3", "title", false);
	AudioUtility::Load("res/Audio/SE/MoveTitle.mp3", "moveTitle", false);
}

void TitleScene::Update() {
	if (InputUtility::IsAllPadDown(XINPUT_BUTTON_A)) {
		AudioUtility::PlayOneShot("moveTitle");
		SceneUtility::SetScene(Menu);
	}
}

void TitleScene::Render() {
	DrawGraph(0, 0, titleSprite, TRUE);
	DrawExtendStringToHandle(textPos.x, textPos.y,1.0f,1.0f, "Aボタンを押せ！",red, useFontHandle);
}

void TitleScene::Setup() {
	AudioUtility::PlayBGM("title",125.0f);
}

void TitleScene::Teardown() {
	AudioUtility::Stop("title");
}

void TitleScene::DeleteData() {

}
