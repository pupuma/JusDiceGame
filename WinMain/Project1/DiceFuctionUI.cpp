#include "Game.h"

#include "DiceFuctionUI.h"

#include "RedDiceFuncButtom.h"
#include "YellowDiceFuncButtom.h"
#include "BlueDiceFuncButtom.h"
#include "GreenDiceFuncButtom.h"
#include "BlackDiceFuncButtom.h"
#include "GrayDiceFuncButtom.h"
#include "GameSpeedButton.h"



DiceFuctionUI::DiceFuctionUI()
{
	// left ,top

	
}


DiceFuctionUI::~DiceFuctionUI()
{
}

bool DiceFuctionUI::Init()
{

	{
		redFunc = new RedDiceFuncButtom();
		yellowFunc = new YellowDiceFuncButtom();
		blueFunc = new BlueDiceFuncButtom();
		greenFunc = new GreenDiceFuncButtom();
		blackFunc = new BlackDiceFuncButtom();
		grayFunc = new GrayDiceFuncButtom();

		redFunc->Init();
		yellowFunc->Init();
		blueFunc->Init();
		greenFunc->Init();
		blackFunc->Init();
		grayFunc->Init();
	}

	{
		gsButtom = new GameSpeedButton();
		gsButtom->Init();
	}
	//{
	//	int iCurrentX = 6;
	//	
	//	iStartX = 53;
	//	iStartY = 717;

	//	iWidth = 77;
	//	iHeight = 64;

	//	for (int i = 0; i < 6; i++)
	//	{

	//		iPosX = iStartX + iWidth / 2;
	//		iPosY = iStartY + iHeight / 2;
	//		rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

	//		rcDiceList.push_back(rc);

	//		iStartX = iStartX + (iWidth) + iCurrentX;
	//	}


	//}


	//{
	//	
	//	imageRed = IMAGEMANAGER->FindImage(TEXT("RedItemUpOffButton"));

	//	imageRed->SetFrameX(0);
	//	imageRed->SetX(rcDiceList[0].left);
	//	imageRed->SetY(rcDiceList[0].top);

	//	imageYellow = IMAGEMANAGER->FindImage(TEXT("YellowItemUpOffButton"));

	//	imageYellow->SetFrameX(0);
	//	imageYellow->SetX(rcDiceList[1].left);
	//	imageYellow->SetY(rcDiceList[1].top);

	//	imageBlue = IMAGEMANAGER->FindImage(TEXT("BlueItemUpOffButton"));

	//	imageBlue->SetFrameX(0);
	//	imageBlue->SetX(rcDiceList[2].left);
	//	imageBlue->SetY(rcDiceList[2].top);

	//	imageGreen = IMAGEMANAGER->FindImage(TEXT("GreenItemUpOffButton"));

	//	imageGreen->SetFrameX(0);
	//	imageGreen->SetX(rcDiceList[3].left);
	//	imageGreen->SetY(rcDiceList[3].top);

	//	imageBlack = IMAGEMANAGER->FindImage(TEXT("BlackItemUpOffButton"));

	//	imageBlack->SetFrameX(0);
	//	imageBlack->SetX(rcDiceList[4].left);
	//	imageBlack->SetY(rcDiceList[4].top);

	//	imageGray = IMAGEMANAGER->FindImage(TEXT("GrayItemUpOffButton"));

	//	imageGray->SetFrameX(0);
	//	imageGray->SetX(rcDiceList[5].left);
	//	imageGray->SetY(rcDiceList[5].top);

	//}

	return true;
}

void DiceFuctionUI::Release()
{
	redFunc->Release();
	yellowFunc->Release();
	blueFunc->Release();
	greenFunc->Release();
	blackFunc->Release();
	grayFunc->Release();
	gsButtom->Release();

	SAFE_DELETE(redFunc);
	SAFE_DELETE(yellowFunc);
	SAFE_DELETE(blueFunc);
	SAFE_DELETE(greenFunc);
	SAFE_DELETE(blackFunc);
	SAFE_DELETE(grayFunc);
	SAFE_DELETE(gsButtom);

	SAFE_DELETE(imageRed);
	SAFE_DELETE(imageYellow);
	SAFE_DELETE(imageBlue);
	SAFE_DELETE(imageGreen);
	SAFE_DELETE(imageBlack);
	SAFE_DELETE(imageGray);


}

