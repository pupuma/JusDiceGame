#include "Game.h"

#include "GameBoard.h"
#include "Dice.h"
#include "Bullet.h"


GameBoard::GameBoard()
{
	iIndex = 0;
	isClicked = false;

	iDiceStartX = 148;
	iDiceStartY = 237;

	iDiceWidth = 73;
	iDiceHeight = 60;
	iSelectNumber = -1;
	index = -1;
	iDestSelectNumber = -1;
}


GameBoard::~GameBoard()
{
}

bool GameBoard::Init()
{
	// GameBoardRect
	{
		int iGameBoardX = 105;
		int iGameBoardY = 204;

		int iGameBoardWidth = 387;
		int iGameBoardHeight = 317;

		int iGameBoardCenterX = iGameBoardX + iGameBoardWidth / 2;
		int iGameBoardCenterY = iGameBoardY + iGameBoardHeight / 2;
		rcGameBoard = RectMakeCenter(iGameBoardCenterX, iGameBoardCenterY, iGameBoardWidth, iGameBoardHeight);
		GAMESYS->SetRectGameBoard(rcGameBoard);
	}

	// GameBoard Dice Position Info  
	//{
	//	//iDiceStartX = 113;
	//	//iDiceStartY = 207;
	//	
	//	iDiceStartX = 148;
	//	iDiceStartY = 237;

	//	iDiceWidth = 73;
	//	iDiceHeight = 60;
	//	
	//	int x = iDiceStartX;
	//	int y = iDiceStartY;

	//	int temp = 0;
	//	//for (int i = 0; i < GAMEBOARDX; i++)
	//	//{
	//	//	for (int j = 0; j < GAMEBOARDY; j++)
	//	//	{
	//	//		rcTest[temp] = RectMakeCenter(x, y, iDiceWidth, iDiceHeight);
	//	//		dice[temp] = new Dice();
	//	//		if (!(dice[temp]->Init(x, y,rcGameBoard)))
	//	//		{
	//	//			return false;
	//	//		}
	//	//		x = x + iDiceWidth + 2;

	//	//		temp++;
	//	//	}
	//	//	x = iDiceStartX;
	//	//	y = y + iDiceHeight + 2 ;
	//	//}

	//	for (int i = 0; i < GAMEBOARDX; i++)
	//	{
	//		for (int j = 0; j < GAMEBOARDY; j++)
	//		{
	//			//rcTest[temp] = RectMakeCenter(x, y, iDiceWidth, iDiceHeight);
	//			//dice[temp] = new Dice();
	//			Dice* dice = new Dice();

	//			if (!(dice->Init(x, y, rcGameBoard)))
	//			{
	//				return false;
	//			}
	//			diceList.push_back(dice);

	//			x = x + iDiceWidth + 2;

	//			temp++;
	//		}
	//		x = iDiceStartX;
	//		y = y + iDiceHeight + 2;
	//	}


	//}



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

		iTemp = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				rcCircle6[iTemp] = RectMakeCenter(circleX6, circleY6, 14, 12);

				circleX6 += (iDiceWidth / 6  * 2 );
				iTemp++;
			}
			circleX6 = startX + (iDiceWidth / 6 * 2);
			circleY6 += (iDiceHeight / 4);
		}


	}

	// EnemyLine °æ·Î
	

	// Save DIce Position 


	return true;
}

