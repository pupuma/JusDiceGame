#pragma once

#include "DiceFuncButtom.h"

class BlackDiceFuncButtom
	: public DiceFuncButtom
{
private:
	int iBlackPrice;
	int iBlackEffect;

	
public:
	BlackDiceFuncButtom();
	~BlackDiceFuncButtom();
public:
	bool Init();
	void Update();
public:
	void TextRender(HDC hdc);
};

