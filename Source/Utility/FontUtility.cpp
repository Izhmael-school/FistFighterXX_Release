#include "FontUtility.h"
#include "../Manager/FontManager.h"

void FontUtility::CreateFontData(std::string fontName, int size, int thick, int fontType, std::string anyFontName) {
	FontManager::GetInstance().CreateFontData(fontName,size,thick,fontType,anyFontName);
}

int FontUtility::UseFontHandle(std::string _fontName) {
	return FontManager::GetInstance().UseFontHandle(_fontName);
}

void FontUtility::DeleteFont() {
	FontManager::GetInstance().DeleteFont();
}
