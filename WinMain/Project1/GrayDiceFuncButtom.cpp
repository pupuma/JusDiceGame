#include "Game.h"
#include "GrayDiceFuncButtom.h"



GrayDiceFuncButtom::GrayDiceFuncButtom()
{
}


GrayDiceFuncButtom::~GrayDiceFuncButtom()
{
}

bool GrayDiceFuncButtom::Init()
{
	iStartX = 468;
	iStartY = 717;

	iWidth = 77;
	iHeight = 64;

	iPosX = iStartX + iWidth / 2;
	iPosY = iStartY + iHeight / 2;

	rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

	img = new Image();
	img = IMAGEMANAGER->FindImage(TEXT("GrayItemUpOffButton"));

	img->SetFrameX(0);
	img->SetX(rc.left);
	img->SetY(rc.top);

	ptPrice = { 502,700 };
	ptLevel = { 491,727 };
	ptEffect = { 500,742 };
	ptDamage = { 500,760 };
	return true;
}

void GrayDiceFuncButtom::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (iGrayPrice <= GAMESYS->GetGold())
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
				DICEMANAGER->SetGrayDiceLevel(iLevel);

				DICEMANAGER->SetGrayDiceDamage(iDamage);
				GAMESYS->SetGoldSale(iGrayPrice);
				iGrayEffect = DICEMANAGER->GetGrayDiceEffectPower();

				//DICEMANAGER->SetBlackDicePrice();
				if (iCount >= 3)
				{
					iCount = 0;
					iGrayEffect++;
					DICEMANAGER->SetGrayDiceEffectPower(iGrayEffect);
				}

				if (iCount == 0)
				{
					iGrayPrice += 200;
				}
				else if (iCount == 1)
				{
					iGrayPrice += 300;
				}
				else if (iCount == 2)
				{
					iGrayPrice += 400;
				}
				iCount++;

				DICEMANAGER->SetGrayDicePrice(iGrayPrice);


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

void GrayDiceFuncButtom::TextRender(HDC hdc)
{
	{
		TCHAR str[256] = { 0, };
		iGrayPrice = DICEMANAGER->GetGrayDicePrice();
		_stprintf(str, TEXT("%d"), iGrayPrice);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSS"), str, &ptPrice, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iLevel = DICEMANAGER->GetGrayDiceLevel();

		_stprintf(str, TEXT("L v.%d"), iLevel);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSB"), str, &ptLevel, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iGrayEffect = DICEMANAGER->GetGrayDiceEffectPower();
		_stprintf(str, TEXT("x%d"), iGrayEffect);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptEffect, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iDamage = DICEMANAGER->GetGrayDiceDamage();
		_stprintf(str, TEXT("%d"), iDamage);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptDamage, RGB(0, 0, 0));
	}
}
