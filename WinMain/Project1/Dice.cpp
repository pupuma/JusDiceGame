#include "Game.h"

#include "Dice.h"

#include "Bullet.h"
#include "State.h"

Dice::Dice()
{
	diceType = eDiceColor::DICE_NONE;
	//_image = IMAGEMANAGER->FindImage(TEXT("TestDice"));

	iLevel =1; 
	isClick = false;
	iAttackPoint = 5;
	// Test
	//targetRect = RectMakeCenter(59, 60, 54, 44);

	fCoolTime = 3.0f;
	iIndex = 0;
	stateType = eStateType::STATE_NONE;
	iDiceIndex = 0;
	color = RGB(0, 0, 0);

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
		stateType = eStateType::STATE_IDLE;
		_image = new Image();

		//_image = IMAGEMANAGER->FindImage(TEXT("TestDice"));
		_image->Init(TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);
	}

	//Bullet Create
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			//bullet[i] = new Bullet();
			Bullet* bullet = new Bullet(color);
			bulletList.push_back(bullet);
		}

		//for (int i = 0; i < MAXBULLET; i++)
		//{
		//	bulletList[i]->Fire(targetRect);
		//}
		
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
		_image->SetFrameX((int)diceType);

	}

	// 총알 위치 -> 
	{
		ptDicePos.x = _x - iDiceWidth / 2;
		ptDicePos.y = _y - iDiceHeight / 2;

		DiceLevelBullet(GetDiceLevel(), ptDicePos.x, ptDicePos.y);
	}


	//Target
	
	return true;
}
bool Dice::Init(int _x, int _y, RECT _rcGameBoard, eDiceColor _color)
{

	{
		rcGameBoard = _rcGameBoard;
		stateType = eStateType::STATE_IDLE;
		_image = new Image();
		
		//_image = IMAGEMANAGER->FindImage(TEXT("TestDice"));
		_image->Init(TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);
	}

	//Bullet Create
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			//bullet[i] = new Bullet();
			Bullet* bullet = new Bullet(color);
			bulletList.push_back(bullet);
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
		diceType = _color;
		_image->SetFrameX((diceType));

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
	//state->Update();

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
			DiceLevelBulletUpdate(GetDiceLevel(), rcDice.left, rcDice.top);

		}

		{
			if (GAMESYS->IsEnemyActivate())
			{
				if (!GAMESYS->IsEnemyEmpty())
				{
					rcTarget = GAMESYS->GetRectEnemy();
				}

			}
		}

		{
			if (!GAMESYS->IsEnemyEmpty())
			{
				if (GAMESYS->IsEnemyActivate())
				{

					if (!bulletList[0]->IsFire() &&
						!bulletList[1]->IsFire() &&
						!bulletList[2]->IsFire() &&
						!bulletList[3]->IsFire() &&
						!bulletList[4]->IsFire() &&
						!bulletList[5]->IsFire())
					{
						if (!bulletList[0]->IsCollision() &&
							!bulletList[1]->IsCollision() &&
							!bulletList[2]->IsCollision() &&
							!bulletList[3]->IsCollision() &&
							!bulletList[4]->IsCollision() &&
							!bulletList[5]->IsCollision())
						{
							iDiceIndex = 0;
							ptSave = DiceStartFirePos(GetDiceLevel(), rcDice.left, rcDice.top);
							bulletList[iDiceIndex]->Fire(rcTarget, ptSave);
						}

					}



					// 발사 이동 
					if (bulletList[iDiceIndex]->IsFire())
					{
						bulletList[iDiceIndex]->BulletMove(rcTarget);
					}

					if (bulletList[iDiceIndex]->IsCollision())
					{
						bulletList[iDiceIndex]->SetCollision(false);
						iDiceIndex++;
						if (iDiceIndex >= iLevel)
						{
							iDiceIndex = 0;
						}
						DiceFirePos(GetDiceLevel(), rcDice.left, rcDice.top);
						bulletList[iDiceIndex]->Fire(rcTarget);
					}
				}
			}

		}
			
	}


}

