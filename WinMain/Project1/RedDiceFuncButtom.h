#pragma once
#include "DiceFuncButtom.h"

class RedDiceFuncButtom
	: public DiceFuncButtom
{
private:
	int iRedPrice;
	int iRedEffect;

	POINT ptRed;
	
public:
	RedDiceFuncButtom();
	~RedDiceFuncButtom();
public:
	bool Init();
	void Update();
public:
	void TextRender(HDC hdc);


};

