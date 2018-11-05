#include "Game.h"
#include "GameScene.h"
#include "GameBoard.h"

#include "Enemy.h"
#include "DiceCreateButton.h"
#include "GameStateButton.h"
#include "DiceFuctionUI.h"

GameScene::GameScene()
{
	iEnemyStartX = 0;
	iEnemyStartY = 0;

	fDeltaTime = 1.5f;
	iCount = 0;
	iRound = 1;
	iEnemyCount = 0;
	iGold = 0;
}


GameScene::~GameScene()
{
}

bool GameScene::Init()
{
	// 게임 배경 이미지 
	backGroundImg = IMAGEMANAGER->AddImage(TEXT("StartBack1"), TEXT("../../Resource/BMP/GameScene.bmp"), WINSIZEX, WINSIZEY, false, COLOR_M);
	
	state = GAMESTATE_IDLE;
	GAMESYS->SetGameState(state);
	//---------Test
	iStartX = 113;
	iStartY = 207;

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

	// Dice Create Button
	{
		dcButtom = new DiceCreateButton();
		dcButtom->Init();

		gsButtom = new GameStateButton();
		gsButtom->Init();

		diceUI = new DiceFuctionUI();
		diceUI->Init();
	}

	{
		ptRound = { 240,120 };
		ptRound2 = { 270,120 };
		ptGold = { 92,618 };
	}

	GAMESYS->AddDice();

	stopImgBack= IMAGEMANAGER->FindImage("gray");
	return true;
}

void GameScene::Release()
{
	gsButtom->Release();
	dcButtom->Release();
	diceUI->Release();

	delete gsButtom;
	delete dcButtom;
	delete diceUI;
	delete gameBoard;

}

void GameScene::Update()
{
	{
		state = GAMESYS->GetGameState();
		gsButtom->Update();

	}
	if (state != GAMESTATE_DIE)
	{
		//
		dcButtom->Update();
		diceUI->Update();
	}

	

	if (KEYMANAGER->IsOnceKeyDown(VK_F1))
	{
		GAMESYS->SetGold(10000);

	}

	if (state == GAMESTATE_IDLE)
	{
		//_type = eGameType::GMAE_PLAY;

		//GAMESYS->SetEnemyList(enemyList);
		iRound = GAMESYS->GetRound();



		gameBoard->Update();
	}
	
	if (state == GAMESTATE_START)
	{

		gameBoard->Update();

		{
			GAMESYS->EnemyProDuce();
			GAMESYS->EnemyUpdate();

		}
	}
	
	if (state == GAMESTATE_DIE)
	{
		gameBoard->Release();
		GAMESYS->Release();
		//Release();
		GAMESYS->SetGameState(GAMESTATE_IDLE);
		GAMESYS->SetFirstStart(true);
		SCENEMANAGER->ChangeScene(TEXT("Start"));
		return;
	}

	if (state == GAMESTATE_STOP)
	{

	}

	{
		EFFECTMANAGER->Update();

		GAMESYS->Update();
	}
}

void GameScene::Render(HDC hdc)
{
	
	{
		{
			backGroundImg->Render(hdc);
		}

		// Draw Game Line 
		{
			DrawLine(hdc, ptGameLine1, ptGameLine2, 2, RGB(0, 0, 0));
			DrawLine(hdc, ptGameLine2, ptGameLine3, 2, RGB(0, 0, 0));
			DrawLine(hdc, ptGameLine3, ptGameLine4, 2, RGB(0, 0, 0));

		}



		// Enemy
		{

			{
				gameBoard->FullAttactRender(hdc);
			}

			{
				GAMESYS->EnemyListRender(hdc);
			}

		}

		{
			EFFECTMANAGER->Render(hdc);

			gameBoard->Render(hdc);
		}

		// Dice Create Buttom Draw
		
		{
			DrawFont(hdc);
		}
	}
	
	if (state == GAMESTATE_STOP)
	{
		stopImgBack->AlphaRender(hdc,50);

		{
			TCHAR str[256] = { 0, };
			_stprintf(str, TEXT("P A U S E"));
			POINT pt = { 250 , 300 };
			FONTMANAGER->RenderText(hdc, TEXT("AdobeBB"), str, &pt, RGB(255, 255, 255));
		}
	}

	{
		dcButtom->Render(hdc);
		gsButtom->Render(hdc);
		diceUI->Render(hdc);
	}

}

void GameScene::DrawFont(HDC hdc)
{

	{
		TCHAR str[256] = { 0, };
		iGold = GAMESYS->GetGold();
		_stprintf(str, TEXT("%d"), iGold);
		
		FONTMANAGER->RenderText(hdc, TEXT("AdobeB"), str, &ptGold, RGB(0, 0, 0));
	}

	if (state == GAMESTATE_IDLE)
	{
		TCHAR str[256] = { 0, };
		_stprintf(str, TEXT("Wav %d"), iRound);
		FONTMANAGER->RenderText(hdc, TEXT("AdobeBB"), str, &ptRound, RGB(0, 0, 0));
	}
	else if (state == GAMESTATE_START || state == GAMESTATE_STOP)
	{
		TCHAR str[256] = { 0, };
		iEnemyCount = GAMESYS->GetEnemyCount();
		_stprintf(str, TEXT("%d / %d"), iEnemyCount,iRound);
		FONTMANAGER->RenderText(hdc, TEXT("AdobeBB"), str, &ptRound2, RGB(0, 0, 0));
	}
	//FONTMANAGER->RenderText(hdc, TEXT("AdobeBB"), TEXT("Start"), &ptRound, RGB(0, 0, 0));
}

