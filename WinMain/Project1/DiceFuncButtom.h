#pragma once
class DiceFuncButtom
{
protected:
	Image* img;
	RECT rc;
	eButtom buttomType;

	POINT ptPrice;
	POINT ptLevel;
	POINT ptDamage;
	POINT ptEffect;

	int iLevel;
	int iDamage;
	int iCount;

protected:
	int iStartX;
	int iStartY;
	int iPosX;
	int iPosY;
	int iWidth;
	int iHeight;
public:
	DiceFuncButtom();
	~DiceFuncButtom();
public:
	virtual bool Init();
	virtual void Update();
	virtual void Release();
	void Render(HDC hdc);
public:
	virtual void TextRender(HDC hdc);
};

