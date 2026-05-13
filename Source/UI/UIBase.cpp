#include "UIBase.h"

int UIBase::idCounter = 0;

UIBase::UIBase(float _x, float _y, float _width, float _height,UITag _tag) 
	:x(_x)
	,y(_y)
	,w(_width)
	,h(_height)
	,isActive(true)
	,tag(_tag)
	, id(idCounter++)
{}
