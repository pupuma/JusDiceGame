#include "Game.h"
#include "GameSystem.h"

#include "Bullet.h"
#include "Dice.h"
#include "Enemy.h"


GameSystem::GameSystem()
{
	iRound = 1;
	iCount = 1;
	iBossConstant = 10;
	fCoolTime = 1.0f;
	iEnemyHp = 1;


	iDiceWidth = 73;
	iDiceHeight = 60;
	iDiceIndex = -1;
	iPrevIndex = 0;
	iBoardCount = 0;
}


GameSystem::~GameSystem()
{
}

bool GameSystem::Init()
{
	{
		int iSaveDiceX = 148;
		int iSaveDiceY = 237;


		int x = iSaveDiceX;
		int y = iSaveDiceY;

		POINT ptSaveDice;
		int temp = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				ptSaveDice.x = x;
				ptSaveDice.y = y;

				saveDiceInfo.first = false;
				saveDiceInfo.second = ptSaveDice;

				pSaveInfo.push_back(saveDiceInfo);

				x = x + iDiceWidth + 2;

				temp++;
			}
			x = iSaveDiceX;
			y = y + iDiceHeight + 2;
		}

	}
	return true;
}

bool GameSystem::CollisionBullet(Bullet* _bullet, const RECT _target)
{
	float fRadius = 7.0f;
	float fPosX = _bullet->GetBulletCenterX();
	float fPosY = _bullet->GetBulletCenterY();

	float fTargetPosX = _target.left + ((_target.right - _target.left) / 2);
	float fTargetPosY = _target.top + ((_target.bottom - _target.top) / 2);

	fCoolTime -= TIMEMANAGER->GetElapsedTime();
	if (CollisionCircleAndPoint(fRadius, fPosX, fPosY, fTargetPosX, fTargetPosY) || fCoolTime <= 0 )
	{
		_bullet->SetFire(false);
		_bullet->ResetPosition();
		_bullet->SetCollision(true);
		fCoolTime = 1.0f;

		// Enemy
		
		return true;
	}

	return false;
	
}



void GameSystem::AddEnemy()
{
}

int GameSystem::EnemyType()
{
	
	
	//iRound = iRound * iCount;
	if (0 == (iRound % 10))
	{
		return 1;
	}

	return 0;
}

int GameSystem::EnemyCount()
{
	if (0 == (iRound % 10))
	{
		return 1;
	}
	
	return iRound;
}

RECT GameSystem::GetRectEnemy()
{
	std::list<Enemy*>::iterator it =  enemyList.begin();
	RECT rc;
	//for (it = enemyList.begin(); it != enemyList.end(); it++)
	//{
	//	rc = (*it)->GetEnemyRect();
	//	break;
	//}
	rc = (*it)->GetEnemyRect();

	return rc;
}

int GameSystem::GetEnemyHp()
{

	/*
	일반몹 스테이지 별 채력  =  iRound * iCount ;
	보스몹 스테이지 별 채력  =  iRound * iCount * iBossConstant;
	*/
	if (0 == (iRound % 10))
	{
		iEnemyHp = iRound * iCount * iBossConstant;
	}
	else
	{
		iEnemyHp = iRound * iCount;
	}


	return iEnemyHp;
}

void GameSystem::GetDiceList(std::vector<Dice*> _diceList)
{
	diceList = _diceList;
}

void GameSystem::CollisionEnemy(std::list<Enemy*> _enmeyList)
{
	// Enemy
	enemyList = _enmeyList;
	std::list<Enemy*>::iterator it;

	// Dice
	//std::vector<Dice*>::iterator iter;


	// Dice 
	{

	}
}

void GameSystem::AddDice()
{
	iDiceIndex = RAND->GetFromIntoTo(0, 23);
	while (true)
	{
		if (iBoardCount >= 25)
		{
			return;
		}

		if (iDiceIndex == iPrevIndex)
		{
			iDiceIndex = RAND->GetFromIntoTo(0, 24);
			continue;
		}
		else if ((iDiceIndex != iPrevIndex))
		{
			if (true == pSaveInfo[iDiceIndex].first)
			{
				iDiceIndex = RAND->GetFromIntoTo(0, 24);
				continue;
			}
			else
			{
				break;
			}
		}
		
	}


	iPrevIndex = iDiceIndex;

	int iRand = RAND->GetFromIntoTo(1, 6);
	eDiceColor diceColor = (eDiceColor)iRand;

	
	if (false == pSaveInfo[iDiceIndex].first)
	{
		Dice* dice = new Dice();
		pSaveInfo[iDiceIndex].first = true;
		

		if (!dice->Init(pSaveInfo[iDiceIndex].second.x, pSaveInfo[iDiceIndex].second.y, rcGameBoard, diceColor))
		{
			return;
		}

		diceInfo.first = iDiceIndex;
		diceInfo.second = dice;

		g_DiceList.push_back(diceInfo);
		
		iBoardCount++;

	}

	std::list<std::pair<int, Dice*>>::iterator it;

	for(it = g_DiceList.begin(); it != g_DiceList.end(); it++)
	{
		if (it->first == iDiceIndex)
		{
			(*it).second->SetColor(diceColor);
			break;
		}
	}
	

	
	
}
