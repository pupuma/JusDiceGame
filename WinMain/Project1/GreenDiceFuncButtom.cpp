#include "Game.h"
#include "GreenDiceFuncButtom.h"



GreenDiceFuncButtom::GreenDiceFuncButtom()
{
}


GreenDiceFuncButtom::~GreenDiceFuncButtom()
{
}

bool GreenDiceFuncButtom::Init()
{
	iStartX = 302;
	iStartY = 717;

	iWidth = 77;
	iHeight = 64;

	iPosX = iStartX + iWidth / 2;
	iPosY = iStartY + iHeight / 2;

	rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

	img = new Image();
	img = IMAGEMANAGER->FindImage(TEXT("GreenItemUpOffButton"));

	img->SetFrameX(0);
	img->SetX(rc.left);
	img->SetY(rc.top);

	ptPrice = { 336,700 };
	ptLevel = { 325,727 };
	ptEffect = { 334,742 };
	ptDamage = { 334,760 };

	return true;
}

void GreenDiceFuncButtom::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (iGreenPrice <= GAMESYS->GetGold())
	{
		if (PtInRect(&rc, _ptMouse))
		{

			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				buttomType = DCBUTTONDIR_DOWN;
				img->SetFrameX(1);
			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
			{
				buttomType = DCBUTTONDIR_UP;
				iDamage++;
				iLevel++;
				DICEMANAGER->SetGreenDiceLevel(iLevel);

				DICEMANAGER->SetGreenDiceDamage(iDamage);
				GAMESYS->SetGoldSale(iGreenPrice);
				iGreenEffect = DICEMANAGER->GetGreenDiceEffectPower();

				//DICEMANAGER->SetBlackDicePrice();
				if (iCount >= 3)
				{
					iCount = 0;
					iGreenEffect++;
					DICEMANAGER->SetGreenDiceEffectPower(iGreenEffect);
				}

				if (iCount == 0)
				{
					iGreenPrice += 200;
				}
				else if (iCount == 1)
				{
					iGreenPrice += 300;
				}
				else if (iCount == 2)
				{
					iGreenPrice += 400;
				}
				iCount++;

				DICEMANAGER->SetGrayDicePrice(iGreenPrice);


				img->SetFrameX(0);
			}

		}
		else
		{
			buttomType = DCBUTTONDIR_NONE;
			img->SetFrameX(0);
		}

	}
	else
	{
		img->SetFrameX(1);
	}

}

void GreenDiceFuncButtom::TextRender(HDC hdc)
{
	{
		TCHAR str[256] = { 0, };
		iGreenPrice = DICEMANAGER->GetGreenDicePrice();
		_stprintf(str, TEXT("%d"), iGreenPrice);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSS"), str, &ptPrice, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iLevel = DICEMANAGER->GetGreenDiceLevel();
		_stprintf(str, TEXT("L v.%d"), iLevel);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSB"), str, &ptLevel, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iGreenEffect = DICEMANAGER->GetGreenDiceEffectPower();
		_stprintf(str, TEXT("%d"), iGreenEffect);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptEffect, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iDamage = DICEMANAGER->GetGreenDiceDamage();
		_stprintf(str, TEXT("%d"), iDamage);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptDamage, RGB(0, 0, 0));
	}
}
