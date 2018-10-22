#include "Game.h"
#include "GameTestScene.h"



GameTestScene::GameTestScene()
{
}


GameTestScene::~GameTestScene()
{
}

bool GameTestScene::Init()
{
	IMAGEMANAGER->AddImage(TEXT("BACK"), TEXT("../Resource/Image/Game3.bmp"), 600, 800, false, RGB(0, 0, 0));
	return true;
}

void GameTestScene::Release()
{
}

void GameTestScene::Update()
{
}

void GameTestScene::Render(HDC hdc)
{
	IMAGEMANAGER->Render(TEXT("BACK"), hdc);
}
