#include "Game.h"
#include "DiceFuncButtom.h"



DiceFuncButtom::DiceFuncButtom()
{
	buttomType = eButtom::DCBUTTONDIR_NONE;
	iLevel = 1;
	iDamage = 1;
}


DiceFuncButtom::~DiceFuncButtom()
{
}

bool DiceFuncButtom::Init()
{
	return true;
}

void DiceFuncButtom::Update()
{
}

void DiceFuncButtom::Release()
{
	//SAFE_DELETE(img);
}

void DiceFuncButtom::Render(HDC hdc)
{
	img->FrameRender(hdc, rc.left, rc.top);
	TextRender(hdc);
}

void DiceFuncButtom::TextRender(HDC hdc)
{
	
}
