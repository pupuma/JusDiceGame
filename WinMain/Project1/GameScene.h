#pragma once

class GameBoard;

class GameScene
	: public GameNode
{
private:
	GameBoard* gameBoard;
private:
	Image* backGroundImg;
	RECT testRect;
	RECT testRect2;

private:
	int iStartX;
	int iStartY;
public:
	GameScene();
	~GameScene();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};
