#pragma once
#include "string"

class FontUtility {
public:
	/// <summary>
	/// フォントを作る
	/// </summary>
	/// <param name="fontName">フォントの名前</param>
	/// <param name="size">サイズ</param>
	/// <param name="thick">太さ</param>
	/// <param name="fontType">フォントタイプ</param>
	/// <param name="anyFontName">任意で付けるフォントの名前</param>
	static void CreateFontData(std::string fontName, int size, int thick, int fontType, std::string anyFontName = "");
	static int UseFontHandle(std::string _fontName);

	static void DeleteFont();
};

