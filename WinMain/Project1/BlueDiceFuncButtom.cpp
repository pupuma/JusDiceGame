#include "Game.h"
#include "BlueDiceFuncButtom.h"



BlueDiceFuncButtom::BlueDiceFuncButtom()
{
}


BlueDiceFuncButtom::~BlueDiceFuncButtom()
{
}

bool BlueDiceFuncButtom::Init()
{
	iStartX = 219;
	iStartY = 717;

	iWidth = 77;
	iHeight = 64;

	iPosX = iStartX + iWidth / 2;
	iPosY = iStartY + iHeight / 2;

	rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);


	img = new Image();
	img = IMAGEMANAGER->FindImage(TEXT("BlueItemUpOffButton"));

	img->SetFrameX(0);
	img->SetX(rc.left);
	img->SetY(rc.top);

	ptPrice = {253,700};
	ptLevel = { 242,727 };
	ptEffect = { 251,742 };
	ptDamage = { 251,760 };

	return true;
}

void BlueDiceFuncButtom::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (iBluePrice <= GAMESYS->GetGold())
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
				DICEMANAGER->SetBlueDiceLevel(iLevel);

				DICEMANAGER->SetBlueDiceDamage(iDamage);
				GAMESYS->SetGoldSale(iBluePrice);
				iBlueEffect = DICEMANAGER->GetBlueDiceEffectPower();

				//DICEMANAGER->SetBlackDicePrice();
				iCount++;
				if (iCount >= 3)
				{
					iCount = 0;
					iBlueEffect++;
					DICEMANAGER->SetBlueDiceEffectPower(iBlueEffect);
				}

				if (iCount == 0)
				{
					iBluePrice += 200;
				}
				else if (iCount == 1)
				{
					iBluePrice += 300;
				}
				else if (iCount == 2)
				{
					iBluePrice += 400;
				}

				DICEMANAGER->SetBlueDicePrice(iBluePrice);

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

void BlueDiceFuncButtom::TextRender(HDC hdc)
{
	{
		TCHAR str[256] = { 0, };
		iBluePrice = DICEMANAGER->GetBlueDicePrice();
		_stprintf(str, TEXT("%d"), iBluePrice);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSS"), str, &ptPrice, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iLevel = DICEMANAGER->GetBlueDiceLevel();

		_stprintf(str, TEXT("L v.%d"), iLevel);
		FONTMANAGER->RenderText(hdc, TEXT("AdobeSB"), str, &ptLevel, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iBlueEffect = DICEMANAGER->GetBlueDiceEffectPower();

		_stprintf(str, TEXT("-%d%%"), iBlueEffect);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptEffect, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iDamage = DICEMANAGER->GetBlueDiceDamage();
		_stprintf(str, TEXT("%d"), iDamage);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptDamage, RGB(0, 0, 0));
	}
}
