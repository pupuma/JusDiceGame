#include "Game.h"

#include "StartScene.h"
#include "Button.h"


StartScene::StartScene()
{
	isStart = false;
}


StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	//back = IMAGEMANAGER->AddImage(TEXT("StartBack1"), TEXT("../../Resource/BMP//GameScene.bmp"), WINSIZEX, WINSIZEY, false, COLOR_M);

	//IMAGEMANAGER->AddFrameImage(TEXT("Button01"), TEXT("../Resource/SpaceShip/button1.bmp"),
	//	0, 0, 122, 62, 1, 2, true, RGB(255, 0, 255));

	back = IMAGEMANAGER->FindImage(TEXT("Title"));
	buttom = IMAGEMANAGER->FindImage(TEXT("StartButton"));

	info = IMAGEMANAGER->FindImage(TEXT("Game3"));
	buttom2 = IMAGEMANAGER->FindImage(TEXT("XOnButton"));
	buttom3 = IMAGEMANAGER->FindImage(TEXT("XOffButton"));


	iStartX = 243;
	iStartY = 0;

	iWidth = 112;
	iHeight = 97;

	iPosX = iStartX + iWidth / 2;
	iPosY = iStartY + iHeight / 2;
	rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

	buttom->SetFrameX(0);
	buttom->SetX(rc.left);
	buttom->SetY(rc.top);

	buttom2->SetX(rc.left);
	buttom2->SetY(rc.top);

	buttom3->SetX(rc.left);
	buttom3->SetY(rc.top);

	//pButton->Init(TEXT("Button01"), WINSIZEX / 2, WINSIZEY / 2,
	//	PointMake(0, 1), PointMake(0, 0), CbScreneChange);
	

	return true;
}
void StartScene::Release()
{
}

void StartScene::Update()
{
	if (GAMESYS->IsFirstStart())
	{
		GAMESYS->Reset();
	}

	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);

	if(!isStart)
	{
		if (PtInRect(&rc, _ptMouse))
		{

			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				buttomType = DCBUTTONDIR_DOWN;
				buttom->SetFrameX(1);
			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
			{
				buttomType = DCBUTTONDIR_UP;
				buttom->SetFrameX(0);
				GAMESYS->ResetEnemyCount();
				isStart = true;
				if (GAMESYS->GetRound() != 1)
				{
					SCENEMANAGER->ChangeScene(TEXT("InGame"));
					GAMESYS->SetGameState(GAMESTATE_IDLE);
					//GAMESYS->Reset();
					//GAMESYS->AddDice();

				}


			}

		}
		else
		{
			buttomType = DCBUTTONDIR_NONE;
			buttom->SetFrameX(0);

		}

	}
	else
	{
		if (PtInRect(&rc, _ptMouse))
		{

			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				buttomType = DCBUTTONDIR_DOWN;
				isClick = true;

			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
			{
				buttomType = DCBUTTONDIR_UP;
				GAMESYS->ResetEnemyCount();
				SCENEMANAGER->ChangeScene(TEXT("InGame"));
				GAMESYS->SetGameState(GAMESTATE_IDLE);
				
				//GAMESYS->Reset();
				//GAMESYS->AddDice();
				isClick = false;
				isStart = false;


			}

		}
		else
		{
			buttomType = DCBUTTONDIR_NONE;
			buttom->SetFrameX(0);
			isClick = false;

		}

	}


	//

}

void StartScene::Render(HDC hdc)
{
	back->Render(hdc);
	if (!isStart)
	{
		buttom->FrameRender(hdc, rc.left, rc.top);
		if (GAMESYS->GetRound() != 1)
		{
			TCHAR str[256] = { 0, };
			int iRound = GAMESYS->GetRound();
			_stprintf(str, TEXT("Bast Wav %d"), iRound);
			POINT pt = { 230,630 };
			FONTMANAGER->RenderText(hdc, TEXT("AdobeBB"), str, &pt, RGB(0, 0, 0));
		}
		
	}
	else
	{
		if (GAMESYS->GetRound() != 1)
		{
			{
				TCHAR str[256] = { 0, };
				int iRound = GAMESYS->GetRound();
				_stprintf(str, TEXT("Bast Wav %d"), iRound);
				POINT pt = { 230,630 };
				FONTMANAGER->RenderText(hdc, TEXT("AdobeBB"), str, &pt, RGB(0, 0, 0));
			}
		}
		else
		{
			info->Render(hdc);
			if (isClick)
			{
				buttom2->Render(hdc);
			}
			else
			{
				buttom3->Render(hdc);
			}
		}

	}
	//back->Render(hdc);
	//pButton->Render(hdc);
}

