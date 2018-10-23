#include "Game.h"
#include "Dice.h"

#include "Bullet.h"

Dice::Dice()
{
	diceType = eDiceColor::DICE_NONE;
	_image = IMAGEMANAGER->FindImage(TEXT("TestDice"));

	iLevel = 6; 
	isClick = false;

	// Test
	targetRect = RectMakeCenter(59, 60, 54, 44);

	fCoolTime = 1.0f;
}


Dice::~Dice()
{
}

bool Dice::Init()
{
	{
		iDiceStartX = 148;
		iDiceStartY = 237;

		iDiceWidth = 73;
		iDiceHeight = 60;

		ptDiceCenterPos.x = iDiceStartX - iDiceWidth / 2;
		ptDiceCenterPos.y = iDiceStartY - iDiceHeight / 2;


		_image = IMAGEMANAGER->AddFrameImage(TEXT("TestDice"), TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);
		_image->SetX(ptDiceCenterPos.x);
		_image->SetY(ptDiceCenterPos.y);

	}
	return true;
}

bool Dice::Init(int _x, int _y)
{
	{
		iDiceWidth = 73;
		iDiceHeight = 60;


		ptDiceCenterPos.x = _x ;
		ptDiceCenterPos.y = _y ;
		
		rcDice = RectMakeCenter(ptDiceCenterPos.x, ptDiceCenterPos.y, iDiceWidth, iDiceHeight);


		_image->SetX(rcDice.left);
		_image->SetY(rcDice.top);
		
		
		// 이미지 색 
		_image->SetFrameX(5);

	}
	
	// 총알 위치 -> 
	{
		ptDicePos.x = _x - iDiceWidth / 2;
		ptDicePos.y = _y - iDiceHeight / 2;

		DiceLevelBullet(GetDiceLevel(), ptDicePos.x, ptDicePos.y);
	}
	return true;
}
bool Dice::Init(int _x, int _y, RECT _rcGameBoard)
{
	{
		rcGameBoard = _rcGameBoard;
	}

	//Bullet Create
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			bullet[i] = new Bullet();
		}

		for (int i = 0; i < MAXBULLET; i++)
		{
			if (!bullet[i]->IsFire())
			{
				bullet[i]->Fire(targetRect);
			}
		}
	}
	// Init
	{
		iDiceWidth = 73;
		iDiceHeight = 60;


		ptDiceCenterPos.x = _x;
		ptDiceCenterPos.y = _y;

		rcDice = RectMakeCenter(ptDiceCenterPos.x, ptDiceCenterPos.y, iDiceWidth, iDiceHeight);


		_image->SetX(rcDice.left);
		_image->SetY(rcDice.top);


		// 이미지 색 
		_image->SetFrameX(5);

	}

	// 총알 위치 -> 
	{
		ptDicePos.x = _x - iDiceWidth / 2;
		ptDicePos.y = _y - iDiceHeight / 2;

		DiceLevelBullet(GetDiceLevel(), ptDicePos.x, ptDicePos.y);
	}
	return true;
}
void Dice::Update()
{
	{
		if (rcGameBoard.left >= (ptDiceCenterPos.x - iDiceWidth/ 2 ))
		{
			ptDiceCenterPos.x = rcGameBoard.left + (iDiceWidth / 2);
		}
		
		if (rcGameBoard.top >= (ptDiceCenterPos.y - iDiceHeight / 2))
		{
			ptDiceCenterPos.y = rcGameBoard.top + (iDiceHeight / 2);

		}
		
		if (rcGameBoard.right <= (ptDiceCenterPos.x + iDiceWidth / 2))
		{
			ptDiceCenterPos.x = rcGameBoard.right - (iDiceWidth / 2);

		}
		
		if (rcGameBoard.bottom <= (ptDiceCenterPos.y + iDiceHeight / 2))
		{
			ptDiceCenterPos.y = rcGameBoard.bottom - (iDiceHeight / 2);

		}



		{
			rcDice = RectMakeCenter(ptDiceCenterPos.x, ptDiceCenterPos.y, iDiceWidth, iDiceHeight);

		}



		
		{
			//DiceLevelBullet(GetDiceLevel(), rcDice.left, rcDice.top);
			DiceLevelBulletUpdate(GetDiceLevel(), rcDice.left, rcDice.top);

			//
			fCoolTime -= TIMEMANAGER->GetElapsedTime();
			if (fCoolTime <= 0)
			{
				
				fCoolTime = 0;
			}


			for (int i = 0; i < MAXBULLET; i++)
			{
				if (bullet[i]->IsFire())
				{
					bullet[i]->BulletMove();
				}
			}
			

			// Collision
			for (int i = 0; i < MAXBULLET; i++)
			{
				if (bullet[i]->IsFire())
				{
					GAMESYS->CollisionBullet((bullet[i]), targetRect);
				}

			}
		}


	}
	

}

