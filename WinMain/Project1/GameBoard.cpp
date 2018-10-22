#include "Game.h"

#include "GameBoard.h"
#include "Dice.h"


GameBoard::GameBoard()
{
}


GameBoard::~GameBoard()
{
}

bool GameBoard::Init()
{
	

	// GameBoard Dice Position Info  
	{
		//iDiceStartX = 113;
		//iDiceStartY = 207;
		
		iDiceStartX = 148;
		iDiceStartY = 237;

		iDiceWidth = 73;
		iDiceHeight = 60;
		
		int x = iDiceStartX;
		int y = iDiceStartY;

		int temp = 0;
		for (int i = 0; i < GAMEBOARDX; i++)
		{
			for (int j = 0; j < GAMEBOARDY; j++)
			{
				rcTest[temp] = RectMakeCenter(x, y, iDiceWidth, iDiceHeight);
				dice[temp] = new Dice();
				if (!(dice[temp]->Init(x, y)))
				{
					return false;
				}
				x = x + iDiceWidth + 2;

				temp++;
			}
			x = iDiceStartX;
			y = y + iDiceHeight + 2 ;
		}

	}

	// Dice Circle Position 
	{
		int startX = iDiceStartX - iDiceWidth / 2;
		int startY = iDiceStartY - iDiceHeight / 2;


		// Level 1 
		int circleX1 = startX + iDiceWidth / 2; 
		int circleY1 = startY + iDiceHeight / 2;
		rcCircle1 = RectMakeCenter(circleX1, circleY1, 14, 12);


		// Level 2 
		int circleX2 = startX + iDiceWidth / 3; 
		int circleY2 = startY + iDiceHeight / 2;

		for (int i = 0; i < 2; i++)
		{
			rcCircle2[i] = RectMakeCenter(circleX2, circleY2, 14, 12);
			circleX2 += (iDiceWidth / 3);
		}

		// Level 3 
		int circleX3 = startX + iDiceWidth / 4; 
		int circleY3 = startY + iDiceHeight / 4;

		for (int i = 0; i < 3; i++)
		{
			rcCircle3[i] = RectMakeCenter(circleX3, circleY3, 14, 12);
			circleX3 += iDiceWidth / 4;
			circleY3 += iDiceHeight / 4;

		}

		// Level 4 
		int circleX4 = startX + iDiceWidth / 3;
		int circleY4 = startY + iDiceHeight / 3;

		int iTemp = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				rcCircle4[iTemp] = RectMakeCenter(circleX4, circleY4, 14, 12);
				circleX4 += iDiceWidth / 3;
				iTemp++;
			}
			circleX4 = startX + iDiceWidth / 3;
			circleY4 += iDiceHeight / 3;
		}


		// Level 5 

		int circleX5 = startX + iDiceWidth / 4;
		int circleY5 = startY + iDiceHeight / 4;

		iTemp = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				rcCircle5[iTemp] = RectMakeCenter(circleX5, circleY5, 14, 12);
				circleX5 += (iDiceWidth / 4 * 2);
				iTemp++;
			}
			circleX5 = startX + iDiceWidth / 4;
			circleY5 += (iDiceHeight / 4 * 2);
		}
		rcCircle5[4] = rcCircle1;
		
		// Level 6 

		int circleX6 = startX + (iDiceWidth / 6 * 2);
		int circleY6 = startY + iDiceHeight / 4;

		int iTemp2 = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				rcCircle6[iTemp2] = RectMakeCenter(circleX6, circleY6, 14, 12);

				circleX6 += (iDiceWidth / 6  * 2 );
				iTemp2++;
			}
			circleX6 = startX + (iDiceWidth / 6 * 2);
			circleY6 += (iDiceHeight / 4);
		}
	}

	// EnemyLine °æ·Î
	{
		ptGameLine1 = { 59, 0 };
		ptGameLine2 = { 59, 558 };
		ptGameLine3 = { 540, 558 };
		ptGameLine4 = { 540, 0 };

	}

	{
		testDice = new Dice();
		if (!testDice->Init())
		{
			return false;
		}

		
	}

	return true;
}

bool GameBoard::Init(int _width, int _height)
{
	return true;
}
void GameBoard::Render(HDC hdc)
{
	// Draw Game Line 
	{
		DrawLine(hdc, ptGameLine1, ptGameLine2, 2, RGB(0, 0, 0));
		DrawLine(hdc, ptGameLine2, ptGameLine3, 2, RGB(0, 0, 0));
		DrawLine(hdc, ptGameLine3, ptGameLine4, 2, RGB(0, 0, 0));

	}

	
	{
		//for (int i = 0; i < GAMEBOARDSIZE; i++)
		//{
		//	DrawObject(hdc, rcTest[i], 1, RGB(125, 125, 125), RECTANGLE);
		//}
	}

	//RGB(125, 125, 125)
	{
		// Level 1 Draw
		//DrawObject(hdc, rcCircle1, 1, RGB(253, 13, 5), ELLIPSE);

		//Level 2 Draw
		//for (int i = 0; i < 2; i++)
		//{
		//	DrawObject(hdc, rcCircle2[i], 1, RGB(253, 13, 5), ELLIPSE);
		//}

		// Level 3 Draw
		//for (int i = 0; i < 3; i++)
		//{
		//	DrawObject(hdc, rcCircle3[i], 1, RGB(253, 13, 5), ELLIPSE);
		//}

		// Level 4 Draw 
		//int iTemp = 0;

		//for (int i = 0; i < 2; i++)
		//{
		//	for (int j = 0; j < 2; j++)
		//	{
		//		DrawObject(hdc, rcCircle4[iTemp], 1, RGB(254, 13, 5), ELLIPSE);
		//		iTemp++;
		//	}
		//}


		// Level 5 Draw
		//int iTemp = 0; 
		//for (int i = 0; i < 5; i++)
		//{
		//	DrawObject(hdc, rcCircle5[i], 1, RGB(255, 13, 5), ELLIPSE);
		//}

		// Level 6 Draw

		for (int i = 0; i < 6; i++)
		{
			DrawObject(hdc, rcCircle6[i], 1, RGB(255, 13, 5), ELLIPSE);
		}

	}

	{
		testDice->Render(hdc);

		for (int i = 0; i < GAMEBOARDSIZE; i++)
		{	
			dice[i]->Render(hdc);
		}
	}

}