bool GameBoard::Init(int _width, int _height)
{
	return true;
}
void GameBoard::Update()
{
	// GameSystem Init(); 
	{
		diceList = GAMESYS->GetDiceList();
		
	}


	// DiceSelect Contrl
	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &_ptMouse);

		if (!diceList.empty())
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				for (it = diceList.begin(); it != diceList.end(); it++)
				{
					if (PtInRect(&(*it).second->GetRectDice(), _ptMouse) && (*it).second->IsClick() == false)
					{
						iSelectNumber = it->first;
						_ptSave = (*it).second->GetDiceCenterPosition();
						(*it).second->SetClick(true);
						isClicked = true;

						break;
					}
				}
			}

		}	


	}

	{
		GetCursorPos(&_ptMouse);
		ScreenToClient(_hWnd, &_ptMouse);

		if (!diceList.empty())
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				for (it = diceList.begin(); it != diceList.end(); it++)
				{
					if (iSelectNumber == it->first)
					{
						(*it).second->SetDicePosition(_ptMouse);
						break;
					}
				}
			}
		}

		if (!diceList.empty())
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				for (it = diceList.begin(); it != diceList.end(); it++)
				{
					if (PtInRect(&(*it).second->GetRectDice(), _ptMouse) && (*it).second->IsClick() == false)
					{
						if (it->first != iSelectNumber)
						{
							iDestSelectNumber = it->first;
							//(*it).second->SetDicePosition(_ptMouse);
							//diceList[iIndex]->SetDicePosition(_ptMouse);
							break;
						}
					}
					else
					{
						iDestSelectNumber = -1;

					}
				}
			}
		}

	}

	{
		if (!diceList.empty())
		{
			if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
			{
				for (it = diceList.begin(); it != diceList.end(); it++)
				{
					if (it->first == iSelectNumber)
					{
						if (!isClicked)
						{
							(*it).second->SetClick(false);
							//dice[iIndex]->SetDicePosition(_);
							iDestSelectNumber = -1;
						}
						else
						{

							(*it).second->SetClick(false);
							(*it).second->SetDicePosition(_ptSave);
							if ((*it).second->GetDiceLevel() < 6)
							{
								if (iDestSelectNumber != -1 && iSelectNumber != -1)
								{
									if (GAMESYS->CompareDice(diceList, iSelectNumber, iDestSelectNumber))
									{
										diceList = GAMESYS->ConvergeDice(diceList, iSelectNumber, iDestSelectNumber, (*it).second->GetDiceLevel());
									}
									iDestSelectNumber = -1;

								}
							}
							
					
						}
						iSelectNumber = -1;
						iDestSelectNumber = -1;

						break;
					}
				}
				
			}
		}
	}



	{
		if (!diceList.empty())
		{
			for (it = diceList.begin(); it != diceList.end(); it++)
			{
				(*it).second->Update();
			}
		}
		
	}

	{
		GAMESYS->SetDiceList(diceList);

	}
	
	//{
	//	GetCursorPos(&_ptMouse);
	//	ScreenToClient(_hWnd, &_ptMouse);



	//	for (int i = 0; i < GAMEBOARDSIZE; i++)
	//	{
	//		if (PtInRect(&diceList[i]->GetRectDice(), _ptMouse))
	//		{
	//			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON) && diceList[i]->IsClick() == false)
	//			{

	//				iIndex = i;
	//				_ptSave = diceList[iIndex]->GetDiceCenterPosition();

	//				diceList[iIndex]->SetClick(true);
	//				isClicked = true;
	//				break;

	//			}
	//		}
	//	}



	//	GetCursorPos(&_ptMouse);
	//	ScreenToClient(_hWnd, &_ptMouse);


	//	if (PtInRect(&diceList[iIndex]->GetRectDice(), _ptMouse))
	//	{
	//		if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	//		{


	//			//ptDiceCenterPos.x += (_ptMouse.x - _ptSave.x);
	//			//ptDiceCenterPos.y += (_ptMouse.y - _ptSave.y);
	//			if (diceList[iIndex]->IsClick() == true)
	//			{

	//				//ptDiceCenterPos.x = _ptMouse.x;
	//				//ptDiceCenterPos.y = _ptMouse.y;
	//				diceList[iIndex]->SetDicePosition(_ptMouse);
	//			}

	//		}

	//	}


	//	if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	//	{
	//		if (!isClicked)
	//		{
	//			diceList[iIndex]->SetClick(false);
	//			//dice[iIndex]->SetDicePosition(_);
	//		}
	//		else
	//		{
	//			diceList[iIndex]->SetClick(false);
	//			diceList[iIndex]->SetDicePosition(_ptSave);
	//		}



	//	}

	//}
	//


	//for (int i = 0; i < GAMEBOARDSIZE; i++)
	//{
	//	diceList[i]->Update();
	//}

	//dice[0]->Update();
	//dice[5]->Update();
	//dice[10]->Update();
	//dice[15]->Update();
	
	// GAMESYS
	{
	//	GAMESYS->GetDiceList(diceList);
	}


}
void GameBoard::Render(HDC hdc)
{
	//RECT GameBoadDraw
	{
		//DrawObject(hdc, rcGameBoard, 1, RGB(124, 123, 133), RECTANGLE);
		TIMEMANAGER->Render(hdc);
	}
	

	{

		//for (int i = 0; i < GAMEBOARDSIZE; i++)
		//{	
		//	if (i != iIndex)
		//	{
		//		diceList[i]->Render(hdc);
		//	}
		//}
		//diceList[iIndex]->Render(hdc);

		if (!diceList.empty())
		{
			for (it = diceList.begin(); it != diceList.end(); it++)
			{
				(*it).second->Render(hdc);
				index = it->first;

				//_stprintf(str, TEXT("Test : %5d"), index);
				//TextOut(hdc, 10, 0, str, _tcslen(str));
			}

			// Select
			for (it = diceList.begin(); it != diceList.end(); it++)
			{
				if (it->first == iSelectNumber)
				{

					(*it).second->Render(hdc);
					break;
				}
			}
			//DrawObject(hdc, (*it_Select).second->GetRectDice(), 1, RGB(255, 0, 0), RECTANGLE);

		}

		
	}

	{
		if (!diceList.empty())
		{
			for (it = diceList.begin(); it != diceList.end(); it++)
			{
				(*it).second->RenderBullet(hdc);
			}
		}
	}
#if defined(_DEBUG_TEST)
	{

		_stprintf(str, TEXT("Add : %5d"), index);
		TextOut(hdc, 10, 0, str, _tcslen(str));

		TCHAR str2[256];
		_stprintf(str2, TEXT("dest : %5d"), iDestSelectNumber);
		TextOut(hdc, 10, 10, str2, _tcslen(str2));

		TCHAR str3[256];
		_stprintf(str3, TEXT("Select : %5d"), iSelectNumber);
		TextOut(hdc, 10, 20, str3, _tcslen(str3));

	}
#endif
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

		//for (int i = 0; i < 6; i++)
		//{
		//	DrawObject(hdc, rcCircle6[i], 1, RGB(255, 13, 5), ELLIPSE);
		//}

	}

	{
		//testDice->Render(hdc);

		//for (int i = 0; i < GAMEBOARDSIZE; i++)
		//{	
		//	if (i != iIndex)
		//	{
		//		diceList[i]->Render(hdc);
		//	}
		//}
		//diceList[iIndex]->Render(hdc);

		//dice[0]->Render(hdc);
		//dice[5]->Render(hdc);
		//dice[10]->Render(hdc);
		//dice[15]->Render(hdc);

	}

}