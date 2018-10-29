#include "Game.h"
#include "GameScene.h"
#include "GameBoard.h"

#include "Enemy.h"
#include "DiceCreateButton.h"

GameScene::GameScene()
{
	iEnemyStartX = 0;
	iEnemyStartY = 0;

	_type = eGameType::GMAE_PLAY;
}


GameScene::~GameScene()
{
}

bool GameScene::Init()
{
	// 게임 배경 이미지 
	backGroundImg = IMAGEMANAGER->AddImage(TEXT("StartBack1"), TEXT("../../Resource/BMP/GameScene.bmp"), WINSIZEX, WINSIZEY, false, COLOR_M);
	
	//---------Test
	iStartX = 113;
	iStartY = 207;

	//testRect = RectMake(113, 207, 73, 60);
	//testRect2 = RectMake(113, 207, 73, 60);
	testRect2 = RectMakeCenter(150, 237, 73, 60);
	testRect = RectMakeCenter(59, 60, 54, 44);
	// Game Line Init 
	{
		ptGameLine1 = { 59, 0 };
		ptGameLine2 = { 59, 558 };
		ptGameLine3 = { 540, 558 };
		ptGameLine4 = { 540, 0 };

		std::vector<POINT> gameLineList;

		gameLineList.push_back(ptGameLine1);
		gameLineList.push_back(ptGameLine2);
		gameLineList.push_back(ptGameLine3);
		gameLineList.push_back(ptGameLine4);

		GAMESYS->SetGameLine(gameLineList);


	}	

	// GameBoard 
	{
		gameBoard = new GameBoard();
		if (!gameBoard->Init())
		{
			return false;
		}

	}
	// Game Enemy
	{
		int currentY = -300;
		int iEnemyCount = GAMESYS->GetRound();
		for (int i = 0; i < 6; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Init(currentY);
			currentY -= (10 + enemy->GetHeight());
			enemyList.push_back(enemy);
		}

	}
	

	{
		//GAMESYS->SetRound(3);

		GAMESYS->SetEnemyList(enemyList);
	}

	// Dice Create Button
	{
		dcButtom = new DiceCreateButton();
		dcButtom->Init();
	}
	return true;
}

void GameScene::Release()
{
}

void GameScene::Update()
{


	{
		dcButtom->Update();
	}


	if (_type == eGameType::GMAE_IDLE)
	{
		GAMESYS->SetEnemyList(enemyList);
		//GAMESYS->CollisionEnemy(enemyList);
		for (it = enemyList.begin(); it != enemyList.end(); it++)
		{
			//(*it)->Update();
		}
		gameBoard->Update();


	}
	else if (_type == eGameType::GMAE_PLAY)
	{
		enemyList = GAMESYS->GetEnemyList();
		gameBoard->Update();
		//GAMESYS->CollisionEnemy(enemyList);

		for (it = enemyList.begin(); it != enemyList.end(); it++)
		{
			(*it)->Update();
		}

		GAMESYS->CollisionObject(enemyList);

	}
	else
	{
		//GAMESYS->SetEnemyList(enemyList);
		//gameBoard->Update();

	}




}

void GameScene::Render(HDC hdc)
{
	{
		backGroundImg->Render(hdc);
		//DrawObject(hdc, testRect, 1, RGB(255, 125, 125), RECTANGLE);
		//DrawObject(hdc, testRect2, 1, RGB(255, 125, 125), RECTANGLE);

	}
	
	// Draw Game Line 
	{
		DrawLine(hdc, ptGameLine1, ptGameLine2, 2, RGB(0, 0, 0));
		DrawLine(hdc, ptGameLine2, ptGameLine3, 2, RGB(0, 0, 0));
		DrawLine(hdc, ptGameLine3, ptGameLine4, 2, RGB(0, 0, 0));

	}

	
	
	// Enemy
	{
		for (it = enemyList.begin(); it != enemyList.end(); it++)
		{
			(*it)->Render(hdc);
		}
		//DrawObject(hdc, testRect, 1, RGB(234, 57, 67), ROUNDRECT, 20, 20);

	}
	
	{
		gameBoard->Render(hdc);
	}

	// Dice Create Buttom Draw
	{
		dcButtom->Render(hdc);
	}
	
	// 도형 그리기 
	//RoundRect(hdc, testRect.left, testRect.top, testRect.right, testRect.bottom, 30, 30);
}
