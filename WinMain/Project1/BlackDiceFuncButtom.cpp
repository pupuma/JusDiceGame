#include "Game.h"
#include "BlackDiceFuncButtom.h"



BlackDiceFuncButtom::BlackDiceFuncButtom()
{
	iCount = 0;
}


BlackDiceFuncButtom::~BlackDiceFuncButtom()
{
}

bool BlackDiceFuncButtom::Init()
{
	iStartX = 385;
	iStartY = 717;

	iWidth = 77;
	iHeight = 64;

	iPosX = iStartX + iWidth / 2;
	iPosY = iStartY + iHeight / 2;

	rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

	img = new Image();
	img = IMAGEMANAGER->FindImage(TEXT("BlackItemUpOffButton"));

	img->SetFrameX(0);
	img->SetX(rc.left);
	img->SetY(rc.top);

	ptPrice = { 419,700 };
	ptLevel = { 408,727 };
	ptEffect = { 417,742 };
	ptDamage = { 417,760 };


	return true;
}

void BlackDiceFuncButtom::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (iBlackPrice <= GAMESYS->GetGold())
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
				DICEMANAGER->SetBlackDiceLevel(iLevel);

				DICEMANAGER->SetBlackDiceDamage(iDamage);
				GAMESYS->SetGoldSale(iBlackPrice);
				iBlackEffect = DICEMANAGER->GetBlackDiceEffectPower();
				
				//DICEMANAGER->SetBlackDicePrice();
				if (iCount >= 3)
				{
					iCount = 0;
					iBlackEffect++;
					DICEMANAGER->SetBlackDiceEffectPower(iBlackEffect);
				}
				
				if (iCount == 0)
				{
					iBlackPrice += 200;
				}
				else if (iCount == 1)
				{
					iBlackPrice += 300;
				}
				else if (iCount == 2)
				{
					iBlackPrice += 400;
				}
				iCount++;

				DICEMANAGER->SetBlackDicePrice(iBlackPrice);

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

void BlackDiceFuncButtom::TextRender(HDC hdc)
{
	{
		TCHAR str[256] = { 0, };
		iBlackPrice = DICEMANAGER->GetBlackDicePrice();
		_stprintf(str, TEXT("%d"), iBlackPrice);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSS"), str, &ptPrice, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iLevel = DICEMANAGER->GetBlackDiceLevel();
		_stprintf(str, TEXT("L v.%d"), iLevel);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSB"), str, &ptLevel, RGB(0, 0, 0));
	}
	{
		TCHAR str[256] = { 0, };
		iBlackEffect = DICEMANAGER->GetBlackDiceEffectPower();
		_stprintf(str, TEXT("%d%"), iBlackEffect);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptEffect, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iDamage = DICEMANAGER->GetBlackDiceDamage();
		_stprintf(str, TEXT("%d"), iDamage);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptDamage, RGB(0, 0, 0));
	}
}
