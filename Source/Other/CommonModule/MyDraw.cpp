#include "MyDraw.h"

void MyDraw::DrawStringCenterPos(int _x, int _y, float _exRateX, float _exRateY, const TCHAR* _text, unsigned int _color, int _fontHandle, unsigned int _edgeColor) {
	int w, h, line;

	// •¶š‚Ì‘å‚«‚³æ“¾
	if (_fontHandle == -1)
		GetDrawStringSize(&w, &h, &line, _text, (int)_tcslen(_text));
	else
		GetDrawStringSizeToHandle(&w, &h, &line, _text, (int)_tcslen(_text), _fontHandle);

	// ’†S‚É•`‰æ‚Å‚«‚é‚æ‚¤À•W‚ğ‚¸‚ç‚·
	_x -= (int)(w * _exRateX) / 2;
	_y -= (int)(h * _exRateY) / 2;

	// •`‰æ
	DrawExtendStringToHandle(_x, _y, _exRateX, _exRateY, _text, _color, _fontHandle, _edgeColor);
}

void MyDraw::DrawGraphCenterPos(int _x, int _y, int _graphHandle, float _exRateX, float _exRateY, int _transFlag) {
	if (_graphHandle == -1) return;

	int w, h;

	// ‰æ‘œ‚Ì‘å‚«‚³‚ğæ“¾
	GetGraphSize(_graphHandle, &w, &h);

	// ’†S‚É•`‰æ‚Å‚«‚é‚æ‚¤À•W‚ğ‚¸‚ç‚·
	_x -= (int)(w * _exRateX) / 2.0f;
	_y -= (int)(h * _exRateY) / 2.0f;

	// •`‰æ
	DrawExtendGraph(_x, _y, _x + w, _y + h, _graphHandle, _transFlag);
}

void MyDraw::DrawExtendGraphCenterPos(int _x, int _y,  int _graphHandle, float _exRateX, float _exRateY, int _transFlag) {
	if (_graphHandle == -1) return;

	int w, h;

	// ‰æ‘œ‚Ì‘å‚«‚³‚ğæ“¾
	GetGraphSize(_graphHandle, &w, &h);

	// ’†S‚É•`‰æ‚Å‚«‚é‚æ‚¤À•W‚ğ‚¸‚ç‚·
	int x = _x - (int)(w * _exRateX) / 2.0f;
	int y = _y - (int)(h * _exRateY) / 2.0f;

	// •`‰æ
	DrawExtendGraph(x, y, _x, _y, _graphHandle, _transFlag);
}
