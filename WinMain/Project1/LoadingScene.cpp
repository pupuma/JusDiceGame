#include "Game.h"

#include "LoadingScene.h"
#include "ProgressBar.h"


LoadingScene::LoadingScene()
	: _bg(NULL), _loadingBar(NULL), _curCount(0)
{

}

LoadingScene::~LoadingScene()
{
}

bool LoadingScene::Init()
{
	_bg = IMAGEMANAGER->AddImage(TEXT("Loading"), TEXT("../Resource/SpaceShip/Loading.bmp"), WINSIZEX, WINSIZEY , false , COLOR_M);

	_loadingBar = new ProgressBar();
	_loadingBar->Init(TEXT("FrontLoading"), TEXT("BackLoading"), 0, WINSIZEY - 20, WINSIZEX, 20);
	
	_loadingBar->SetGauge(0, 0);


	CreateThread(
		NULL,
		0,
		ThreadFunction,
		this, NULL,
		0
	);

	return true;
}

void LoadingScene::Release()
{
	SAFE_DELETE(_loadingBar);
}

void LoadingScene::Update()
{
	_loadingBar->Update();
	_loadingBar->SetGauge(_curCount, 100);

	if (_curCount == 100)
	{
		SCENEMANAGER->ChangeScene(TEXT("InGame"));
	}
}


void LoadingScene::Render(HDC hdc)
{
	_bg->Render(hdc);
	_loadingBar->Render(hdc);
}



DWORD CALLBACK ThreadFunction(LPVOID lpParam)
{
	LoadingScene* loadHelper = (LoadingScene*)lpParam;

	while (loadHelper->_curCount < 100)
	{
		for (int i = 0; i < 10000; ++i)
		{
			printf_s("·Îµù Áß\n ");
		}
		loadHelper->_curCount++;
	}
	return 0;
}

