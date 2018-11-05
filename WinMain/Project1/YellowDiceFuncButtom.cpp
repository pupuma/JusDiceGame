#include "Game.h"
#include "YellowDiceFuncButtom.h"



YellowDiceFuncButtom::YellowDiceFuncButtom()
{
}


YellowDiceFuncButtom::~YellowDiceFuncButtom()
{
}

bool YellowDiceFuncButtom::Init()
{

	iStartX = 136;
	iStartY = 717;

	iWidth = 77;
	iHeight = 64;

	iPosX = iStartX + iWidth / 2;
	iPosY = iStartY + iHeight / 2;

	rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

	img = new Image();
	img = IMAGEMANAGER->FindImage(TEXT("YellowItemUpOffButton"));

	img->SetFrameX(0);
	img->SetX(rc.left);
	img->SetY(rc.top);

	ptPrice =  { 170,700 }; 
	ptLevel = { 159,727 };
	ptEffect = { 168,742 };
	ptDamage = { 168,760 };
	return true;
}

void YellowDiceFuncButtom::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (iYellowPrice <= GAMESYS->GetGold())
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
				DICEMANAGER->SetYellowDiceLevel(iLevel);

				DICEMANAGER->SetYellowDiceDamage(iDamage);
				GAMESYS->SetGoldSale(iYellowPrice);
				iYellowEffect = DICEMANAGER->GetYellowDiceEffectPower();

				//DICEMANAGER->SetBlackDicePrice();
				if (iCount >= 3)
				{
					iCount = 0;
					iYellowEffect++;
					DICEMANAGER->SetRedDiceEffectPower(iYellowEffect);
				}

				if (iCount == 0)
				{
					iYellowPrice += 200;
				}
				else if (iCount == 1)
				{
					iYellowPrice += 300;
				}
				else if (iCount == 2)
				{
					iYellowPrice += 400;
				}
				iCount++;

				DICEMANAGER->SetYellowDicePrice(iYellowPrice);

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

void YellowDiceFuncButtom::TextRender(HDC hdc)
{
	{
		TCHAR str[256] = { 0, };
		iYellowPrice = DICEMANAGER->GetYellowDicePrice();
		_stprintf(str, TEXT("%d"), iYellowPrice);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSS"), str, &ptPrice, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iLevel = DICEMANAGER->GetYellowDiceLevel();
		_stprintf(str, TEXT("L v.%d"), iLevel);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSB"), str, &ptLevel, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iYellowEffect = DICEMANAGER->GetYellowDiceEffectPower();
		_stprintf(str, TEXT("%d"), iYellowEffect);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptEffect, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iDamage = DICEMANAGER->GetYellowDiceDamage();
		_stprintf(str, TEXT("%d"), iDamage);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptDamage, RGB(0, 0, 0));
	}
}
