#pragma once
#include <string>
#include "../Definition.h"
#include "Utility/Span.h"
#include <vector>
#include "../UI/UIBase.h"

struct Tips {
	std::string armName;
	std::string tipsText;
	int armIconHandle;
};

class MenuTips : public UIBase {
public:
	MenuTips(float _x, float _y, float _width, float _height);

	~MenuTips() = default;

public:
	void Update() override;
	void Render() override;

private:
	void Initialize();

	void ChangeTips();
public:
	// チップスデータ
	std::vector<Tips> tips;	

	Span changeTipsSpan;

	int tipsFrameHandle = -1;

	int tipsNameFontHandle = -1;
	int tipsTextFontHandle = -1;

	int currentTipsIndex = -1;
};

