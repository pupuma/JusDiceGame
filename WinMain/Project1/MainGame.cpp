#include "Game.h"
#include "MainGame.h"

#include "StartScene.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "LogoScene.h"

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
		IMAGEMANAGER->AddFrameImage(TEXT("PauseButton"), TEXT("../../Resource/BMP/PauseButton.bmp"), 226, 108, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("StartButton"), TEXT("../../Resource/BMP/StartButton.bmp"), 226, 108, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("BlackBulletEffect"), TEXT("../../Resource/BMP/BlackBulletEffect.bmp"), 360, 30, 12, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("BlueBulletEffect"), TEXT("../../Resource/BMP/BlueBulletEffect.bmp"), 360, 30, 12, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("GreenBullectEffect"), TEXT("../../Resource/BMP/GreenBullectEffect.bmp"), 360, 30, 12, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("GrayBulletEffect"), TEXT("../../Resource/BMP/GrayBulletEffect.bmp"), 360, 30, 12, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("RedBulletEffect"), TEXT("../../Resource/BMP/RedBulletEffect.bmp"), 360, 30, 12, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("YellowBulletEffect"), TEXT("../../Resource/BMP/YellowBulletEffect.bmp"), 360, 30, 12, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("ChainEffect"), TEXT("../../Resource/BMP/ChainEffect.bmp"), 740, 64, 10, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("SpeedButtom"), TEXT("../../Resource/BMP/SpeedButtom.bmp"), 204, 85, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("SpeedOnButtom"), TEXT("../../Resource/BMP/SpeedOnButtom.bmp"), 204, 84,2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("SkelEffect"), TEXT("../../Resource/BMP/SkelEffect.bmp"), 300, 50, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Title"), TEXT("../../Resource/BMP/Title.bmp"), 600, 800, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Game3"), TEXT("../../Resource/BMP/Game3.bmp"), 600, 800, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("XOffButton"), TEXT("../../Resource/BMP/XOffButton.bmp"), 113, 117, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("XOnButton"), TEXT("../../Resource/BMP/XOnButton.bmp"), 113, 117, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("gray"), TEXT("../../Resource/BMP/gray.bmp"), 600, 800, true, COLOR_M);
		IMAGEMANAGER->AddImage(TEXT("Logo"), TEXT("../../Resource/BMP/Logo.bmp"), 600, 800, true, COLOR_M);


		IMAGEMANAGER->AddFrameImage(TEXT("RedItemUpOffButton"), TEXT("../../Resource/BMP/RedItemUpOffButton.bmp"), 154, 64, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("YellowItemUpOffButton"), TEXT("../../Resource/BMP/YellowItemUpOffButton.bmp"), 154, 64, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("BlueItemUpOffButton"), TEXT("../../Resource/BMP/BlueItemUpOffButton.bmp"), 154, 64, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("GreenItemUpOffButton"), TEXT("../../Resource/BMP/GreenItemUpOffButton.bmp"), 154, 64, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("BlackItemUpOffButton"), TEXT("../../Resource/BMP/BlackItemUpOffButton.bmp"), 154, 64, 2, 1, true, COLOR_M);
		IMAGEMANAGER->AddFrameImage(TEXT("GrayItemUpOffButton"), TEXT("../../Resource/BMP/GrayItemUpOffButton.bmp"), 154, 64, 2, 1, true, COLOR_M);


		EFFECTMANAGER->AddEffect(TEXT("BlackBulletEffect"), TEXT("../../Resource/BMP/BlackBulletEffect.bmp"), 360, 30, 30, 30, 1, 1.0f, 100, COLOR_M);
		EFFECTMANAGER->AddEffect(TEXT("BlueBulletEffect"), TEXT("../../Resource/BMP/BlueBulletEffect.bmp"), 360, 30, 30, 30, 1, 1.0f, 100, COLOR_M);
		EFFECTMANAGER->AddEffect(TEXT("GreenBullectEffect"), TEXT("../../Resource/BMP/GreenBullectEffect.bmp"), 360, 30, 30, 30, 1, 1.0f, 100, COLOR_M);
		EFFECTMANAGER->AddEffect(TEXT("GrayBulletEffect"), TEXT("../../Resource/BMP/GrayBulletEffect.bmp"), 360, 30, 30, 30, 1, 1.0f, 100, COLOR_M);
		EFFECTMANAGER->AddEffect(TEXT("RedBulletEffect"), TEXT("../../Resource/BMP/RedBulletEffect.bmp"), 360, 30, 30, 30, 1, 1.0f, 100, COLOR_M);
		EFFECTMANAGER->AddEffect(TEXT("YellowBulletEffect"), TEXT("../../Resource/BMP/YellowBulletEffect.bmp"), 360, 30, 30, 30, 1, 1.0f, 100, COLOR_M);
		EFFECTMANAGER->AddEffect(TEXT("ChainEffect"), TEXT("../../Resource/BMP/ChainEffect.bmp"), 600, 50, 60, 50, 1, 1.0f, 100, COLOR_M);
		EFFECTMANAGER->AddEffect(TEXT("Effect"), TEXT("../../Resource/BMP/Effect.bmp"), 740, 64, 74, 64, 1, 1.0f, 100, COLOR_M);
		EFFECTMANAGER->AddEffect(TEXT("SkelEffect"), TEXT("../../Resource/BMP/SkelEffect.bmp"), 300, 50, 60, 50, 1, 1.0f, 100, COLOR_M);

	}

	{
		SOUNDMANAGER->Init();
		SOUNDMANAGER->AddSound(TEXT("Sound"), TEXT("../Resource/Sound/SoundM/Sound/Sound.wav"), false, false);
	}

	//
	STATEMANAGER->StateInit();
	//// SCENE
	SCENEMANAGER->AddScene(TEXT("Start"), new StartScene());
	SCENEMANAGER->AddScene(TEXT("Logo"), new LogoScene());

	//SCENEMANAGER->AddScene(TEXT("Loading"), new LoadingScene());
	SCENEMANAGER->AddScene(TEXT("InGame"), new GameScene());


	//// 첫 씬의 설정 

	// ------------------------------------------------------------------------
	SCENEMANAGER->Init();
	SCENEMANAGER->ChangeScene(TEXT("Logo"));
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