void Dice::Render(HDC hdc)
{
	_image->FrameRender(hdc, rcDice.left, rcDice.top);
	//DrawObject(hdc, rcDice, 1, RGB(125, 125, 3), RECTANGLE);
	//LevelDiceRender(hdc);

	for (int i = 0; i < 6; i++)
	{
		DrawObject(hdc, levelPos.rcLevel6[i], 1, RGB(125, 125, 3), ELLIPSE);
	}
	
	//  DrawBullet
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			if (bullet[i]->IsFire())
			{
				bullet[i]->Render(hdc);
			}
		}
	}
}

void Dice::DiceLevelBullet(int _level, int _x ,int _y)
{
	switch (_level)
	{
	case 1:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 2;
		levelPos.iCircleStartY = _y + iDiceHeight / 2;
		levelPos.rcLevel1 = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
		bullet[0]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);

	

	}
		break;
	case 2:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 3;
		levelPos.iCircleStartY = _y + iDiceHeight / 2;

		for (int i = 0; i < 2; i++)
		{
			levelPos.rcLevel2[i] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
			bullet[i]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


			levelPos.iCircleStartX += (iDiceWidth / 3);

		}
	}
		break;
	case 3:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 4;
		levelPos.iCircleStartY = _y + iDiceHeight / 4;

		for (int i = 0; i < 3; i++)
		{
			levelPos.rcLevel3[i] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
			bullet[i]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);



			levelPos.iCircleStartX += iDiceWidth / 4;
			levelPos.iCircleStartY += iDiceHeight / 4;

		}

	}
		break;
	case 4:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 3;
		levelPos.iCircleStartY = _y + iDiceHeight / 3;

		int iTemp = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				levelPos.rcLevel4[iTemp] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
				bullet[iTemp]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


				levelPos.iCircleStartX += iDiceWidth / 3;
				iTemp++;
			}
			levelPos.iCircleStartX = _x + iDiceWidth / 3;
			levelPos.iCircleStartY += iDiceHeight / 3;
		}

	}
		break;
	case 5:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 4;
		levelPos.iCircleStartY = _y + iDiceHeight / 4;

		int iTemp = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				levelPos.rcLevel5[iTemp] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
				bullet[iTemp]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


				levelPos.iCircleStartX += (iDiceWidth / 4 * 2);
				iTemp++;
			}
			levelPos.iCircleStartX = _x + iDiceWidth / 4;
			levelPos.iCircleStartY += (iDiceHeight / 4 * 2);
		}

		levelPos.iCircleStartX = _x + iDiceWidth / 2;
		levelPos.iCircleStartY = _y + iDiceHeight / 2;

		levelPos.rcLevel5[4] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
		bullet[4]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


	}
		break;
	case 6:
	{
		levelPos.iCircleStartX = _x + (iDiceWidth / 6 * 2);
		levelPos.iCircleStartY = _y + iDiceHeight / 4;

		int iTemp  = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				levelPos.rcLevel6[iTemp] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
				bullet[iTemp]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


				levelPos.iCircleStartX += (iDiceWidth / 6 * 2);
				iTemp++;
			}
			levelPos.iCircleStartX = _x + (iDiceWidth / 6 * 2);
			levelPos.iCircleStartY += (iDiceHeight / 4);
		}
	}
		break;
	}
}

