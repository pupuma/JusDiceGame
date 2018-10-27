#include "Game.h"
#include "MainGame.h"

#include "StartScene.h"
#include "LoadingScene.h"
#include "GameScene.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

bool MainGame::Init()
{
	GameNode::Init(true);

	//
	GAMESYS->Init();
	// 이미지 매니져 초기화 
	IMAGEMANAGER->AddImage(TEXT("FrontLoading"), TEXT("../Resource/SpaceShip/hpBarTop.bmp"), 0, WINSIZEY - 20,
		WINSIZEX, 20, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("BackLoading"), TEXT("../Resource/SpaceShip/hpBarBottom.bmp"), 0, WINSIZEY - 20,
		WINSIZEX, 20, true, COLOR_M);

	IMAGEMANAGER->AddFrameImage(TEXT("TestDice"), TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("GameDiceInitButton"), TEXT("../../Resource/BMP/GameDiceInitButton.bmp"), 220, 91, 2, 1, true, COLOR_M);

	{
		IMAGEMANAGER->AddImage(TEXT("RedDiceOff"), TEXT("../../Resource/BMP/RedDiceOff.bmp"),73,62,true,COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("RedDiceOn"), TEXT("../../Resource/BMP/RedDiceOn.bmp"), 73, 62, true, COLOR_M);

		IMAGEMANAGER->AddImage(TEXT("YellowDiceOff"), TEXT("../../Resource/BMP/YellowDiceOff.bmp"), 73, 62, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("YellowDiceOn"), TEXT("../../Resource/BMP/YellowDiceOn.bmp"), 73, 62, true, COLOR_M);

		IMAGEMANAGER->AddImage(TEXT("BlueDiceOff"), TEXT("../../Resource/BMP/BlueDiceOff.bmp"), 73, 62, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("BlueDiceOn"), TEXT("../../Resource/BMP/BlueDiceOn.bmp"), 73, 62, true, COLOR_M);

		IMAGEMANAGER->AddImage(TEXT("GreenDiceOff"), TEXT("../../Resource/BMP/GreenDiceOff.bmp"), 73, 62, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("GreenDiceOn"), TEXT("../../Resource/BMP/GreenDiceOn.bmp"), 73, 62, true, COLOR_M);

		IMAGEMANAGER->AddImage(TEXT("GrayDiceOff"), TEXT("../../Resource/BMP/GrayDiceOff.bmp"), 73, 62, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("GrayDiceOn"), TEXT("../../Resource/BMP/GrayDiceOn.bmp"), 73, 62, true, COLOR_M);

		IMAGEMANAGER->AddImage(TEXT("BlackDiceOff"), TEXT("../../Resource/BMP/BlackDiceOff.bmp"), 73, 62, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("BlackDiceOn"), TEXT("../../Resource/BMP/BlackDiceOn.bmp"), 73, 62, true, COLOR_M);

	}

	//
	STATEMANAGER->StateInit();
	//// SCENE
	//SCENEMANAGER->AddScene(TEXT("Start"), new StartScene());
	//SCENEMANAGER->AddScene(TEXT("Loading"), new LoadingScene());
	SCENEMANAGER->AddScene(TEXT("InGame"), new GameScene());




	//// 첫 씬의 설정 

	// ------------------------------------------------------------------------
	SCENEMANAGER->Init();
	SCENEMANAGER->ChangeScene(TEXT("InGame"));
	// ------------------------------------------------------------------------
	return true;

}
// 크리티컬 색션
void MainGame::Release()
{
	GameNode::Release();

	//================
	IMAGEMANAGER->Release();
	SCENEMANAGER->Release();
	//================
}

void MainGame::Update()
{
	GameNode::Update();

	//================
	SCENEMANAGER->Update();
	//================
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================
	SCENEMANAGER->Render(backDC);
	//================
	this->GetBackBuffer()->Render(hdc, 0, 0);
}

