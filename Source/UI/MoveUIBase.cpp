#include "MoveUIBase.h"
#include "../Object/Object.h"
#include "DxLib.h"

MoveUIBase::MoveUIBase(Object* _sourceObject, float _offsetX, float _offsetY, float _width, float _height, UITag _tag)
	:UIBase(_sourceObject->GetPosition().x,_sourceObject->GetPosition().y,_width,_height,_tag)
	,sourceObject(_sourceObject)
	,offsetX(_offsetX)
	,offsetY(_offsetY)
{}

void MoveUIBase::Update() {
	VECTOR pos = sourceObject->GetTransform().GetPosition();
	pos = ConvWorldPosToScreenPos(pos);
	x = pos.x + offsetX;
	y = pos.y + offsetY;
}
