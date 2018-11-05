#include "Game.h"
#include "GameSpeedButton.h"

#include "Enemy.h"

GameSpeedButton::GameSpeedButton()
{
}


GameSpeedButton::~GameSpeedButton()
{
}

bool GameSpeedButton::Init()
{
	{
		state = GAMESYS->GetGameState();

	}

	{
		image = IMAGEMANAGER->FindImage(TEXT("SpeedButtom"));

		// left ,top
		iStartX = 497;
		iStartY = 583;
		iWidth = 102;
		iHeight = 84;
		iPosX = iStartX + iWidth / 2;
		iPosY = iStartY + iHeight / 2;
		

		rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);
		ptText = { 550, 560 };

		image->SetFrameX(0);
		image->SetX(rc.left);
		image->SetY(rc.top);

	}

	{
		startImg = IMAGEMANAGER->FindImage(TEXT("SpeedOnButtom"));

		startImg->SetFrameX(0);
		startImg->SetX(rc.left);
		startImg->SetY(rc.top);
	}
	return true;
}

void GameSpeedButton::Release()
{
	//SAFE_DELETE(image);
	//SAFE_DELETE(startImg);

}

void GameSpeedButton::Update()
{
	GetCursorPos(&_ptMouse);
	ScreenToClient(_hWnd, &_ptMouse);
	state = GAMESYS->GetGameState();

	if (state == GAMESTATE_IDLE)
	{
		if (PtInRect(&rc, _ptMouse))
		{

			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				buttomType = DCBUTTONDIR_DOWN;
				startImg->SetFrameX(1);
			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
			{
				buttomType = DCBUTTONDIR_UP;
				startImg->SetFrameX(0);
				GAMESYS->SetGameState(GAMESTATE_START);
				GAMESYS->ResetEnemyCount();

				CreateThread(
					NULL,
					0,
					ThreadFunction,
					this, NULL,
					0
				);

				//GAMESYS->AddDice();


			}

		}
		else
		{
			buttomType = DCBUTTONDIR_NONE;
			startImg->SetFrameX(0);

		}

	}

	if (state == GAMESTATE_START)
	{
		if (PtInRect(&rc, _ptMouse))
		{

			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				buttomType = DCBUTTONDIR_DOWN;
				image->SetFrameX(1);
			}
			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				active = true;
				GAMESYS->IsSpeedUp();
			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
			{
				buttomType = DCBUTTONDIR_UP;
				image->SetFrameX(0);
				active = false;
				GAMESYS->IsSpeedIDle();

			}

		}
		else
		{
			buttomType = DCBUTTONDIR_NONE;
			image->SetFrameX(0);
			active = false;
			GAMESYS->IsSpeedIDle();

		}
	}

}

void GameSpeedButton::Render(HDC hdc)
{
	if (state == GAMESTATE_IDLE)
	{
		startImg->FrameRender(hdc, rc.left, rc.top);
		
		
	}
	else if (state == GAMESTATE_START)
	{
		image->FrameRender(hdc, rc.left, rc.top);

		if (active)
		{
			TCHAR str[256] = { 0, };
			_stprintf(str, TEXT("x4"));

			FONTMANAGER->RenderText(hdc, TEXT("AdobeB"), str, &ptText, RGB(0, 0, 0));
		}
		else
		{
			TCHAR str[256] = { 0, };
			_stprintf(str, TEXT("x2"));

			FONTMANAGER->RenderText(hdc, TEXT("AdobeB"), str, &ptText, RGB(0, 0, 0));
		}
		

	}
}




DWORD CALLBACK ThreadFunction(LPVOID lpParam)
{
	int currentY = -50;
	int iEnemyCount = GAMESYS->GetRound();
	int iHp = GAMESYS->GetEnemyHp();
	eEnemyType type;
	//iEnemyCount = 10;
	if (iEnemyCount % 10 == 0)
	{
		type = eEnemyType::ENEMY_BOSS;
		Enemy* enemy = new Enemy();
		enemy->Init(currentY, type);
		enemy->SetHp(iHp);
		//currentY -= (10 + enemy->GetHeight());
		GAMESYS->AddEnemy(enemy, 0);
	}
	else
	{
		type = eEnemyType::ENEMY_NONE;
		for (int i = 0; i < iEnemyCount; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Init(currentY, type);
			enemy->SetHp(iHp);
			//currentY -= (10 + enemy->GetHeight());
			GAMESYS->AddEnemy(enemy, i);
		}
	}

	return 0;
}

