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
	//_bg = IMAGEMANAGER->FindImage("Loading");
	_bg = IMAGEMANAGER->AddImage(TEXT("Loading"), TEXT("../Resource/SpaceShip/Loading.bmp"), WINSIZEX, WINSIZEY , false , COLOR_M);

	_loadingBar = new ProgressBar();
	_loadingBar->Init(TEXT("FrontLoading"), TEXT("BackLoading"), 0, WINSIZEY - 20, WINSIZEX, 20);
	
	_loadingBar->SetGauge(0, 0);


	//_beginthreadEx

	//CreateThread(
	// 정보 은닉을 위해 LPSECURITY_ATTRIBUTES 로 넘겨 줘야 한다. ,
	// 쓰레드가 사용할 스텍 사이즈,
	// 쓰레드 콜백 함수 ,
	// 쓰레드 콜백 함수가 넘겨 받을 매개변수, ,
	// 쓰레드 우선순위 ( 쓰레드를 만들때 일시 정지 상태인지 아닌지 ) 플래그 ,
	// 쓰레드 ID );
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

//---------------------------------------------------------
// 씬 전환 사이에 처리해야 할 작업들 처리
// 쓰레드 

// return 0 이 되면 자동적으로 메모리에서 삭제 된다. ( delete ) 

DWORD CALLBACK ThreadFunction(LPVOID lpParam)
{
	LoadingScene* loadHelper = (LoadingScene*)lpParam;

	while (loadHelper->_curCount < 100)
	{
		for (int i = 0; i < 10000; ++i)
		{
			printf_s("로딩 중\n ");
		}
		loadHelper->_curCount++;
	}
	return 0;
}


// 씬 메니져 전환 사이에 로딩씬이 필요 없다. 
// os 가 프로세스를 만든다.\
// 해당 프로세스는 해당 os 한데 메모리를 할당 받는다.
// 프로세스는 하나의 프로그램이 실행되는 단위
// 쓰레드란 이 프로세스가 실행되는 실행 단위 
// 프로세스를 실행시키면 os가 메모리를 할당 받은 후 , 메인 함수를 만나면 메인 쓰레드를 만든다. 
// 그 외에 프로세스안에 어떠한 로직이 최소단위 하나의 쓰레드를 하나의 호출 가능하다.
// 여러개의 쓰레드는 메인 쓰레드 와 다른 쓰레드를 번갈아 가면서 실행시킨다. ( 컨텍티스 스위칭 )
// 쓰레드는 생성 할 때 스택을 생성한다.