#include "Game.h"
#include "DiceCreateButton.h"



DiceCreateButton::DiceCreateButton()
{
}


DiceCreateButton::~DiceCreateButton()
{
}

bool DiceCreateButton::Init()
{
	image = IMAGEMANAGER->FindImage(TEXT("GameDiceInitButton"));

	// left ,top
	iStartX = 245;
	iStartY = 580;

	iWidth = 99;
	iHeight = 83;

	iPosX = iStartX + iWidth / 2;
	iPosY = iStartY + iHeight / 2;
	rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

	image->SetFrameX(0);
	image->SetX(rc.left);
	image->SetX(rc.top);

	return true;
}

void DiceCreateButton::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	
	
	if (PtInRect(&rc, _ptMouse))
	{
		
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			buttomType = DCBUTTONDIR_DOWN;
			image->SetFrameX(1);
		}

		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
		{
			buttomType = DCBUTTONDIR_UP;
			image->SetFrameX(0);
			GAMESYS->AddDice();

		}


		
		
	}
	else
	{
		buttomType = DCBUTTONDIR_NONE;
		image->SetFrameX(0);

	}

	

}

void DiceCreateButton::Render(HDC hdc)
{
	image->FrameRender(hdc, rc.left, rc.top);
}
