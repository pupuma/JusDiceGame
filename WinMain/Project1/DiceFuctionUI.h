#pragma once

class DiceFuncButtom;
class GameSpeedButton;
class DiceFuctionUI
{
private:
	int iRedPrice;
	int iYellowPrice;
	int iBluePrice;
	int iGreenPrice;
	int iBlackPrice;
	int iGrayPrice;

	POINT ptRed;
	POINT ptYellow;
	POINT ptBlue;
	POINT ptGreen;
	POINT ptBlack;
	POINT ptGray;


private:
	Image* imageRed;
	Image* imageYellow;
	Image* imageBlue;
	Image* imageGreen;
	Image* imageBlack;
	Image* imageGray;

	RECT rc;
	eDCButtom buttomType;
	eDiceColor color;
	std::vector<RECT> rcDiceList;
private:
	int iStartX;
	int iStartY;
	int iPosX;
	int iPosY;
	int iWidth;
	int iHeight;
private:
	DiceFuncButtom* redFunc;
	DiceFuncButtom* yellowFunc;
	DiceFuncButtom* blueFunc;
	DiceFuncButtom* greenFunc;
	DiceFuncButtom* blackFunc;
	DiceFuncButtom* grayFunc;
	GameSpeedButton* gsButtom;
public:
	DiceFuctionUI();
	~DiceFuctionUI();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	void RedDiceFunc(RECT rc, POINT _pt);
	void YellowDiceFunc(RECT rc, POINT _pt);
	void BlueDiceFunc(RECT rc, POINT _pt);
	void GreenDiceFunc(RECT rc, POINT _pt);
	void BlackDiceFunc(RECT rc, POINT _pt);
	void GrayDiceFunc(RECT rc, POINT _pt);
};

