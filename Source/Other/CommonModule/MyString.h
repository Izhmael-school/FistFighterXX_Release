#pragma once
#include <string>
#include "DxLib.h"

class MyString {
public:


	/// <summary>
/// 文字列の合体
/// </summary>
/// <param name="text"></param>
/// <param name=""></param>
/// <returns></returns>
	template<typename ...Args>
	static inline std::string MergeString(const Args & ...args) {

		std::string mergedText;

		(mergedText += ... += args);

		return mergedText;
	}

	/// <summary>
	/// 中央揃えのための座標計算（参照）
	/// </summary>
	/// <param name="_str"></param>
	/// <param name="_fontHandle"></param>
	/// <param name="posX"></param>
	/// <param name="posY"></param>
	/// <param name="exRateX"></param>
	/// <param name="exRateY"></param>
	static void StringCenterPos(const TCHAR* _str, int _fontHandle, int* posX, int* posY, int exRateX = 1, int exRateY = 1);

	/// <summary>
	/// 中央揃えのための座標計算（返り値）
	/// </summary>
	/// <param name="_str"></param>
	/// <param name="_fontHandle"></param>
	/// <param name="posX"></param>
	/// <param name="posY"></param>
	/// <param name="exRateX"></param>
	/// <param name="exRateY"></param>
	static VECTOR StringCenterPos(const TCHAR* _str, int _fontHandle, int posX, int posY, float exRateX = 1, float exRateY = 1);

	/// <summary>
	/// 右詰めのための座標計算
	/// </summary>
	/// <param name="_str"></param>
	/// <param name="_fontHandle"></param>
	/// <param name="posX"></param>
	/// <param name="exRateX"></param>
	/// <returns></returns>
	static int StringRightPos(const TCHAR* _str, int _fontHandle, int posX, int exRateX = 1);
};