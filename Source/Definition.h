#pragma once
#include "DxLib.h"
#include "Other/CommonModule/MyImage.h"
#include <string_view>

// 定数を管理するヘッダー
#define WINDOW_WIDTH (1920) 
#define WINDOW_HEIGHT (1080) 
#define FPS (60)

// ワールドベクトル
#define VRight	 (VGet(1.0f,0,0))
#define VLeft	 (VGet(-1.0f,0,0))
#define VUp		 (VGet(0,1.0f,0))
#define VDown	 (VGet(0,-1.0f,0))
#define VForward (VGet(0,0,1.0f))
#define VBack    (VGet(0,0,-1.0f))

// ゼロベクトル
#define VZero   (VGet(0,0,0))
#define VOne   (VGet(1,1,1))
#define VMinus (VGet(-1,-1,-1))

const unsigned int red = GetColor(255, 0, 0);
const unsigned int green = GetColor(0, 255, 0);
const unsigned int blue = GetColor(0, 0, 255);
const unsigned int magenta = GetColor(255, 0, 255);
const unsigned int cyan = GetColor(0, 255, 255);
const unsigned int yellow = GetColor(255, 255, 0);
const unsigned int white = GetColor(255, 255, 255);
const unsigned int gray = GetColor(120, 120, 120);
const unsigned int black = GetColor(0, 0, 0);

constexpr float BLEND_MAX = 255.0f;

constexpr int USE_ARM_MAX = 8;

constexpr int PLAYER_MAX = 4;
constexpr int PLAYER_COLOR_MAX = 8;

constexpr int STAGE_MAX = 3;

constexpr int ITEM_NUM = 7;

// コントローラ関連
constexpr int KEY_NUM = 256;
constexpr int MAX_PAD_PORT = 4;
constexpr float DEADZONE = 0.15f;
constexpr int DI_PUSH_NUM = 128;

constexpr int DI_SWITCH_BUTTON_B = 0;
constexpr int DI_SWITCH_BUTTON_A = 1;
constexpr int DI_SWITCH_BUTTON_Y = 2;
constexpr int DI_SWITCH_BUTTON_X = 3;
constexpr int DI_SWITCH_BUTTON_L = 4;
constexpr int DI_SWITCH_BUTTON_R = 5;
constexpr int DI_SWITCH_BUTTON_ZL = 6;
constexpr int DI_SWITCH_BUTTON_ZR = 7;
constexpr int DI_SWITCH_BUTTON_MINUS = 8;
constexpr int DI_SWITCH_BUTTON_PLUS = 9;
constexpr int DI_SWITCH_BUTTON_LSTICK = 10;
constexpr int DI_SWITCH_BUTTON_RSTICK = 11;
constexpr int DI_SWITCH_BUTTON_HOME = 12;
constexpr int DI_SWITCH_BUTTON_PHOTO = 13;

constexpr std::string_view ITEMDATA_FILEPATH = "src/Data/ItemData.json";
constexpr std::string_view ITEMMODEL_FILEPATH = "res/Model/Item/";
constexpr std::string_view ARMDATA_FILEPATH = "src/Data/ArmData.json";
constexpr std::string_view ARMMODEL_FILEPATH = "res/Model/Arm/";
constexpr std::string_view STAGEMODEL_FILEPATH = "res/Model/Stage/";
constexpr std::string_view EFFECTMODEL_FILEPATH = "res/Model/Effect/";
constexpr std::string_view EFFECT_FILE_EXTENSION = ".efkefc";
constexpr std::string_view MODEL_FILE_EXTENSION = ".mv1";
constexpr std::string_view TITLE_SPRITE_PATH = "res/Image/TitleScene/Title.png";
constexpr std::string_view MENU_SPRITE_PATH = "res/Image/MenuScene/Menu.png";
constexpr std::string_view MENUBUTTON_SPRITE_PATH = "res/Image/MenuScene/ButtonBack.png";
constexpr std::string_view ARM_SPRITE_PATH = "res/Image/ArmImage/";
constexpr std::string_view SPRITE_EXTENSION = ".png";
// 音楽関連
constexpr std::string_view BGM_FILEPATH = "res/Audio/BGM/";
constexpr std::string_view SE_FILEPATH = "res/Audio/SE/";
constexpr std::string_view AUDIO_EXTENSION = ".mp3";

constexpr float PLAYER_GAUGE_WIDTH = 300.0f;
constexpr float PLAYER_GAUGE_HEIGHT = 20.0f;

constexpr float PLAYER_MOVEGAUGE_WIDTH = 150.0f;
constexpr float PLAYER_MOVEGAUGE_HEIGHT = 10.0f;

constexpr float ARM_MOVEGAUGE_WIDTH = 75.0f;
constexpr float ARM_MOVEGAUGE_HEIGHT = 10.0f;

const VECTOR PLAYER_GAUGE_POS[PLAYER_MAX] = {
	MyImage::BoxCenterPos((WINDOW_WIDTH / 16)  , WINDOW_HEIGHT / 16,PLAYER_GAUGE_WIDTH,PLAYER_GAUGE_HEIGHT),
	MyImage::BoxCenterPos((WINDOW_WIDTH / 16) * 9 , WINDOW_HEIGHT / 16,PLAYER_GAUGE_WIDTH,PLAYER_GAUGE_HEIGHT),
	MyImage::BoxCenterPos((WINDOW_WIDTH / 16)  , (WINDOW_HEIGHT / 16) * 15,PLAYER_GAUGE_WIDTH,PLAYER_GAUGE_HEIGHT),
	MyImage::BoxCenterPos((WINDOW_WIDTH / 16) * 9 , (WINDOW_HEIGHT / 16) * 15,PLAYER_GAUGE_WIDTH,PLAYER_GAUGE_HEIGHT)
};

enum VectorElement {
	X,
	Y,
	Z,
	VMax
};

// ゲームオブジェクトのタグ 
enum Tag {
	NoTag,
	Arm,
	PlayerCharacter,
	Item,
	UnmovingWall,
	Wall,
	EffectTag,
};

// シーンの状態
enum SceneState {
	Invalid = -1,
	Title,
	Menu,
	MainGame,
	SceneMax
};

// フェードの状態
enum FadeState {
	FadeIn = -1,
	None = 0,
	FadeOut = 1,
};

// フェードの種類
enum FadeType {
	FadeNormal,
	FadeMax
};

enum ArmType {
	Punch,
	Drill,
	Star,
	Bomb,
	Cutter,
	ArmTypeMax
};

enum ArmPos {
	Right,
	Left,
	ArmMax
};

enum ItemEffectType {
	NoItemEffect = -1,
	HPHeal,
	StaminaHeal,
	ArmChange,
	Destroy
};

enum UIType {
	Gauge,
	CirlceGauge,
};

enum CameraType {
	Free,
	Fixed,
	Target
};

enum MenuSceneState {
	MenuInvalid = -1, 
	MenuSelect,
	MenuPlayerRegister,
	MenuConfig,
	MenuStageSelect,
	MenuStateMax
};

enum GameSceneState {
	GameInvalid = -1,
	GamePlay,
	GameStop,
	GameStateMax
};

enum UITag {
	NoUITag,
	PlayerGauge,
};