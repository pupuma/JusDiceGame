#pragma once
class ImageCropTest
	: public GameNode
{
private:
	Image * _background;
	int _offsetX, _offsetY;

public:
	ImageCropTest();
	~ImageCropTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

