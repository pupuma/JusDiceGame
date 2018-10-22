#include "Game.h"
#include "Dice.h"



Dice::Dice()
{
	diceType = eDiceColor::DICE_NONE;
}


Dice::~Dice()
{
}

bool Dice::Init()
{
	iDiceStartX = 148;
	iDiceStartY = 237;

	iDiceWidth = 73;
	iDiceHeight = 60;

	ptDiceCenterPos.x = iDiceStartX - iDiceWidth / 2;
	ptDiceCenterPos.y = iDiceStartY - iDiceHeight / 2;


	_image = IMAGEMANAGER->AddFrameImage(TEXT("TestDice"), TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);
	_image->SetX(ptDiceCenterPos.x);
	_image->SetY(ptDiceCenterPos.y);
	return true;
}

void Dice::Render(HDC hdc)
{
	_image->FrameRender(hdc, ptDiceCenterPos.x, ptDiceCenterPos.y);
}