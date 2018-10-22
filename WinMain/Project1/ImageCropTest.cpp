#include "Game.h"
#include "ImageCropTest.h"

ImageCropTest::ImageCropTest()
{

}


ImageCropTest::~ImageCropTest()
{

}

bool ImageCropTest::Init()
{
	_background = new Image();
	_background->Init(TEXT("background.bmp"), WINSIZEX, WINSIZEY);

	_offsetX = _offsetY = 0;
	return true;
}

void ImageCropTest::Release()
{
	SAFE_DELETE(_background);
}

void ImageCropTest::Update()
{
	if (_offsetX <= 0)
	{
		_offsetX = 0;
	}
	if (_offsetY <= 0)
	{
		_offsetY = 0;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		_offsetX -= 2;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		_offsetX += 2;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		_offsetY -= 2;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		_offsetY += 2;
	}


}

void ImageCropTest::Render(HDC hdc)
{
	_background->Render(hdc, 0, 0);
	_background->Render(hdc, 1, 100, _offsetX, _offsetY, 500, 500);
}
