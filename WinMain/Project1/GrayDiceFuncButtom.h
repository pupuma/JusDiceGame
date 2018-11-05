#pragma once
#include "DiceFuncButtom.h"
class GrayDiceFuncButtom
	: public DiceFuncButtom
{
private:
	int iGrayPrice;
	POINT ptGray;
	int iGrayEffect;
public:
	GrayDiceFuncButtom();
	~GrayDiceFuncButtom();
public:
	bool Init();
	void Update();
public:
	void TextRender(HDC hdc);

};

