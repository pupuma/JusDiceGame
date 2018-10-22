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
	// ���� ������ ���� LPSECURITY_ATTRIBUTES �� �Ѱ� ��� �Ѵ�. ,
	// �����尡 ����� ���� ������,
	// ������ �ݹ� �Լ� ,
	// ������ �ݹ� �Լ��� �Ѱ� ���� �Ű�����, ,
	// ������ �켱���� ( �����带 ���鶧 �Ͻ� ���� �������� �ƴ��� ) �÷��� ,
	// ������ ID );
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
// �� ��ȯ ���̿� ó���ؾ� �� �۾��� ó��
// ������ 

// return 0 �� �Ǹ� �ڵ������� �޸𸮿��� ���� �ȴ�. ( delete ) 

DWORD CALLBACK ThreadFunction(LPVOID lpParam)
{
	LoadingScene* loadHelper = (LoadingScene*)lpParam;

	while (loadHelper->_curCount < 100)
	{
		for (int i = 0; i < 10000; ++i)
		{
			printf_s("�ε� ��\n ");
		}
		loadHelper->_curCount++;
	}
	return 0;
}


// �� �޴��� ��ȯ ���̿� �ε����� �ʿ� ����. 
// os �� ���μ����� �����.\
// �ش� ���μ����� �ش� os �ѵ� �޸𸮸� �Ҵ� �޴´�.
// ���μ����� �ϳ��� ���α׷��� ����Ǵ� ����
// ������� �� ���μ����� ����Ǵ� ���� ���� 
// ���μ����� �����Ű�� os�� �޸𸮸� �Ҵ� ���� �� , ���� �Լ��� ������ ���� �����带 �����. 
// �� �ܿ� ���μ����ȿ� ��� ������ �ּҴ��� �ϳ��� �����带 �ϳ��� ȣ�� �����ϴ�.
// �������� ������� ���� ������ �� �ٸ� �����带 ������ ���鼭 �����Ų��. ( ����Ƽ�� ����Ī )
// ������� ���� �� �� ������ �����Ѵ�.