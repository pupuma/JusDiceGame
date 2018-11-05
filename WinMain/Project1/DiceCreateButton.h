#pragma once




class DiceCreateButton
{
private:
	Image* image;
	RECT rc;
	eDCButtom buttomType;
	POINT ptGold;
private:
	int iStartX;
	int iStartY;
	int iPosX;
	int iPosY;
	int iWidth;
	int iHeight;
	int iGold;
public:
	DiceCreateButton();
	~DiceCreateButton();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:

	
};

