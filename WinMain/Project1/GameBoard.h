#pragma once

// 주사위 놓을 x축 개수 
#define GAMEBOARDX 5
// 주사위 놓을 y축 개수 
#define GAMEBOARDY 5

// 주사위게임 보드 총 개수 
#define GAMEBOARDSIZE (GAMEBOARDX * GAMEBOARDY)



class Dice;
class Bullet;


class GameBoard
{
private:
	std::list<std::pair<int, Dice*>> diceList;
	std::list<std::pair<int, Dice*>>::iterator it;
	
	//std::list<std::pair<int, Dice*>>::iterator it_Select;
	int iSelectNumber;
	int iDestSelectNumber;

	TCHAR str[256];

private:
	RECT rcTest[GAMEBOARDSIZE];
	int index;
	
	
	RECT rcCircle1;
	RECT rcCircle2[2];
	RECT rcCircle3[3];
	RECT rcCircle4[4];
	RECT rcCircle5[5];
	RECT rcCircle6[6];

	// vector?
	std::vector<RECT> vCircleList;
	//std::vector<Dice*> diceList;

private:
	int iDiceStartX;
	int iDiceStartY;
	int iDiceWidth;
	int iDiceHeight;

	int iIndex;
	bool isClicked;

private:
	RECT rcGameBoard;
public:
	GameBoard();
	~GameBoard();
public:
	bool Init();
	bool Init(int _width, int _height);
	void Update();
	void Render(HDC hdc);
public:
	RECT GetRectGameBoard() { return rcGameBoard; }
};

