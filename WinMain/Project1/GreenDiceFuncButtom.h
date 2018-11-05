#pragma once
#include "DiceFuncButtom.h"

class GreenDiceFuncButtom
	: public DiceFuncButtom
{
private:
	int iGreenPrice;
	int iGreenEffect;
	POINT ptGreen;
public:
	GreenDiceFuncButtom();
	~GreenDiceFuncButtom();
public:
	bool Init();
	void Update();
public:
	void TextRender(HDC hdc);

};

