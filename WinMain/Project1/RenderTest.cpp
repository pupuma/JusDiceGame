#include "Game.h"

#include "RenderTest.h"



RenderTest::RenderTest()
{
}


RenderTest::~RenderTest()
{
}

bool RenderTest::Init()
{
	_background1.x = 0;
	_background1.image = new Image();
	_background1.image->Init(TEXT("background.bmp"), WINSIZEX, WINSIZEY);

	_background2.x = WINSIZEX;
	_background2.image = new Image();
	_background2.image->Init(TEXT("background.bmp"), WINSIZEX, WINSIZEY);
	return true;
}

void RenderTest::Release()
{
	SAFE_DELETE(_background1.image);
	SAFE_DELETE(_background2.image);
}

void RenderTest::Update()
{
	if (_background1.x <= -WINSIZEX)
	{
		_background1.x = WINSIZEX;
	}
	if(_background2.x <= -WINSIZEY)
	{
		_background2.x = WINSIZEX;

	}

	_background1.x -= 1;
	_background2.x -= 1;

}

void RenderTest::Render(HDC hdc)
{
	_background1.image->Render(hdc, _background1.x ,0);
	_background2.image->Render(hdc, _background2.x, 0);
}
