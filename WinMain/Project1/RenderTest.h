#pragma once

struct LoopObj
{
	int x;
	Image* image;
};

class RenderTest
	: public GameNode
{
private:
	LoopObj _background1;
	LoopObj _background2;
public:
	RenderTest();
	~RenderTest();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

