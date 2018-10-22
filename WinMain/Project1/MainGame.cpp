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

	// �̹��� �Ŵ��� �ʱ�ȭ 
	IMAGEMANAGER->AddImage(TEXT("FrontLoading"), TEXT("../Resource/SpaceShip/hpBarTop.bmp"), 0, WINSIZEY - 20,
		WINSIZEX, 20, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("BackLoading"), TEXT("../Resource/SpaceShip/hpBarBottom.bmp"), 0, WINSIZEY - 20,
		WINSIZEX, 20, true, COLOR_M);

	IMAGEMANAGER->AddFrameImage(TEXT("TestDice"), TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);

	//// SCENE
	//SCENEMANAGER->AddScene(TEXT("Start"), new StartScene());
	//SCENEMANAGER->AddScene(TEXT("Loading"), new LoadingScene());
	SCENEMANAGER->AddScene(TEXT("InGame"), new GameScene());




	//// ù ���� ���� 

	// ------------------------------------------------------------------------
	SCENEMANAGER->Init();
	SCENEMANAGER->ChangeScene(TEXT("InGame"));
	// ------------------------------------------------------------------------
	return true;

}
// ũ��Ƽ�� ����
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

