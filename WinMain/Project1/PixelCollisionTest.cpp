#include "Game.h"
#include "PixelCollisionTest.h"



PixelCollisionTest::PixelCollisionTest()
{
}


PixelCollisionTest::~PixelCollisionTest()
{
}

bool PixelCollisionTest::Init()
{
	_bg = IMAGEMANAGER->AddImage(TEXT("Back"), TEXT("../Resource/Sprite/background.bmp"), WINSIZEX, WINSIZEY, true, COLOR_M);
	_mountain = IMAGEMANAGER->AddImage(TEXT("Ground"), TEXT("../Resource/Sprite/mountain.bmp"), WINSIZEX, WINSIZEY, true, COLOR_M);

	_ball = IMAGEMANAGER->AddImage(TEXT("Ball"), TEXT("../Resource/Sprite/ball.bmp"), 60, 60, true, COLOR_M);

	_x = WINSIZEX / 2 - 150;
	_y = WINSIZEY / 2 + 400;


	_rc = RectMakeCenter(_x, _y, _ball->GetWidth(), _ball->GetHeight());
	_probY = _y + _ball->GetHeight() / 2;

	return true;
}

void PixelCollisionTest::Release()
{
}

void PixelCollisionTest::Update()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		_x -= 3;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		_x += 3;
	}

	if (_x < _ball->GetHeight())
	{
		_x = _ball->GetWidth();
	}

	if (_x > WINSIZEX - _ball->GetWidth())
	{
		_x = WINSIZEX - _ball->GetWidth();
	}
	COLORREF color;


	_rc = RectMakeCenter(_x, _y, _ball->GetWidth(), _ball->GetHeight());


	// -------------------------------------------------------------------------
	
	//CollisionPixelAndRect(_mountain, _x,_y, _colorKey);
	// 볼에 중점에서  볼의 반지름을 더한 아래 위로 100만큼 탐사 범위 
	
	_probY = _y + _ball->GetHeight() / 2;


	for (int i = _probY - 100; i < _probY + 100; ++i)
	{
		COLORREF color = GetPixel(_mountain->GetMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->GetHeight() / 2;
			break;
		}
	}
	// -------------------------------------------------------------------------

}

void PixelCollisionTest::Render(HDC hdc)
{
	_bg->Render(hdc);
	_mountain->Render(hdc);
	_ball->Render(hdc, _rc.left, _rc.top);
}
