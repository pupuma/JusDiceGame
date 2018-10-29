#include "Game.h"
#include "Enemy.h"



Enemy::Enemy()
{
	
	// hp
	iHp = 30;

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

	iMoveSpeed = 2;
	
}


Enemy::~Enemy()
{
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

		float fAngle = UTIL::GetAngle(fPosX, fPosY, ptCurrentPos.x, ptCurrentPos.y);

		iStartX += cosf(fAngle) * iMoveSpeed;
		iStartY += -sinf(fAngle) * iMoveSpeed;

		if ((iStartY + iNomalHeight /2  >= 0))
		{
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
	}
}

