#include "MyString.h"

void MyString::StringCenterPos(const TCHAR* _str, int _fontHandle, int* posX, int* posY, int exRateX, int exRateY) {
	int w, h, line;

	GetDrawStringSizeToHandle(&w, &h, &line, _str, (int)_tcslen(_str), _fontHandle);
	*posX -= (int)(w * exRateX) / 2;
	*posY -= (int)(h * exRateY) / 2;
}

VECTOR MyString::StringCenterPos(const TCHAR* _str, int _fontHandle, int posX, int posY, float exRateX, float exRateY) {
	int w, h, line;

	if (_fontHandle == -1)
		GetDrawStringSize(&w, &h, &line, _str, (int)_tcslen(_str));
	else
		GetDrawStringSizeToHandle(&w, &h, &line, _str, (int)_tcslen(_str), _fontHandle);

	posX -= (int)(w * exRateX) / 2;
	posY -= (int)(h * exRateY) / 2;

	return VGet(posX, posY, 0);
}

int MyString::StringRightPos(const TCHAR* _str, int _fontHandle, int posX, int exRateX) {
	int w, h, line;

	GetDrawStringSizeToHandle(&w, &h, &line, _str, (int)_tcslen(_str), _fontHandle);

	return posX -= (int)(w * exRateX);
}
