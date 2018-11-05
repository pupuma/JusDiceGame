#include "Game.h"
#include "GameStateButton.h"
#include "Enemy.h"


GameStateButton::GameStateButton()
{
}


GameStateButton::~GameStateButton()
{
}

bool GameStateButton::Init()
{
	{
		state = GAMESYS->GetGameState();

	}

	{
		image = IMAGEMANAGER->FindImage(TEXT("StartButton"));

		// left ,top
		iStartX = 243;
		iStartY = 0;

		iWidth = 112;
		iHeight = 97;

		iPosX = iStartX + iWidth / 2;
		iPosY = iStartY + iHeight / 2;
		rc = RectMakeCenter(iPosX, iPosY, iWidth, iHeight);

		image->SetFrameX(0);
		image->SetX(rc.left);
		image->SetY(rc.top);

	}
	
	{
		pauseImg = IMAGEMANAGER->FindImage(TEXT("PauseButton"));

		pauseImg->SetFrameX(0);
		pauseImg->SetX(rc.left);
		pauseImg->SetY(rc.top);
	}
	return true;
}

void GameStateButton::Release()
{
	//image->Release();
	//pauseImg->Release();

	//SAFE_DELETE(image);
	//SAFE_DELETE(pauseImg);

}

void GameStateButton::Update()
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
				image->SetFrameX(1);
			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
			{
				buttomType = DCBUTTONDIR_UP;
				image->SetFrameX(0);
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
			image->SetFrameX(0);

		}

	}
	
	if (state == GAMESTATE_START)
	{
		if (PtInRect(&rc, _ptMouse))
		{

			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				buttomType = DCBUTTONDIR_DOWN;
				pauseImg->SetFrameX(1);
			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
			{
				buttomType = DCBUTTONDIR_UP;
				pauseImg->SetFrameX(0);
				GAMESYS->SetGameState(GAMESTATE_STOP);

			}

		}
		else
		{
			buttomType = DCBUTTONDIR_NONE;
			pauseImg->SetFrameX(0);

		}
	}
	
	if (state == GAMESTATE_STOP)
	{
		if (PtInRect(&rc, _ptMouse))
		{

			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				buttomType = DCBUTTONDIR_DOWN;
				pauseImg->SetFrameX(1);
			}

			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && buttomType == DCBUTTONDIR_DOWN)
			{
				buttomType = DCBUTTONDIR_UP;
				pauseImg->SetFrameX(0);
				GAMESYS->SetGameState(GAMESTATE_START);

			}

		}
		else
		{
			buttomType = DCBUTTONDIR_NONE;
			pauseImg->SetFrameX(0);

		}
	}



}

void GameStateButton::Render(HDC hdc)
{
	if (state == GAMESTATE_IDLE || state == GAMESTATE_STOP)
	{
		image->FrameRender(hdc, rc.left, rc.top); 

	}
	else if (state == GAMESTATE_START)
	{
		pauseImg->FrameRender(hdc, rc.left, rc.top);

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

