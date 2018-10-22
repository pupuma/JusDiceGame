#pragma once

// �ֻ��� ���� x�� ���� 
#define GAMEBOARDX 5
// �ֻ��� ���� y�� ���� 
#define GAMEBOARDY 5

// �ֻ������� ���� �� ���� 
#define GAMEBOARDSIZE (GAMEBOARDX * GAMEBOARDY)

class Dice;

class GameBoard
{
private:
	RECT rcTest[GAMEBOARDSIZE];
	
	RECT rcCircle1;
	RECT rcCircle2[2];
	RECT rcCircle3[3];
	RECT rcCircle4[4];
	RECT rcCircle5[5];
	RECT rcCircle6[6];

	// vector?
	std::vector<RECT> vCircleList;
	
private:
	POINT ptGameLine1;
	POINT ptGameLine2;
	POINT ptGameLine3;
	POINT ptGameLine4;
private:
	int iDiceStartX;
	int iDiceStartY;
	int iDiceWidth;
	int iDiceHeight;
private:
	Dice* testDice;
public:
	GameBoard();
	~GameBoard();
public:
	bool Init();
	bool Init(int _width, int _height);
	void Render(HDC hdc);
private:
	void RandomColorPull();
};

