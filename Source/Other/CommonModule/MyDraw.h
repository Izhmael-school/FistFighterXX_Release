#pragma once
#include "DxLib.h"

class MyDraw {
public:
	// 指定した座標を中心として文字を描画
	static void DrawStringCenterPos(int _x, int _y, float _exRateX, float _exRateY, const TCHAR* _text, unsigned int _color, int _fontHandle = -1, unsigned int _edgeColor = 0U);

	// 指定した座標を中心として画像を描画
	static void DrawGraphCenterPos(int _x, int _y, int _graphHandle, float _exRateX = 1.0f, float _exRateY = 1.0f, int _transFlag = TRUE);

	static void DrawExtendGraphCenterPos(int _x, int _y, int _graphHandle, float _exRateX = 1.0f, float _exRateY = 1.0f, int _transFlag = TRUE);
};

