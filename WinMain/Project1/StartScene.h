#pragma once


// TitleScene
class Button;


class StartScene
	: public GameNode
{
private:
	//RECT rc;
	Image* back;
	Button * pButton;
public:
	StartScene();
	~StartScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

public:
	static void CbScreneChange();

};

