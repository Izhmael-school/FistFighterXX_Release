#pragma once
#include "../Definition.h"

class PadBase;

/// <summary>
/// 入力管理クラスを使いやすくした便利クラス
/// </summary>
class InputUtility {
public:

	// 更新処理
	static void Update();

	/**
	押されているか
	KEY_INPUT_##
	*/
	static bool IsKey(int _key);
	/**
	押されたか
	KEY_INPUT_##
	*/
	static bool IsKeyDown(int _key);
	/**
	離したか
	KEY_INPUT_##
	*/
	static bool IsKeyUp(int _key);

	/**
	  押されているか
	  MOUSE_INPUT_##
	*/
	static bool IsMouse(int _mouse);
	/**
	  押されたか
	  MOUSE_INPUT_##
	*/
	static bool IsMouseDown(int _mouse);
	/**
	  離したか
	  MOUSE_INPUT_##
	*/
	static bool IsMouseUp(int _mouse);
	/**
	  全てのコントローラのうち一つでも押されているか
	  XINPUT_BUTTON_##
	*/
	static bool IsAllPad(int _pad);
	/**
	  押されているか
	  XINPUT_BUTTON_##
	*/
	static bool IsPad(int _index, int _pad);
	/**
	  全てのコントローラのうち一つでも押したか
	  XINPUT_BUTTON_##
	*/
	static bool IsAllPadDown(int _pad);
	/**
	  押したか
	  XINPUT_BUTTON_##
	*/
	static bool IsPadDown(int _index, int _pad);
	/**
	  全てのマウスのうち一つでも離したか
	  XINPUT_BUTTON_##
	*/
	static bool IsAllPadUp(int _pad);
	/**
	  離したか
	  XINPUT_BUTTON_##
	*/
	static bool IsPadUp(int _index, int _pad);

	/**
	  左Stickの取得
	*/
	static VECTOR GetLeftStick(int _index);

	/**
	  右Stickの取得
	*/
	static VECTOR GetRightStick(int _index);
	
	static PadBase* GetPad(int _portNum);
};