void Dice::Render(HDC hdc)
{
	_image->FrameRender(hdc, rcDice.left, rcDice.top);
	//DrawObject(hdc, rcDice, 1, RGB(125, 125, 3), RECTANGLE);
	LevelDiceRender(hdc);


	//  DrawBullet
	{
		RenderBullet(hdc);
		//for (int i = 0; i < MAXBULLET; i++)
		//{
		//	if (bulletList[i]->IsFire())
		//	{
		//		bulletList[i]->Render(hdc);
		//	}
		//}
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
		bulletList[0]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


	}
		break;
	case 2:
	{
		levelPos.iCircleStartX = _x + iDiceWidth / 3;
		levelPos.iCircleStartY = _y + iDiceHeight / 2;

		for (int i = 0; i < 2; i++)
		{
			levelPos.rcLevel2[i] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
			bulletList[i]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);



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
			bulletList[i]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);



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
				bulletList[iTemp]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);

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
				bulletList[iTemp]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


				levelPos.iCircleStartX += (iDiceWidth / 4 * 2);
				iTemp++;
			}
			levelPos.iCircleStartX = _x + iDiceWidth / 4;
			levelPos.iCircleStartY += (iDiceHeight / 4 * 2);
		}

		levelPos.iCircleStartX = _x + iDiceWidth / 2;
		levelPos.iCircleStartY = _y + iDiceHeight / 2;

		levelPos.rcLevel5[4] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);
		bulletList[4]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


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
				bulletList[iTemp]->Init(levelPos.iCircleStartX, levelPos.iCircleStartY);


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

		int iTemp = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				levelPos.rcLevel6[iTemp] = RectMakeCenter(levelPos.iCircleStartX, levelPos.iCircleStartY, 14, 12);


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

void Dice::LevelDiceRender(HDC hdc)
{
	int level = GetDiceLevel();
	switch (level)
	{
	case 1:
	{
		DrawObject(hdc, levelPos.rcLevel1, 1,color, ELLIPSE);
	}
	break;
	case 2:
	{
		for (int i = 0; i < 2; i++)
		{
			DrawObject(hdc, levelPos.rcLevel2[i], 1, color, ELLIPSE);
		}
	}
	break;
	case 3:
	{
		for (int i = 0; i < 3; i++)
		{
			DrawObject(hdc, levelPos.rcLevel3[i], 1, color, ELLIPSE);
		}
	}
	break;
	case 4:
	{
		for (int i = 0; i <4; i++)
		{
			DrawObject(hdc, levelPos.rcLevel4[i], 1, color, ELLIPSE);
		}
	}
	break;
	case 5:
	{
		for (int i = 0; i < 5; i++)
		{
			DrawObject(hdc, levelPos.rcLevel5[i], 1, color, ELLIPSE);
		}
	}
	break;
	case 6:
	{
		for (int i = 0; i < 6; i++)
		{
			DrawObject(hdc, levelPos.rcLevel6[i], 1, color, ELLIPSE);
		}
	}
	break;
	}
}

POINT Dice::DiceStartFirePos(int _level, int _x, int _y)
{
	POINT pt;

	switch (_level)
	{
	case 1:
	{
		pt.x = _x + iDiceWidth / 2;
		pt.y = _y + iDiceHeight / 2;
	}

	break;
	case 2:
	{
		pt.x = _x + iDiceWidth / 3;
		pt.y = _y + iDiceHeight / 2;
	
	}
	break;
	case 3:
	{
		pt.x = _x + iDiceWidth / 4;
		pt.y = _y + iDiceHeight / 4;

	}
	break;
	case 4:
	{
		pt.x = _x + iDiceWidth / 3;
		pt.y = _y + iDiceHeight / 3;
	}
	break;
	case 5:
	{
		pt.x = _x + iDiceWidth / 4;
		pt.y = _y + iDiceHeight / 4;


	}
	break;
	case 6:
	{
		pt.x = _x + (iDiceWidth / 6 * 2);
		pt.y = _y + iDiceHeight / 4;
		
	}
	break;

	}

	return pt;
}

