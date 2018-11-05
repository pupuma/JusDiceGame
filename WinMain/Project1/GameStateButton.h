#pragma once

class GameStateButton
{
private:
	Image* image;
	Image* pauseImg;
	RECT rc;
	eDCButtom buttomType;
	eGState state;
private:
	int iStartX;
	int iStartY;
	int iPosX;
	int iPosY;
	int iWidth;
	int iHeight;
public:
	GameStateButton();
	~GameStateButton();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

static DWORD CALLBACK ThreadFunction(LPVOID lpParam);