void DiceFuctionUI::Update()
{

	redFunc->Update();
	yellowFunc->Update();
	blueFunc->Update();
	greenFunc->Update();
	blackFunc->Update();
	grayFunc->Update();
	gsButtom->Update();
	//GetCursorPos(&_ptMouse);
	//ScreenToClient(_hWnd, &_ptMouse);

	//RedDiceFunc(rcDiceList[0], _ptMouse);
	//YellowDiceFunc(rcDiceList[1], _ptMouse);
	//BlueDiceFunc(rcDiceList[2], _ptMouse);
	//GreenDiceFunc(rcDiceList[3], _ptMouse);
	//BlackDiceFunc(rcDiceList[4], _ptMouse);
	//GrayDiceFunc(rcDiceList[5], _ptMouse);

	//for (int i = 0; i < 6; i++)
	//{
	//	if (PtInRect(&rcDiceList[i], _ptMouse))
	//	{

	//		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	//		{
	//			buttomType = DCBUTTONDIR_DOWN;
	//			image->SetFrameX(1);
	//		}

	//		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
	//		{
	//			buttomType = DCBUTTONDIR_UP;
	//			image->SetFrameX(0);
	//		}

	//	}
	//	else
	//	{
	//		buttomType = DCBUTTONDIR_NONE;
	//		image->SetFrameX(0);
	//	}
	//	
	//}
	
}

void DiceFuctionUI::Render(HDC hdc)
{
	{
		redFunc->Render(hdc);
		yellowFunc->Render(hdc);
		blueFunc->Render(hdc);
		greenFunc->Render(hdc);
		blackFunc->Render(hdc);
		grayFunc->Render(hdc);
		gsButtom->Render(hdc);
	}
	//

	//for (int i = 0; i < 6; i++)
	//{
	//	DrawObject(hdc, rcDiceList[i], 1, RGB(255, 123, 2), ROUNDRECT);
	//}

	//imageRed->FrameRender(hdc, rcDiceList[0].left, rcDiceList[0].top);
	//imageYellow->FrameRender(hdc, rcDiceList[1].left, rcDiceList[1].top);
	//imageBlue->FrameRender(hdc, rcDiceList[2].left, rcDiceList[2].top);
	//imageGreen->FrameRender(hdc, rcDiceList[3].left, rcDiceList[3].top);
	//imageBlack->FrameRender(hdc, rcDiceList[4].left, rcDiceList[4].top);
	//imageGray->FrameRender(hdc, rcDiceList[5].left, rcDiceList[5].top);
}

void DiceFuctionUI::RedDiceFunc(RECT rc, POINT _pt)
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if (PtInRect(&rc, _ptMouse))
	{

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			buttomType = DCBUTTONDIR_DOWN;
			imageRed->SetFrameX(1);
		}

		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
		{
			buttomType = DCBUTTONDIR_UP;
			imageRed->SetFrameX(0);
		}

	}
	else
	{
		buttomType = DCBUTTONDIR_NONE;
		imageRed->SetFrameX(0);
	}
}

void DiceFuctionUI::YellowDiceFunc(RECT rc, POINT _pt)
{
	if (PtInRect(&rc, _ptMouse))
	{

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			buttomType = DCBUTTONDIR_DOWN;
			imageYellow->SetFrameX(1);
		}

		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) )
		{
			buttomType = DCBUTTONDIR_UP;
			imageYellow->SetFrameX(0);
		}

	}
	else
	{
		buttomType = DCBUTTONDIR_NONE;
		imageYellow->SetFrameX(0);
	}
}

void DiceFuctionUI::BlueDiceFunc(RECT rc, POINT _pt)
{
	if (PtInRect(&rc , _ptMouse))
	{

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			buttomType = DCBUTTONDIR_DOWN;
			imageBlue->SetFrameX(1);
		}

		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) )
		{
			buttomType = DCBUTTONDIR_UP;
			imageBlue->SetFrameX(0);
		}

	}
	else
	{
		buttomType = DCBUTTONDIR_NONE;
		imageBlue->SetFrameX(0);
	}
}

void DiceFuctionUI::GreenDiceFunc(RECT rc, POINT _pt)
{
	if (PtInRect(&rc , _ptMouse))
	{

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			buttomType = DCBUTTONDIR_DOWN;
			imageGreen->SetFrameX(1);
		}

		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) )
		{
			buttomType = DCBUTTONDIR_UP;
			imageGreen->SetFrameX(0);
		}

	}
	else
	{
		buttomType = DCBUTTONDIR_NONE;
		imageGreen->SetFrameX(0);
	}
}

void DiceFuctionUI::BlackDiceFunc(RECT rc, POINT _pt)
{
	if (PtInRect(&rc , _ptMouse))
	{

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			buttomType = DCBUTTONDIR_DOWN;
			imageBlack->SetFrameX(1);
		}

		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) )
		{
			buttomType = DCBUTTONDIR_UP;
			imageBlack->SetFrameX(0);
		}

	}
	else
	{
		buttomType = DCBUTTONDIR_NONE;
		imageBlack->SetFrameX(0);
	}
}

void DiceFuctionUI::GrayDiceFunc(RECT rc, POINT _pt)
{
	if (PtInRect(&rc, _ptMouse))
	{

		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			buttomType = DCBUTTONDIR_DOWN;
			imageGray->SetFrameX(1);
		}

		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) )
		{
			buttomType = DCBUTTONDIR_UP;
			imageGray->SetFrameX(0);
		}

	}
	else
	{
		buttomType = DCBUTTONDIR_NONE;
		imageGray->SetFrameX(0);
	}
}

