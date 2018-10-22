#include "Game.h"
#include "FrameRenderTest.h"
#include "Player.h"
#include "Monster.h"

FrameRenderTest::FrameRenderTest()
{
}

FrameRenderTest::~FrameRenderTest()
{
}

bool FrameRenderTest::Init()
{
	_background = IMAGEMANAGER->AddImage(TEXT("BackGround1"), TEXT("../Resource/Sprite/background.bmp"),
		WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddFrameImage(TEXT("Player"), TEXT("../Resource/Sprite/SivaRun.bmp"), 440, 108, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage(TEXT("Monster"), TEXT("../Resource/Sprite/Monster.bmp"), 358, 632, 2, 4, true, RGB(255, 0, 255));

	_player = new Player;
	_monster = new Monster;

	return true;
}

void FrameRenderTest::Release()
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_monster);
}

void FrameRenderTest::Update()
{
	_player->Update();
	_monster->Update();
}

void FrameRenderTest::Render(HDC hdc)
{
	//_background->Render(hdc, 0, 0);
	_background->AlphaRender(hdc, 125);
	_player->Render(hdc);
	_monster->Render(hdc);
}

// new , delete
// malloc, realloc, free