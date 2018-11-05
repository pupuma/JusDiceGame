#include "Game.h"
#include "Enemy.h"

#include "Animation.h"



Enemy::Enemy()
{
	test = new TimeCheck(TEXT("Enemy"));
	// hp
	iHp = 0;
	iSlowCount = 0;
	poisonNumber = 0;
	// position 
	iStartX = 59;
	iStartY = 60;
	
	// size
	iNomalWidth = 54;
	iNomalHeight = 44;
	iBossWidth = 80;
	iBossHeight = 66;
	// 
	iColorR = 255;
	iColorG = 0;
	iColorB = 5;

	fMoveSpeed = 2.f;
	fMaxMoveSpeed = 2.f;
	fAngle = PI;
	sa = SA_NONE;

	fFreezTime = 3.0f;
	fPoisonTime = 3.0f;

	fFreezDeltaTime = 1.0f;
	fPoisonDeltaTime = 0.5f;
	isPoison = false;
	isSlow = false;
	isLive = true;
	isDieState = false;
	activate = false;
	isDead = false;
}


Enemy::~Enemy()
{
	delete test;
}

bool Enemy::Init()
{
	//
	{
		enemyType = (eEnemyType)GAMESYS->EnemyType();
	}

	{
		rcEnemy = RectMakeCenter(iStartX, iStartY, iNomalWidth, iNomalHeight);
	}
	return true;
}

