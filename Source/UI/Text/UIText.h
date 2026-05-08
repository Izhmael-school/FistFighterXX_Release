#pragma once
#include "../UIBase.h"
#include <string>
#include "../../Definition.h"

class UIText : public UIBase {
public:
	UIText(float _x,float _y,std::string _text,int _fontHandle = -1 ,unsigned int _color = black);
	~UIText() = default;

private:
	void Start();
public:
	void Update() override;
	void Render() override;
private:
	unsigned int color;
	std::string text;
	int fontHandle;
};

