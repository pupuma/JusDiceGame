#include "Game.h"
#include "CameraTest.h"
#include "Player.h"

CameraTest::CameraTest()
{
}

CameraTest::~CameraTest()
{
}

bool CameraTest::Init()
{
	_background = IMAGEMANAGER->AddImage(TEXT("BackGround1"), TEXT("../Resource/Sprite/Back.bmp"),
		1920, 1080, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddFrameImage(TEXT("Player"), TEXT("../Resource/Sprite/SivaRun.bmp"), 440, 108, 8, 2, true, RGB(255, 0, 255));

	_player = new Player;

	_rcClient = { 0, 0, WINSIZEX, WINSIZEY };
	_rcWorld = { 0, 0, 1920, 1080 };

	if (CAMERA->Init(_player->GetPos(), _rcClient, _rcWorld) == false)
	{
		return false;
	}

	return false;
}

void CameraTest::Release()
{
	SAFE_DELETE(_player);
}

void CameraTest::Update()
{
	_player->Update();

	CAMERA->Update();
}

void CameraTest::Render(HDC hdc)
{
	_background->Render(hdc, 0, 0, CAMERA->GetPosition()->x, CAMERA->GetPosition()->y, WINSIZEX, WINSIZEY);
	_player->Render(hdc);
}
