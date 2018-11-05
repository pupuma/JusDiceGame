#pragma once
#include "DiceFuncButtom.h"

class YellowDiceFuncButtom
	:public DiceFuncButtom
{
private:
	int iYellowPrice;
	int iYellowEffect;
	POINT ptYellow;
public:
	YellowDiceFuncButtom();
	~YellowDiceFuncButtom();
public:
	bool Init();
	void Update();
public:
	void TextRender(HDC hdc);

};

