#pragma once

#include "GameNode.h"

class Enemy;

class AlphaRenderTest
	: public GameNode
{
	Enemy*	 ufo;
public:
	AlphaRenderTest();
	~AlphaRenderTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