void Dice::DiceFirePos(int _level, int _x, int _y)
{

	switch (_level)
	{
	case 1:
	{
		ptSave.x = _x + iDiceWidth / 2;
		ptSave.y = _y + iDiceHeight / 2;

		if (!bulletList[0]->IsFire())
		{
			
			bulletList[0]->SetPosition(ptSave);
			bulletList[0]->SetStartPosition(ptSave);
		}

		
	}

	break;
	case 2:
	{
		ptSave.x = _x + iDiceWidth / 3;
		ptSave.y = _y + iDiceHeight / 2;

		for (int i = 0; i < 2; i++)
		{
			if (!bulletList[i]->IsFire())
			{

				bulletList[i]->SetPosition(ptSave);
				bulletList[i]->SetStartPosition(ptSave);

				ptSave.x += (iDiceWidth / 3);

			}

		}
	}
	break;
	case 3:
	{
		ptSave.x = _x + iDiceWidth / 4;
		ptSave.y = _y + iDiceHeight / 4;

		for (int i = 0; i < 3; i++)
		{
			if (!bulletList[i]->IsFire())
			{
				bulletList[i]->SetPosition(ptSave);
				bulletList[i]->SetStartPosition(ptSave);


			}
			ptSave.x += iDiceWidth / 4;
			ptSave.y += iDiceHeight / 4;

		}

	}
	break;
	case 4:
	{
		ptSave.x = _x + iDiceWidth / 3;
		ptSave.y = _y + iDiceHeight / 3;

		int iTemp = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (!bulletList[iTemp]->IsFire())
				{
					bulletList[iTemp]->SetPosition(ptSave);
					bulletList[iTemp]->SetStartPosition(ptSave);


				}

				ptSave.x += iDiceWidth / 3;
				iTemp++;
			}
			ptSave.x = _x + iDiceWidth / 3;
			ptSave.y += iDiceHeight / 3;
		}

	}
	break;
	case 5:
	{
		ptSave.x = _x + iDiceWidth / 4;
		ptSave.y = _y + iDiceHeight / 4;

		int iTemp = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (!bulletList[iTemp]->IsFire())
				{
					bulletList[iTemp]->SetPosition(ptSave);
					bulletList[iTemp]->SetStartPosition(ptSave);


				}
				ptSave.x += (iDiceWidth / 4 * 2);
				iTemp++;
			}
			ptSave.x = _x + iDiceWidth / 4;
			ptSave.y += (iDiceHeight / 4 * 2);
		}

		ptSave.x = _x + iDiceWidth / 2;
		ptSave.y = _y + iDiceHeight / 2;

		if (!bulletList[4]->IsFire())
		{
			bulletList[4]->SetPosition(ptSave);
			bulletList[4]->SetStartPosition(ptSave);

		}

	}
	break;
	case 6:
	{
		ptSave.x = _x + (iDiceWidth / 6 * 2);
		ptSave.y = _y + iDiceHeight / 4;

		int iTemp = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (!bulletList[iTemp]->IsFire())
				{
					bulletList[iTemp]->SetPosition(ptSave); 
					bulletList[iTemp]->SetStartPosition(ptSave);

					
				}
				ptSave.x += (iDiceWidth / 6 * 2);
				iTemp++;
			}
			ptSave.x = _x + (iDiceWidth / 6 * 2);
			ptSave.y += (iDiceHeight / 4);
		}
	}
	break;

	}
}

void Dice::SetColor(eDiceColor _color)
{
	 diceType = _color; 
	 _image->SetFrameX(diceType);
}

void Dice::ResetBullet()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		bulletList[i]->SetFire(false);
	}
}

void Dice::RenderBullet(HDC hdc)
{
	for (int i = 0; i < MAXBULLET; i++)
		{
			if (bulletList[i]->IsFire())
			{
				bulletList[i]->Render(hdc);
			}
		}
}

void Dice::DiceAbility()
{
}

