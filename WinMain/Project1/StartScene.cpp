#include "Game.h"

#include "StartScene.h"
#include "Button.h"


StartScene::StartScene()
{
}


StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	//rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	//back = IMAGEMANAGER->AddFrameImage(TEXT("background"), TEXT("../Resource/Sprite/background.bmp"), WINSIZEX, WINSIZEY, 1, 1, false, RGB(0, 0, 0));
	back = IMAGEMANAGER->AddImage(TEXT("StartBack1"), TEXT("../../Resource/BMP//GameScene.bmp"), WINSIZEX, WINSIZEY, false, COLOR_M);

	IMAGEMANAGER->AddFrameImage(TEXT("Button01"), TEXT("../Resource/SpaceShip/button1.bmp"),
		0, 0, 122, 62, 1, 2, true, RGB(255, 0, 255));

	pButton = new Button();
	assert(pButton != NULL);

	pButton->Init(TEXT("Button01"), WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), CbScreneChange);


	return true;
}
void StartScene::Release()
{
	SAFE_DELETE(pButton);
}

void StartScene::Update()
{
	//if(KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	//{
	//	GetCursorPos(&_ptMouse);
	//	ScreenToClient(_hWnd, &(_ptMouse));
	//	if (PtInRect(&rc, _ptMouse))
	//	{
	//		SCENEMANAGER->ChangeScene("Loading");
	//	}
	//}
	pButton->Update();
}

void StartScene::Render(HDC hdc)
{
	back->Render(hdc);
	pButton->Render(hdc);
	//DrawObject(hdc, rc, 1, RGB(0, 125, 0), RECTANGLE);
}

void StartScene::CbScreneChange()
{
	SCENEMANAGER->ChangeScene(TEXT("InGame"));
}
