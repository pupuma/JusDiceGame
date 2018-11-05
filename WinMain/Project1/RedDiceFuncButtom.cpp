#include "Game.h"
#include "RedDiceFuncButtom.h"



RedDiceFuncButtom::RedDiceFuncButtom()
{
}


RedDiceFuncButtom::~RedDiceFuncButtom()
{
}

bool RedDiceFuncButtom::Init()
{

	iStartX = 53;
	iStartY = 717;

	iWidth = 77;
	iHeight = 64;

	iPosX = iStartX + iWidth / 2;
	iPosY = iStartY + iHeight / 2;

	rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);


	img = new Image();
	img = IMAGEMANAGER->FindImage(TEXT("RedItemUpOffButton"));

	img->SetFrameX(0);
	img->SetX(rc.left);
	img->SetY(rc.top);

	ptPrice = { 87,700 };
	ptLevel = { 76,727 };
	ptEffect = {85,742};
	ptDamage = { 85,760 };

	return true;
}

void RedDiceFuncButtom::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (iRedPrice <= GAMESYS->GetGold())
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
				DICEMANAGER->SetRedDiceLevel(iLevel);

				DICEMANAGER->SetRedDiceDamage(iDamage);
				GAMESYS->SetGoldSale(iRedPrice);
				iRedEffect = DICEMANAGER->GetRedDiceEffectPower();

				//DICEMANAGER->SetBlackDicePrice();
				if (iCount >= 3)
				{
					iCount = 0;
					iRedEffect += 20;
					DICEMANAGER->SetRedDiceEffectPower(iRedEffect);
				}

				if (iCount == 0)
				{
					iRedPrice += 200;
				}
				else if (iCount == 1)
				{
					iRedPrice += 300;
				}
				else if (iCount == 2)
				{
					iRedPrice += 400;
				}
				iCount++;

				DICEMANAGER->SetRedDicePrice(iRedPrice);

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

void RedDiceFuncButtom::TextRender(HDC hdc)
{
	{
		TCHAR str[256] = { 0, };
		iRedPrice = DICEMANAGER->GetRedDicePrice();
		_stprintf(str, TEXT("%d"), iRedPrice);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSS"), str, &ptPrice, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iLevel = DICEMANAGER->GetRedDiceLevel();
		_stprintf(str, TEXT("L v.%d"), iLevel);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeSB"), str, &ptLevel, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iRedEffect = DICEMANAGER->GetRedDiceEffectPower();
		_stprintf(str, TEXT("%d"), iRedEffect);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptEffect, RGB(0, 0, 0));
	}

	{
		TCHAR str[256] = { 0, };
		iDamage = DICEMANAGER->GetRedDiceDamage();
		_stprintf(str, TEXT("%d"), iDamage);

		FONTMANAGER->RenderText(hdc, TEXT("AdobeS"), str, &ptDamage, RGB(0, 0, 0));
	}
}
