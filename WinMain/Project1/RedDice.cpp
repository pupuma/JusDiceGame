#include "Game.h"
#include "RedDice.h"

#include "Bullet.h"


RedDice::RedDice()
{
	diceType = eDiceColor::DICE_RED;
	color = RGB(228, 58, 40);
	isFire = false;
	r = 100;
	fDeltaTime = 0.01f;
	colorKey = 220;
}


RedDice::~RedDice()
{
}

bool RedDice::Init(int _x, int _y, RECT _rcGameBoard)
{
	{
		
		rcGameBoard = _rcGameBoard;
		_image = new Image();

		//_image = IMAGEMANAGER->FindImage(TEXT("TestDice"));
		_image->Init(TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);

		_imageOn = new Image();
		_imageOn->Init(TEXT("../../Resource/BMP/DiceOn.bmp"), 438, 62, 6, 1, true, COLOR_M);

		
		
		//circleImg->SetWidth(r);
		//circleImg->SetHeight(r);
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
		//diceType = _color;
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

void RedDice::Update()
{

	{
		if (rcGameBoard.left >= (ptDiceCenterPos.x - iDiceWidth / 2))
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
			// 적 검사 
			if (GAMESYS->IsEnemyActivate())
			{
				if (!GAMESYS->IsEnemyEmpty())
				{
					if (!isTarget)
					{
						_target = GAMESYS->GetPosEnemy(this);

						isTarget = true;
					}
					else
					{
						_target = GAMESYS->TargetUpdate(_target);
					}
				}

			}



		}

		{
			if (_target.first == -1 || _target.second.x == 0 || _target.second.y == 0)
			{
				bulletList[iDiceIndex]->SetFire(false);
				bulletList[iDiceIndex]->SetCollision(false);
				bulletList[iDiceIndex]->SetFire(false);

				bulletList[iDiceIndex]->ResetPosition();
				isTarget = false;
				return;
			}
		}

		{
			// 총알 발사 
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
				}
			}
		}



		// Bullet Move
		{
			if (!GAMESYS->IsEnemyEmpty())
			{
				if (bulletList[iDiceIndex]->IsFire())
				{
					bulletList[iDiceIndex]->BulletMove(_target.second);
					GAMESYS->SetFire(false);

				}
			}
		}

		{
			GAMESYS->CollisionBullet(this, iDiceIndex, _target);
		}


		// Collision 
		{
			if (bulletList[iDiceIndex]->IsCollision())
			{
				bulletList[iDiceIndex]->SetCollision(false);
				iDiceIndex++;
				if (iDiceIndex >= iLevel)
				{
					iDiceIndex = 0;
				}
				DiceFirePos(GetDiceLevel(), rcDice.left, rcDice.top);



				bulletList[iDiceIndex]->Fire(_target.second);
			}
		}


		{
			fDeltaTime -= TIMEMANAGER->GetElapsedTime();
			if (fDeltaTime <= 0)
			{
				colorKey -= (BYTE)10;

				fDeltaTime = 0.01f;
			}


			if (colorKey <= 0)
			{
				colorKey = 0;
				isFire = false;
				//circleImg->Release();
				//elete circleImg;
			}
		}

	}


	//	

	//	{
	//		if (!GAMESYS->IsEnemyEmpty())
	//		{
	//			if (GAMESYS->IsEnemyActivate())
	//			{

	//				if (!bulletList[0]->IsFire() &&
	//					!bulletList[1]->IsFire() &&
	//					!bulletList[2]->IsFire() &&
	//					!bulletList[3]->IsFire() &&
	//					!bulletList[4]->IsFire() &&
	//					!bulletList[5]->IsFire())
	//				{
	//					if (!bulletList[0]->IsCollision() &&
	//						!bulletList[1]->IsCollision() &&
	//						!bulletList[2]->IsCollision() &&
	//						!bulletList[3]->IsCollision() &&
	//						!bulletList[4]->IsCollision() &&
	//						!bulletList[5]->IsCollision())
	//					{
	//						iDiceIndex = 0;
	//						ptSave = DiceStartFirePos(GetDiceLevel(), rcDice.left, rcDice.top);
	//						bulletList[iDiceIndex]->Fire(rcTarget, ptSave);
	//					}

	//				}



	//				// 발사 이동 
	//				if (bulletList[iDiceIndex]->IsFire())
	//				{
	//					bulletList[iDiceIndex]->BulletMove(_target.second);
	//					//isFire = false;
	//					GAMESYS->SetFire(false);
	//				}

	//				if (bulletList[iDiceIndex]->IsCollision())
	//				{
	//					bulletList[iDiceIndex]->SetCollision(false);
	//					iDiceIndex++;
	//					if (iDiceIndex >= iLevel)
	//					{
	//						iDiceIndex = 0;
	//					}
	//					DiceFirePos(GetDiceLevel(), rcDice.left, rcDice.top);
	//					bulletList[iDiceIndex]->Fire(rcTarget);
	//				}
	//			}
	//		}

	//	}

	//}

	//{
	//	fDeltaTime -= TIMEMANAGER->GetElapsedTime();
	//	if (fDeltaTime <= 0)
	//	{
	//		colorKey -= (BYTE)10;
	//		
	//		fDeltaTime = 0.01f;
	//	}
	//	
	//	
	//	if (colorKey <= 0)
	//	{
	//		colorKey = 0;
	//		isFire = false;
	//		//circleImg->Release();
	//		//elete circleImg;
	//	}
	//}

}

void RedDice::Render(HDC hdc)
{
	if (!isDiceOn)
	{
		_image->FrameRender(hdc, rcDice.left, rcDice.top);
	}
	else
	{
		_imageOn->FrameRender(hdc, rcDice.left, rcDice.top);
	}

	//DrawObject(hdc, rcDice, 1, RGB(125, 125, 3), RECTANGLE);
	LevelDiceRender(hdc);

	//  DrawBullet
	{
		RenderBullet(hdc);
	}

	{
		//CircleRender(hdc);
		
	}

}

void RedDice::CircleRender(HDC hdc)
{
	if (isFire)
	{
		//DrawObject(hdc, rcCircleFire, 1, RGB(200, 58, 40), ELLIPSE);
		circleImg->AlphaRender(hdc, pt.x - r / 2, pt.y - r / 2, colorKey);

	}
}

void RedDice::DiceAbility()
{
	isFire = true;
	GAMESYS->SetFire(isFire);
	GAMESYS->SetCircleFireRadius(r);
	pt = { bulletList[iDiceIndex]->GetBulletCenterX(), bulletList[iDiceIndex]->GetBulletCenterY() };


	circleImg = new Image();
	circleImg->Init(TEXT("../../Resource/BMP/BulletRed.bmp"), r, r, true, COLOR_M);


	colorKey = 220;
	rcCircleFire = RectMakeCenter(bulletList[iDiceIndex]->GetBulletCenterX(), bulletList[iDiceIndex]->GetBulletCenterY(), r, r);
}