void Dice::DiceLevelBulletUpdate(int _level, int _x, int _y)
{
	switch (_level)
	{
	case 1:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 2;
		levelPos.iCircleStartY = _y + iDiceHeight / 2;
		levelPos.rcLevel1 = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
	}
	break;
	case 2:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 3;
		levelPos.iCircleStartY = _y + iDiceHeight / 2;

		for (int i = 0; i < 2; i++)
		{
			levelPos.rcLevel2[i] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);

			levelPos.iCircleStartX += (iDiceWidth / 3);

		}
	}
	break;
	case 3:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 4;
		levelPos.iCircleStartY = _y + iDiceHeight / 4;

		for (int i = 0; i < 3; i++)
		{
			levelPos.rcLevel3[i] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);

			levelPos.iCircleStartX += iDiceWidth / 4;
			levelPos.iCircleStartY += iDiceHeight / 4;

		}

	}
	break;
	case 4:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 3;
		levelPos.iCircleStartY = _y + iDiceHeight / 3;

		int iTemp = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				levelPos.rcLevel4[iTemp] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);

				levelPos.iCircleStartX += iDiceWidth / 3;
				iTemp++;
			}
			levelPos.iCircleStartX = _x + iDiceWidth / 3;
			levelPos.iCircleStartY += iDiceHeight / 3;
		}

	}
	break;
	case 5:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 4;
		levelPos.iCircleStartY = _y + iDiceHeight / 4;

		int iTemp = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				levelPos.rcLevel5[iTemp] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);

				levelPos.iCircleStartX += (iDiceWidth / 4 * 2);
				iTemp++;
			}
			levelPos.iCircleStartX = _x + iDiceWidth / 4;
			levelPos.iCircleStartY += (iDiceHeight / 4 * 2);
		}

		levelPos.iCircleStartX = _x + iDiceWidth / 2;
		levelPos.iCircleStartY = _y + iDiceHeight / 2;

		levelPos.rcLevel5[4] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);


	}
	break;
	case 6:
	{
		levelPos.iCircleStartX = _x + (iDiceWidth / 6 * 2);
		levelPos.iCircleStartY = _y + iDiceHeight / 4;

		int iTemp2 = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				levelPos.rcLevel6[iTemp2] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);

				levelPos.iCircleStartX += (iDiceWidth / 6 * 2);
				iTemp2++;
			}
			levelPos.iCircleStartX = _x + (iDiceWidth / 6 * 2);
			levelPos.iCircleStartY += (iDiceHeight / 4);
		}
	}
	break;

	}
}

void Dice::LevelDiceRender(HDC hdc)
{
	int level = GetDiceLevel();
	switch (level)
	{
	case 1:
	{
		DrawObject(hdc, levelPos.rcLevel1, 1, RGB(125, 125, 3), ELLIPSE);
	}
	break;
	case 2:
	{
		for (int i = 0; i < 2; i++)
		{
			DrawObject(hdc, levelPos.rcLevel2[i], 1, RGB(125, 125, 3), ELLIPSE);
		}
	}
	break;
	case 3:
	{
		for (int i = 0; i < 3; i++)
		{
			DrawObject(hdc, levelPos.rcLevel3[i], 1, RGB(125, 125, 3), ELLIPSE);
		}
	}
	break;
	case 4:
	{
		for (int i = 0; i <4; i++)
		{
			DrawObject(hdc, levelPos.rcLevel4[i], 1, RGB(125, 125, 3), ELLIPSE);
		}
	}
	break;
	case 5:
	{
		for (int i = 0; i < 5; i++)
		{
			DrawObject(hdc, levelPos.rcLevel5[i], 1, RGB(125, 125, 3), ELLIPSE);
		}
	}
	break;
	case 6:
	{
		for (int i = 0; i < 6; i++)
		{
			DrawObject(hdc, levelPos.rcLevel6[i], 1, RGB(125, 125, 3), ELLIPSE);
		}
	}
	break;
	}
}