bool Enemy::Init(int _y, eEnemyType _type)
{
	//
	{
		//enemyType = (eEnemyType)GAMESYS->EnemyType();
		if (_type == eEnemyType::ENEMY_NONE)
		{
			iWidth= iNomalWidth;
			iHeight= iNomalHeight;

		}
		else if (_type == eEnemyType::ENEMY_BOSS)
		{
			iWidth = iBossWidth;
			iHeight = iBossHeight;
		}
	}

	{
		iStartY += _y;
		rcEnemy = RectMakeCenter(iStartX, iStartY, iWidth, iHeight);
	}


	{
		slowImg1 = new Image();
		assert(slowImg1 != NULL);
		if (_type == eEnemyType::ENEMY_NONE)
		{
			slowImg1->Init(TEXT("../../Resource/BMP/SlowEffect1.bmp"), 600, 70, 10, 1, true, COLOR_M);
		}
		else if (_type == eEnemyType::ENEMY_BOSS)
		{
			slowImg1->Init(TEXT("../../Resource/BMP/SlowEffect1.bmp"), 850, 90 , 10, 1, true, COLOR_M);
		}

		slowImg1->SetX(iStartX - (iWidth / 2) );
		slowImg1->SetY(iStartY - (iHeight / 2) - 10);
		slowAni1 = new Animation();
		slowAni1->Init(slowImg1);
		slowAni1->SetFPS(1);
		slowAni1->SetDefPlayFrame(false, true);

		slowImg2 = new Image();
		assert(slowImg2 != NULL);

		if (_type == eEnemyType::ENEMY_NONE)
		{
			slowImg2->Init(TEXT("../../Resource/BMP/SlowEffect2.bmp"), 600, 70, 10, 1, true, COLOR_M);
		}
		else if (_type == eEnemyType::ENEMY_BOSS)
		{
			slowImg2->Init(TEXT("../../Resource/BMP/SlowEffect2.bmp"), 850, 90, 10, 1, true, COLOR_M);
		}
		slowImg2->SetX(iStartX -( iWidth / 2));
		slowImg2->SetY(iStartY - (iHeight / 2));
		slowAni2 = new Animation();
		slowAni2->Init(slowImg2);
		slowAni2->SetFPS(1);
		slowAni2->SetDefPlayFrame(false, true);

		slowImg3 = new Image();
		assert(slowImg3 != NULL);

		if (_type == eEnemyType::ENEMY_NONE)
		{
			slowImg3->Init(TEXT("../../Resource/BMP/SlowEffect3.bmp"), 600, 70, 10, 1, true, COLOR_M);
		}
		else if (_type == eEnemyType::ENEMY_BOSS)
		{
			slowImg3->Init(TEXT("../../Resource/BMP/SlowEffect3.bmp"), 850, 90, 10, 1, true, COLOR_M);
		}
		slowImg3->SetX(iStartX - (iWidth / 2));
		slowImg3->SetY(iStartY - (iHeight / 2));
		slowAni3 = new Animation();
		slowAni3->Init(slowImg3);
		slowAni3->SetFPS(1);
		slowAni3->SetDefPlayFrame(false, true);

		slowList.push_back(slowImg1);
		slowList.push_back(slowImg2);
		slowList.push_back(slowImg3);


		
	}

	{
		poisonImg1 = new Image();
		assert(poisonImg1 != NULL);
		if (_type == eEnemyType::ENEMY_NONE)
		{
			poisonImg1->Init(TEXT("../../Resource/BMP/Poison1.bmp"), 270, 50, 5, 1, true, COLOR_M);
		}
		else if (_type == eEnemyType::ENEMY_BOSS)
		{
			poisonImg1->Init(TEXT("../../Resource/BMP/Poison1.bmp"), 450, 90, 5, 1, true, COLOR_M);
		}

		poisonImg1->SetX(iStartX - (iWidth / 2));
		poisonImg1->SetY(iStartY - (iHeight / 2) - 10);
		poisonAni1 = new Animation();
		poisonAni1->Init(poisonImg1);
		poisonAni1->SetFPS(1);
		poisonAni1->SetDefPlayFrame(false, true);

		poisonImg2 = new Image();
		assert(poisonImg2 != NULL);

		if (_type == eEnemyType::ENEMY_NONE)
		{
			poisonImg2->Init(TEXT("../../Resource/BMP/Poison2.bmp"), 270, 50, 5, 1, true, COLOR_M);
		}
		else if (_type == eEnemyType::ENEMY_BOSS)
		{
			poisonImg2->Init(TEXT("../../Resource/BMP/Poison2.bmp"), 450, 90, 5, 1, true, COLOR_M);
		}
		poisonImg2->SetX(iStartX - (iWidth / 2));
		poisonImg2->SetY(iStartY - (iHeight / 2));
		poisonAni2 = new Animation();
		poisonAni2->Init(poisonImg2);
		poisonAni2->SetFPS(1);
		poisonAni2->SetDefPlayFrame(false, true);

		poisonImg3 = new Image();
		assert(poisonImg3 != NULL);

		if (_type == eEnemyType::ENEMY_NONE)
		{
			poisonImg3->Init(TEXT("../../Resource/BMP/Poison3.bmp"), 270, 50, 5, 1, true, COLOR_M);
		}
		else if (_type == eEnemyType::ENEMY_BOSS)
		{
			poisonImg3->Init(TEXT("../../Resource/BMP/Poison3.bmp"), 450, 90, 5, 1, true, COLOR_M);
		}
		poisonImg3->SetX(iStartX - (iWidth / 2));
		poisonImg3->SetY(iStartY - (iHeight / 2));
		poisonAni3 = new Animation();
		poisonAni3->Init(poisonImg3);
		poisonAni3->SetFPS(1);
		poisonAni3->SetDefPlayFrame(false, true);

		poisonList.push_back(poisonImg1);
		poisonList.push_back(poisonImg2);
		poisonList.push_back(poisonImg3);


	}

	{
		ptDestPos1 = GAMESYS->GetGameLine()[1];
		ptDestPos2 = GAMESYS->GetGameLine()[2];
		ptDestPos3 = GAMESYS->GetGameLine()[3];

		ptCurrentPos = ptDestPos1;
		isLive = true;
	}
	return true;
}

void Enemy::Release()
{
	for (int i = 0; i < 3; i++)
	{
		SAFE_DELETE(slowList[i]);
		//slowList.pop_back();
	}
	slowList.clear();
	for (int i = 0; i < 3; i++)
	{
		SAFE_DELETE(poisonList[i]);
		//poisonList.pop_back();
	}
	poisonList.clear();


	SAFE_DELETE(slowAni1);
	SAFE_DELETE(slowAni2);
	SAFE_DELETE(slowAni3);

	SAFE_DELETE(poisonAni1);
	SAFE_DELETE(poisonAni2);
	SAFE_DELETE(poisonAni3);



}

