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
	fClickedTime = 1.0f;
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
void GameBoard::Release()
{
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
				fClickedTime = 1.0f;

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
				fClickedTime -= TIMEMANAGER->GetElapsedTime();

				

				for (it = diceList.begin(); it != diceList.end(); it++)
				{
					if (iSelectNumber == it->first)
					{
						(*it).second->SetDicePosition(_ptMouse);

						if (fClickedTime <= 0.0f)
						{
							GAMESYS->SetDiceListOn(diceList, iSelectNumber);
						}
						break;
					}
				}
			}
		}

		if (!diceList.empty())
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				//fClickedTime = 1.0f;

				for (it = diceList.begin(); it != diceList.end(); it++)
				{
					if (PtInRect(&(*it).second->GetRectDice(), _ptMouse) && (*it).second->IsClick() == false)
					{
						if (it->first != iSelectNumber)
						{
							iDestSelectNumber = it->first;
							if (-1 != iSelectNumber)
							{
								GAMESYS->SetDiceListOn(diceList, iSelectNumber);
							}

			
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
				GAMESYS->SetDiceListOff();

				for (it = diceList.begin(); it != diceList.end(); it++)
				{
					if (it->first == iSelectNumber)
					{
						if (!isClicked)
						{
							(*it).second->SetClick(false);
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
	
	

}
void GameBoard::Render(HDC hdc)
{
	//RECT GameBoadDraw
	{
	//	TIMEMANAGER->Render(hdc);
	}
	

	{



		if (!diceList.empty())
		{
			for (it = diceList.begin(); it != diceList.end(); it++)
			{
				(*it).second->Render(hdc);
				index = it->first;

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

	}

	

}

void GameBoard::FullAttactRender(HDC hdc)
{
	if (!diceList.empty())
	{
		for (it = diceList.begin(); it != diceList.end(); it++)
		{
			(*it).second->CircleRender(hdc);
		}
	}
}
