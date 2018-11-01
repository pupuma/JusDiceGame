#include "Game.h"
#include "Enemy.h"



Enemy::Enemy()
{
	test = new TimeCheck(TEXT("Enemy"));
	// hp
	iHp = 100;

	// position 
	iStartX = 59;
	iStartY = 60;
	
	// size
	iNomalWidth = 54;
	iNomalHeight = 44;
	//iNomalWidth = 85;
	//iNomalHeight = 63;
	// 
	iColorR = 255;
	iColorG = 23;
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

bool Enemy::Init(int _y)
{
	//
	{
		enemyType = (eEnemyType)GAMESYS->EnemyType();
	}

	{
		iStartY += _y;
		rcEnemy = RectMakeCenter(iStartX, iStartY, iNomalWidth, iNomalHeight);
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

void Enemy::Update()
{
	
	{
		EnemyAI();
	}

}

void Enemy::Render(HDC hdc)
{
	DrawObject(hdc, rcEnemy, 1, RGB(iColorR, iColorG, iColorB), ROUNDRECT);
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
		
		//iStartX += cosf(fAngle) * iMoveSpeed;
		//iStartY += -sinf(fAngle) * iMoveSpeed;

		iStartX += cosf(fAngle) * fMoveSpeed;
		iStartY += -sinf(fAngle) * fMoveSpeed;

		if ((iStartY + iNomalHeight /2  >= 0))
		{
			//
			SetActivate(true);
			GAMESYS->SetEnemyActivate(true);
		}


		rcEnemy = RectMakeCenter(iStartX, iStartY, iNomalWidth, iNomalHeight);
	}
}

void Enemy::DrawFont(HDC hdc )
{
	//SetBkMode(hdc, TRANSPARENT);

	//TCHAR strHp[256];
	//_stprintf(strHp, TEXT("%d"), iHp);

	//TextOut(hdc, iStartX, iStartY, strHp, _tcslen(strHp));
	
	//DrawText(hdc, strHp, _tcslen(strHp), &rcEnemy, DT_CENTER | DT_SINGLELINE | DT_VCENTER );
	POINT pt = { iStartX, iStartY };
	//GAMESYS->RenderText(hdc, TEXT("Adobe"), strHp, &pt, RGB(0, 0,0));
#if defined(_DEBUG_TEST)
	GAMESYS->TextEnemyHpRender(hdc, iHp, &rcEnemy, RGB(255,255,255));
#endif //
}

void Enemy::DreaseHp(int _attackPoint)
{
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
}

void Enemy::Slow(int _posX, int _posY)
{
	float iSlow = GAMESYS->GetSlowPoint();

	fMoveSpeed -= iSlow;

	if (fMoveSpeed <= 1.f)
	{
		fMoveSpeed = 1.f;
	}
	
}

