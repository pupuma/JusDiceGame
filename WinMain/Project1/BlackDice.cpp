#include "Game.h"
#include "BlackDice.h"

#include "Bullet.h"
#include "State.h"


BlackDice::BlackDice()
{
	diceType = eDiceColor::DICE_BLACK;
	color = RGB(18, 39, 59);
	sa = eStateAbnormal::SA_DIE;
	iProbability =  DICEMANAGER->GetBlackDiceEffectPower();
	;


}


BlackDice::~BlackDice()
{
}

bool BlackDice::Init(int _x, int _y, RECT _rcGameBoard)
{
	{
		rcGameBoard = _rcGameBoard;
		_image = new Image();

		_image->Init(TEXT("../../Resource/BMP/DiceOff.bmp"), 438, 62, 6, 1, true, COLOR_M);

		_imageOn = new Image();
		_imageOn->Init(TEXT("../../Resource/BMP/DiceOn.bmp"), 438, 62, 6, 1, true, COLOR_M);
	}

	//Bullet Create
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
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
		_image->SetFrameX((diceType));

	}

	// 총알 위치 -> 
	{
		ptDicePos.x = _x - iDiceWidth / 2;
		ptDicePos.y = _y - iDiceHeight / 2;

		DiceLevelBullet(GetDiceLevel(), ptDicePos.x, ptDicePos.y);
	}

	{
		iAttackPoint = DICEMANAGER->GetBlackDiceDamage();
	}

	return true;
}

void BlackDice::Update()
{
	{
		iAttackPoint = DICEMANAGER->GetBlackDiceDamage();
	}

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

		//====================================================================================================
		{
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
					if (bulletList[iLevel - 1]->IsCollision())
					{
						fBulletCoolTIme -= TIMEMANAGER->GetElapsedTime();
						if (fBulletCoolTIme <= 0)
						{
							bulletList[iDiceIndex]->SetCollision(false);
							bulletList[iDiceIndex]->ResetPosition();


							iDiceIndex++;
							if (iDiceIndex >= iLevel)
							{
								iDiceIndex = 0;
							}
							DiceFirePos(GetDiceLevel(), rcDice.left, rcDice.top);
							bulletList[iDiceIndex]->Fire();

							fBulletCoolTIme = 1.0f;
						}
					}
					else
					{
						bulletList[iDiceIndex]->SetCollision(false);
						bulletList[iDiceIndex]->ResetPosition();


						iDiceIndex++;
						if (iDiceIndex >= iLevel)
						{
							iDiceIndex = 0;
						}
						DiceFirePos(GetDiceLevel(), rcDice.left, rcDice.top);
						bulletList[iDiceIndex]->Fire();
					}

				}
			}


		}


	}



}

void BlackDice::DiceAbility()
{
	iProbability = DICEMANAGER->GetBlackDiceEffectPower();
	GAMESYS->SetProbabilitySize(iProbability);
	
}
