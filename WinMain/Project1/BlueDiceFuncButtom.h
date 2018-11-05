#pragma once

#include "DiceFuncButtom.h"

class BlueDiceFuncButtom
	: public DiceFuncButtom
{
private:
	int iBluePrice;
	int iBlueEffect;
	POINT ptBlue;
public:
	BlueDiceFuncButtom();
	~BlueDiceFuncButtom();
public:
	bool Init();
	void Update();
public:
	void TextRender(HDC hdc);

};

