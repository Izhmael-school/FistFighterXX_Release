#include "UIText.h"
#include "../../Other/CommonModule/MyString.h"

UIText::UIText(float _x, float _y, std::string _text, int _fontHandle, unsigned int _color) 
	:UIBase(_x,_y)
	,text(_text)
	,fontHandle(_fontHandle)
	,color(_color)
{ Start(); }

void UIText::Start() {
	VECTOR p = MyString::StringCenterPos(text.c_str(), fontHandle, x, y);
	x = p.x;
	y = p.y;
}

void UIText::Update() {
}

void UIText::Render() {
	if (!isActive) return;

	//DrawString()
}
