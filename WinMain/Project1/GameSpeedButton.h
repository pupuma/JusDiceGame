#pragma once
class GameSpeedButton
{
private:
	Image* image;
	Image* startImg;
	RECT rc;
	eDCButtom buttomType;
	eGState state;
	bool active;
	POINT ptText;
private:
	int iStartX;
	int iStartY;
	int iPosX;
	int iPosY;
	int iWidth;
	int iHeight;
public:
	GameSpeedButton();
	~GameSpeedButton();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

static DWORD CALLBACK ThreadFunction(LPVOID lpParam);
