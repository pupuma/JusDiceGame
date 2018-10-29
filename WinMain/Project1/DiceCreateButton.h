#pragma once


typedef enum eDiceCreateBUTTTONDIR
{
	DCBUTTONDIR_NONE,
	DCBUTTONDIR_UP,
	DCBUTTONDIR_DOWN,

}eDCButtom;



class DiceCreateButton
{
private:
	Image* image;
	RECT rc;
	eDCButtom buttomType;
private:
	int iStartX;
	int iStartY;
	int iPosX;
	int iPosY;
	int iWidth;
	int iHeight;
public:
	DiceCreateButton();
	~DiceCreateButton();
public:
	bool Init();
	void Update();
	void Render(HDC hdc);
public:

	
};

