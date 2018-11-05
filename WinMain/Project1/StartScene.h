#pragma once


// TitleScene
class Button;


class StartScene
	: public GameNode
{
private:
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
private:
	//RECT rc;
	Image* back;
	Image* buttom;

	Image* info;
	Image* buttom2;
	Image* buttom3;


	bool isStart;
	bool isClick;
public:
	StartScene();
	~StartScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);


};