void Enemy::Update()
{
	
	{
		EnemyAI();
	}

}

void Enemy::Render(HDC hdc)
{
	if (activate)
	{
		DrawObject(hdc, rcEnemy, 1, RGB(iColorR, iColorG, iColorB), ROUNDRECT);
	}

	if (isSlow)
	{
		if (iSlowCount >= 50)
		{
			slowList[2]->AniRender(hdc, iStartX - (iWidth / 2) -2, iStartY - (iHeight / 2) - 8, slowAni3);
		}
		else if (iSlowCount < 50 && iSlowCount >= 30)
		{
			slowList[1]->AniRender(hdc, iStartX - (iWidth / 2) - 2, iStartY - (iHeight / 2) - 8, slowAni2);

		}
		else
		{
			slowList[0]->AniRender(hdc, iStartX - (iWidth / 2) - 2, iStartY - (iHeight / 2) - 8, slowAni1);
		}
	}

	if (isPoison)
	{
		if (poisonNumber == 1)
		{
			poisonList[2]->AniRender(hdc, iStartX - (iWidth / 2) - 2, iStartY - (iHeight / 2) - 8, poisonAni3);
		}
		else if (poisonNumber == 2)
		{
			poisonList[1]->AniRender(hdc, iStartX - (iWidth / 2) - 2, iStartY - (iHeight / 2) - 8, poisonAni2);
		}
		else
		{
			poisonList[0]->AniRender(hdc, iStartX - (iWidth / 2) - 2, iStartY - (iHeight / 2) - 8, poisonAni1);
		}
	}

	
	DrawFont(hdc);
}

void Enemy::EnemyAI()
{
	//
	

	//
	{
		//iStartY++;
		//rcEnemy = RectMakeCenter(iStartX, iStartY, iNomalWidth, iNomalHeight);

		if (ptDestPos1.y <= iStartY)
		{
			ptCurrentPos = ptDestPos2;
		}
		if (ptDestPos2.x <= iStartX)
		{
			ptCurrentPos = ptDestPos3;
		}
		float fPosX = static_cast<float>(iStartX);
		float fPosY = static_cast<float>(iStartY);

		fAngle = UTIL::GetAngle(fPosX, fPosY, ptCurrentPos.x, ptCurrentPos.y);

		// State Abnormal Effect 
		StateAbnormalEffect(iStartX, iStartY);
		
		multiSpeed = GAMESYS->GetMultiSpeed();
		iStartX += cosf(fAngle) * fMoveSpeed * multiSpeed;
		iStartY += -sinf(fAngle) * fMoveSpeed * multiSpeed;

		if ((iStartY + iHeight /2  >= 0))
		{
			//
			SetActivate(true);
			GAMESYS->SetEnemyActivate(true);
		}

		if ((iStartX == ptDestPos3.x) && (iStartY - iHeight / 2 <= 0))
		{
			GAMESYS->SetGameState(GAMESTATE_DIE);
		}

		{
			if (isSlow)
			{
				if (iSlowCount >= 50)
				{
					slowList[2]->SetX(iStartX - (iWidth / 2));
					slowList[2]->SetY(iStartY - (iHeight / 2));
					slowAni3->Start();
					slowAni3->FrameUpdate(TIMEMANAGER->GetElapsedTime() * multiSpeed);

				}
				else if (iSlowCount < 50 && iSlowCount >= 30)
				{
					slowList[1]->SetX(iStartX - (iWidth / 2));
					slowList[1]->SetY(iStartY - (iHeight / 2));
					slowAni2->Start();

					slowAni2->FrameUpdate(TIMEMANAGER->GetElapsedTime()* multiSpeed);

				}
				else
				{
					slowList[0]->SetX(iStartX - (iWidth / 2));
					slowList[0]->SetY(iStartY - (iHeight / 2));
					slowAni1->Start();

					slowAni1->FrameUpdate(TIMEMANAGER->GetElapsedTime()* multiSpeed);
				}
			}

			if (isPoison)
			{
				if (poisonNumber == 1)
				{
					poisonList[2]->SetX(iStartX - (iWidth / 2));
					poisonList[2]->SetY(iStartY - (iHeight / 2));
					poisonAni3->Start();
					poisonAni3->FrameUpdate(TIMEMANAGER->GetElapsedTime()* multiSpeed);

				}
				else if (poisonNumber == 2)
				{
					poisonList[1]->SetX(iStartX - (iWidth / 2));
					poisonList[1]->SetY(iStartY - (iHeight / 2));
					poisonAni2->Start();
					poisonAni2->FrameUpdate(TIMEMANAGER->GetElapsedTime()* multiSpeed);

				}
				else
				{
					poisonList[0]->SetX(iStartX - (iWidth / 2));
					poisonList[0]->SetY(iStartY - (iHeight / 2));
					poisonAni1->Start();

					poisonAni1->FrameUpdate(TIMEMANAGER->GetElapsedTime()* multiSpeed);
				}
			}

		}

		{
		}


		rcEnemy = RectMakeCenter(iStartX, iStartY, iWidth, iHeight);
	}
}

