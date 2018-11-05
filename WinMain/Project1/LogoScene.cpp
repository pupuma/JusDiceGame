#include "Game.h"
#include "LogoScene.h"



LogoScene::LogoScene()
{
	fDeltaTime = 2.0f;
}


LogoScene::~LogoScene()
{
}

bool LogoScene::Init()
{
	img = IMAGEMANAGER->FindImage(TEXT("Logo"));
	return true;
}

void LogoScene::Update()
{
	fDeltaTime -= TIMEMANAGER->GetElapsedTime();

	if (fDeltaTime <= 0)
	{
		SCENEMANAGER->ChangeScene(TEXT("Start"));
	}
}

void LogoScene::Render(HDC hdc)
{
	img->Render(hdc);
}
