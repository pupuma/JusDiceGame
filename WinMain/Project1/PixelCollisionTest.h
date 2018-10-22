
#pragma once

#include "GameNode.h"

class PixelCollisionTest
	: public GameNode
{
private:
	Image* _bg;
	Image*	_mountain;
	Image*	_ball;

	RECT	_rc;
	float	_x, _y;
	int		_probY;
	COLORREF _colorkey;
public:
	PixelCollisionTest();
	~PixelCollisionTest();
public:
	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

