#include "Game.h"
#include "GameScene.h"
#include "GameBoard.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

bool GameScene::Init()
{
	// 게임 배경 이미지 
	backGroundImg = IMAGEMANAGER->AddImage(TEXT("StartBack1"), TEXT("../../Resource/BMP//GameScene.bmp"), WINSIZEX, WINSIZEY, false, COLOR_M);
	
	//---------Test
	iStartX = 113;
	iStartY = 207;

	//testRect = RectMake(113, 207, 73, 60);
	//testRect2 = RectMake(113, 207, 73, 60);
	testRect2 = RectMakeCenter(150, 237, 73, 60);
	testRect = RectMakeCenter(59, 60, 54, 44);
	// Game Line Init 


	// GameBoard 
	{
		gameBoard = new GameBoard();
		if (!gameBoard->Init())
		{
			return false; 
		}
	}

	{
		GAMESYS->SetRound(3);
		GAMESYS->AddEnemy();
	}
	return true;
}

void GameScene::Release()
{
}

void GameScene::Update()
{
	gameBoard->Update();
}

void GameScene::Render(HDC hdc)
{
	{
		backGroundImg->Render(hdc);
		//DrawObject(hdc, testRect, 1, RGB(255, 125, 125), RECTANGLE);
		//DrawObject(hdc, testRect2, 1, RGB(255, 125, 125), RECTANGLE);

	}
	
	{
		gameBoard->Render(hdc);
	}
	
	{
		DrawObject(hdc, testRect, 1, RGB(234, 57, 67), ROUNDRECT, 20, 20);
	}

	
	// 도형 그리기 
	//RoundRect(hdc, testRect.left, testRect.top, testRect.right, testRect.bottom, 30, 30);
}
