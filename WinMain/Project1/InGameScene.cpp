#include "Game.h"
#include "InGameScene.h"

#include "SpaceShip.h"
#include "Enemy.h"

InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

bool InGameScene::Init()
{
	ship = new SpaceShip();
	ship->Init();
	
	enemy = new Enemy();
	enemy->Init();

	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	back = IMAGEMANAGER->FindImage("background2");

	return true;
}

void InGameScene::Release()
{
	SAFE_DELETE(ship);
}

void InGameScene::Update()
{
	//if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	//{
	//	GetCursorPos(&_ptMouse);
	//	ScreenToClient(_hWnd, &(_ptMouse));
	//	if (PtInRect(&rc, _ptMouse))
	//	{
	//		SCENEMANAGER->ChangeScene("Start");
	//	}
	//}
	ship->Update();
	enemy->Update();
}

void InGameScene::Render(HDC hdc)
{
	back->Render(hdc);
	ship->Render(hdc);
	enemy->Render(hdc);
//	DrawObject(hdc, rc, 1, RGB(125, 125, 125), RECTANGLE);

}
