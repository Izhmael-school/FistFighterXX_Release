#pragma once
#include "../UIBase.h"
#include "../../Definition.h"
#include <string>
#include <functional>

class UIButton : public UIBase {
public:
	UIButton(float _x, float _y, float _width, float _height,std::function<void(void)> _func, std::string _text = "Text", unsigned int _idleColor = black, unsigned int _selectColor = yellow, int _fontHandle = -1, float _fontSize = 1.0f, int _backImageHandle = -1, int _frameImageHandle = -1);
	~UIButton();

private:
	void Start();

public:
	void Update() override;
	void Render() override;

	inline void SetSelect(bool _isSelect) { isSelect = _isSelect; }
private:
	bool isSelect;
	bool isPush;
	std::function<void(void)> func;
	int backImageHandle;
	int frameImageHandle;
	float textPosX, textPosY;
	std::string buttonText;
	int textFontHandle;
	float fontSize;
	unsigned int textIdleColor;
	unsigned int textSelectColor;
	bool useSound;
};