void Enemy::DrawFont(HDC hdc )
{

	POINT pt = { iStartX, iStartY };
	FONTMANAGER->TextHpRender(hdc, iHp, &rcEnemy, RGB(255, 255, 255));

}

void Enemy::DreaseHp(int _attackPoint)
{

	float fMaxHp = iHp;
	float fCurrentHp = iHp - _attackPoint;
	float fRate = (fCurrentHp / fMaxHp) * 100;
	int iTemp = (255 * fRate) / 100;
	
	int iResult = (255 - iTemp);
	if (iResult < 0)
	{
		iResult = 0;
	}

	iColorG = iColorG + iResult;
	if (iColorG >= 255)
	{
		iColorG = 232;
	}
	iHp -= _attackPoint;


	if (iHp <= 0)
	{
		iHp = 0;
		isLive = false;
	}
}

void Enemy::StateAbnormalEffect(int _posX, int _posY)
{
	if (sa == eStateAbnormal::SA_NONE)
	{

	}

	if (sa == eStateAbnormal::SA_DIE)
	{
		isDieState = true;
	}

	if (sa == eStateAbnormal::SA_POISON)
	{
		isPoison = true;

	}

	if (sa == eStateAbnormal::SA_SlOW)
	{
		isSlow = true;
		q_stateAb.push(sa);

	}


	//


	//
	if (isDieState)
	{
		isLive = GAMESYS->RandomDie();
		isDieState = false;
		isDead = !isLive;
		sa = eStateAbnormal::SA_NONE;
	}


	if (isPoison)
	{
		fPoisonTime -= TIMEMANAGER->GetElapsedTime();
		if (fPoisonTime >= 0.0f)
		{
			fPoisonDeltaTime -= TIMEMANAGER->GetElapsedTime();
			if (fPoisonDeltaTime <= 0.0f)
			{
				Poison(_posX, _posY);
				fPoisonDeltaTime = 0.5f;
				poisonNumber = GAMESYS->GetPoisonNumber();
			}
		}
		else
		{
			isPoison = false;
			fPoisonTime = 3.0f;
		}
	}

	if (isSlow)
	{
		fFreezTime -= TIMEMANAGER->GetElapsedTime();
		if (fFreezTime >= 0.0f)
		{
			iSlowCount = GAMESYS->GetSlowCount();
			Slow(_posX, _posY);
		}
		else
		{
			isSlow = false;
			fMoveSpeed = fMaxMoveSpeed;
			fFreezTime = 3.0f;
		}

	}
}

void Enemy::Poison(int _posX, int _posY)
{
	iHp -= GAMESYS->GetPoisonPoint();

	if (iHp <= 0)
	{
		iHp = 0;
		isLive = false;
	}
}

void Enemy::Slow(int _posX, int _posY)
{
	float iSlow = GAMESYS->GetSlowPoint();
	
	
	multiSpeed = multiSpeed - iSlow;
	fMoveSpeed =fMoveSpeed   - iSlow;

	if (multiSpeed <= 1.f)
	{
		multiSpeed = 1.f;

	}
	if (fMoveSpeed <= 1.f  )
	{
		fMoveSpeed = 1.f;
	}
	
}

void Enemy::SetHp(int _hp)
{
	iHp = _hp;
}

