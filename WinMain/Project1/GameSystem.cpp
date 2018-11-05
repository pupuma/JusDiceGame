#include "Game.h"
#include "GameSystem.h"

#include "Bullet.h"
#include "Dice.h"
#include "Enemy.h"

#include "RedDice.h"
#include "YellowDice.h"
#include "BlueDice.h"
#include "GreenDice.h"
#include "GrayDice.h"
#include "BlackDice.h"

GameSystem::GameSystem()
{
	iGold = 0;
	iRound = 1;
	iCount = 1;
	iBossConstant = 10;
	iEnemyHp = 1;
	slowCount = 0;
	poisonNumber = 0;
	iDiceWidth = 73;
	iDiceHeight = 60;
	iDiceIndex = -1;
	iPrevIndex = 0;
	iBoardCount = 0;
	fSpeedUp = 1.f;
	iMaxSpeed = 30;
	fSpeed = 5.0f;
	fDeltaTime =1.f;
	chainCount = 2;
	iEnemyCount = 0;
	isEnemyActivate = false;
	speedUp = 1;
	g_State = GAMESTATE_NONE;
}


GameSystem::~GameSystem()
{
}

bool GameSystem::Init()
{
	{
		for (int i = 1; i <= 100; i++)
		{
			randomList.push_back(i);
		}

	}
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



	{
		for (int i = 0; i < 100; i++)
		{
			chain.chainAcitve = false;
			chain.pt = { 0,0 };
			chainList.push_back(chain);
		}
	}
	return true;
}

void GameSystem::Release()
{
	// DiceList
	for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end();  )
	{
		(*it_Dice).second->Release();
		SAFE_DELETE((*it_Dice).second);
		++it_Dice;
	}
	g_DiceList.clear();
	// EnemyList
	for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end();  )
	{
		(*it_Enemy).second->Release();
		SAFE_DELETE((*it_Enemy).second);
		++it_Enemy;
	}
	enemyList.clear();
}

void GameSystem::Update()
{
	{
		if (!enemyList.empty())
		{
			it_Enemy = enemyList.begin();
			if (!(*it_Enemy).second->GetActivate())
			{
				SetEnemyActivate(false);
			}
		}


	}
	{
		if (!enemyList.empty())
		{
			for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); )
			{
				if (!(*it_Enemy).second->GetActivate())
				{
					break;
				}

				if ((*it_Enemy).second->IsDead())
				{
					EFFECTMANAGER->Play(TEXT("SkelEffect"), (*it_Enemy).second->GetPosX(), (*it_Enemy).second->GetPosY());
				}

				if ((*it_Enemy).second->GetHp() <= 0 || !(*it_Enemy).second->IsLive())
				{
					if (iRound % 10 != 0)
					{
						GoldGain();
						iEnemyCount++;

					}
					else
					{
						iGold = iRound * 10 ;
						iEnemyCount = iRound;
					}
					EFFECTMANAGER->Play(TEXT("Effect"), (*it_Enemy).second->GetPosX(), (*it_Enemy).second->GetPosY());

					SAFE_DELETE((*it_Enemy).second);

					it_Enemy = enemyList.erase(it_Enemy);
					_dice->SetTargeting(false);
					//_dice->GetBulletList()[_index]->SetFire(false);
					//_dice->GetBulletList()[_index]->SetCollision(true);
					//_dice->GetBulletList()[_index]->ResetPosition();
				}
				else
				{
					++it_Enemy;
				}
			}
		}
	}

	{
		if (g_State == GAMESTATE_IDLE)
		{
			SetEnemyActivate(false);
			for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end(); it_Dice++)
			{
				(*it_Dice).second->SetTargeting(false);

				for (int i = 0; i < 6; i++)
				{
					(*it_Dice).second->GetBulletList()[i]->SetFire(false);
					(*it_Dice).second->GetBulletList()[i]->SetCollision(false);

					if ((*it_Dice).second->GetBulletList()[i]->IsFire())
					{
						DiceEffect((*it_Dice).second->GetColor(),
							(*it_Dice).second->GetBulletList()[i]->GetBulletCenterX(),
							(*it_Dice).second->GetBulletList()[i]->GetBulletCenterY());
					}
					(*it_Dice).second->GetBulletList()[i]->ResetPosition();


				}
			}
		}
	}

	if (g_State == GAMESTATE_START)
	{
		if (iEnemyCount == iRound)
		{
			if (q_Enemy.empty())
			{
				if (enemyList.empty())
				{
					g_State = GAMESTATE_IDLE;
					iRound++;
				}
			}
		}
		
	}
}

void GameSystem::EnemyUpdate()
{
	{
		if (!enemyList.empty())
		{
			for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
			{
				(*it_Enemy).second->Update();
			}
		}
	}
}

void GameSystem::EnemyListRender(HDC hdc)
{
	{
		if (!enemyList.empty())
		{
			for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
			{
				if ((*it_Enemy).second->GetActivate())
				{
					(*it_Enemy).second->Render(hdc);
				}
			}
		}

	}
}

void GameSystem::CollisionBullet(Dice* _dice, int _index, std::pair<int,POINT> _pData)
{
	attackPoint = _dice->GetAttackPoint();
	Dice* dice = NULL;
	int iCount = 0;

	{
		
	}


	if (!enemyList.empty())
	{
		for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++, iCount++)
		{
			if (_dice->GetBulletList()[_index]->IsFire())
			{
				if (!(*it_Enemy).second->GetActivate())
				{
					break;
				}
				if ((*it_Enemy).first == _pData.first)
				{
					if (CollisionCircleAndCircle(7, (*it_Enemy).second->GetPosX(), (*it_Enemy).second->GetPosY(), 7,
						_dice->GetBulletList()[_index]->GetBulletCenterX(),
						_dice->GetBulletList()[_index]->GetBulletCenterY()))
					{

						(*it_Enemy).second->SetStateAbnormalEffect(_dice->GetStateAbnormalEffect());
						DiceStateAdnormal(_dice);
						attackPoint = _dice->GetAttackPoint();
						DiceEffect(_dice->GetColor(), _dice,_index);
						if (_dice->GetColor() == eDiceColor::DICE_RED)
						{
							ptSave = { _dice->GetBulletList()[_index]->GetBulletCenterX(),
										_dice->GetBulletList()[_index]->GetBulletCenterY() };
							_dice->GetBulletList()[_index]->SetFire(false);
							_dice->GetBulletList()[_index]->SetCollision(true);

							//_dice->GetBulletList()[_index]->ResetPosition();
							dice = _dice;
						}
						else if (_dice->GetColor() == eDiceColor::DICE_YELLOW)
						{

							_dice->GetBulletList()[_index]->SetFire(false);
							_dice->GetBulletList()[_index]->SetCollision(true);
							//_dice->GetBulletList()[_index]->ResetPosition();
							dice = _dice;
						}
						else
						{
							(*it_Enemy).second->DreaseHp(attackPoint);
							_dice->GetBulletList()[_index]->SetFire(false);
							_dice->GetBulletList()[_index]->SetCollision(true);
							//_dice->GetBulletList()[_index]->ResetPosition();
							dice = _dice;
						}
						break;

					}

				}	
			}

		}
	}

	// bullet
	

	//
	if (dice != NULL)
	{
		if (dice->GetColor() == eDiceColor::DICE_YELLOW)
		{
			ChainDamage(_pData.first,dice);
		}
		EnemyDamage(_index, dice);
	}
	


}


void GameSystem::BulletCollision()
{
	for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end(); it_Dice++)
	{
		for (size_t i = 0; i < (*it_Dice).second->GetBulletList().size(); i++)
		{
			if ((*it_Dice).second->GetBulletList()[i]->IsFire())
			{
				(*it_Dice).second->GetBulletList()[i]->SetCollision(false);

			}

		}
	}

}



void GameSystem::AddEnemy(Enemy * _enemy, int index)
{
	std::pair<int, Enemy*> p_Data;
	p_Data.first = index;
	p_Data.second = _enemy;
	q_Enemy.push(p_Data);
}

int GameSystem::EnemyType()
{
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

std::pair<int, POINT> GameSystem::GetPosEnemy(Dice* dice)
{
	int iCount = 0;

	if (!enemyList.empty())
	{
		for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
		{
			if ((*it_Enemy).second->GetActivate())
			{
				iCount++;
			}
		}
	}

	
	int iRand = RAND->GetFromIntoTo(0, iCount);

	if (iRand == iCount)
	{
		iRand--;
	}
	if (iRand == -1)
	{
		iRand = 0;
	}

	std::pair<int, POINT> pData;

	POINT pt = { 0,0 };


	int iSize = enemyList.size();
	if (!dice->IsTargeting())
	{
		if (!enemyList.empty())
		{
			std::list<std::pair<int, Enemy*>>::iterator it_Target;
			std::list<std::pair<int, Enemy*>>::iterator it_Enemy = enemyList.begin();

			if (iRand > (iSize / 4))
			{
				it_Target = std::next(it_Enemy, (iRand) );
			}
			else
			{
				it_Target = std::next(it_Enemy, (iRand));
			}
			
			pt.x = (*it_Target).second->GetPosX();
			pt.y = (*it_Target).second->GetPosY();

			pData.first = it_Target->first;
			pData.second = pt;
		}
	

	}
	

	return pData;
}

int GameSystem::GetEnemyHp()
{
	if (0 == (iRound % 10))
	{
		iCount++;
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

void GameSystem::AddDice()
{
	iDiceIndex = RAND->GetFromIntoTo(0, 24);
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

	int iRand = RAND->GetFromIntoTo(0, 5);
	eDiceColor diceColor = (eDiceColor)iRand;

	
	if (false == pSaveInfo[iDiceIndex].first)
	{
		//diceColor = eDiceColor::DICE_BLUE;
		Dice* dice = DiceRandomCreate(diceColor);

		pSaveInfo[iDiceIndex].first = true;

		assert(dice != NULL);
		diceInfo.first = iDiceIndex;
		diceInfo.second = dice;
		

		if (!dice->Init(pSaveInfo[iDiceIndex].second.x, pSaveInfo[iDiceIndex].second.y,rcGameBoard))
		{
			return;
		}

		

		g_DiceList.push_back(diceInfo);
		
		iBoardCount++;

	}

	{
	}

	
	
}

Dice* GameSystem::DiceRandomCreate(int _rand)
{
	eDiceColor _color = (eDiceColor)_rand;

	switch (_color)
	{
	case eDiceColor::DICE_RED:
		_dice = new RedDice();
		break;
	case eDiceColor::DICE_YELLOW:
		_dice = new YellowDice();
		break;
	case eDiceColor::DICE_BLUE:
		_dice = new BlueDice();
		break;
	case eDiceColor::DICE_GREEN:
		_dice = new GreenDice();
		break;
	case eDiceColor::DICE_GRAY:
		_dice = new GrayDice();
		break;
	case eDiceColor::DICE_BLACK:
		_dice = new BlackDice();
		break;

	}

	return _dice;
}

std::list<std::pair<int, Dice*>> GameSystem::ConvergeDice(std::list<std::pair<int, Dice*>> _diceList, int _selectNumber, int _destSelectNumber, int _level)
{
	g_DiceList = _diceList;
	std::list<std::pair<int, Dice*>>::iterator it;
	std::list<std::pair<int, Dice*>>::iterator iter;

	int iDeleteNumber = _selectNumber;
	int iTemp = _destSelectNumber;
	
	//
	
	
	int iIndex = _destSelectNumber;
	POINT pos = pSaveInfo[iTemp].second;
	int level = _level;

	//
	SelectDeleteDice(iDeleteNumber);
	SelectDeleteDice(iTemp);

	//
	SelectAddDice(iIndex, pos, level);

	return g_DiceList;
}

void GameSystem::SelectDeleteDice(int _number)
{
	std::list<std::pair<int, Dice*>>::iterator it;

	for (it = g_DiceList.begin(); it != g_DiceList.end();)
	{
		if (it->first == _number)
		{
			pSaveInfo[_number].first = false;
			iBoardCount--;
			iPrevIndex = -1;
			(*it).second->ResetBullet();
			it = g_DiceList.erase(it);
			
		}
		else
		{
			++it;

		}
		
	}
}

void GameSystem::SelectAddDice(int _index, POINT _pt, int _level)
{
	iBoardCount++;
	iPrevIndex = -1;

	pSaveInfo[_index].first = true;

	int iRand = RAND->GetFromIntoTo(0, 5);
	eDiceColor diceColor = (eDiceColor)iRand;

	Dice* dice = DiceRandomCreate(diceColor);

	int level = _level;
	level++;
	dice->SetDiceLevel(level);
	if (!dice->Init(_pt.x, _pt.y, rcGameBoard))
	{
		return;
	}

	
	dice->ResetBullet();
	diceInfo.first = _index;
	diceInfo.second = dice;

	g_DiceList.push_back(diceInfo);

}

bool GameSystem::CompareDice(std::list<std::pair<int, Dice*>> _diceList, int _selectNumber, int _destSelectNumber)
{
	std::list<std::pair<int, Dice*>>::iterator it;
	std::list<std::pair<int, Dice*>>::iterator iter;

	
	g_DiceList = _diceList;

	for (it = g_DiceList.begin(); it != g_DiceList.end(); it++)
	{
		for (iter = g_DiceList.begin(); iter != g_DiceList.end(); iter++)
		{
			if (it->first == _selectNumber)
			{
				if (iter->first == _destSelectNumber)
				{
					if ((*it).second->GetDiceLevel() == (*iter).second->GetDiceLevel())
					{
						if ((*it).second->GetColor() == (*iter).second->GetColor())
						{
							return true;
						}

					}
				}
			}
			
		}
	}
	return false;
}

bool GameSystem::IsEnemyEmpty()
{
	if (!enemyList.empty())
	{
		return false;
	}
	return true;
}

bool GameSystem::RandomDie()
{
	std::vector<int> vSelectNubmer;
	
	for (size_t i = 0; i < randomList.size(); i++)
	{
		vSelectNubmer.push_back(randomList[i]);
	}

	int iRand = RAND->GetFromIntoTo(1, 100);
	//Shuffle
	for (size_t i = 0; i < 500; i++)
	{
		int index1 = RAND->GetFromIntoTo(0,99);
		int index2 = RAND->GetFromIntoTo(0, 99);
		int iTemp = vSelectNubmer[index1];
		vSelectNubmer[index1] = vSelectNubmer[index2];
		vSelectNubmer[index2] = iTemp;
	}

	//
	for (size_t i = 0; i < GetProbabilitySize(); i++)
	{
		if (iRand == randomList[i])
		{
			return false;
		}
	}
	return true;
}

float GameSystem::GetSlowPoint()
{
	return slowPoint;
}

void GameSystem::DiceStateAdnormal(Dice * dice)
{
	dice->DiceAbility();
}

float GameSystem::GetSpeed()
{
	return fSpeed;
}

float GameSystem::GraySpeed()
{
	return (fSpeed + fSpeedUp);
}

void GameSystem::SetDiceListOn(std::list<std::pair<int, Dice*>> _diceList, int iSelectNumber)
{
	g_DiceList = _diceList;

	eDiceColor color;
	int iLevel;

	for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end(); it_Dice++)
	{
		if (it_Dice->first == iSelectNumber)
		{
			color = (*it_Dice).second->GetColor();
			iLevel = (*it_Dice).second->GetDiceLevel();
			break;
		}
	}

	for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end(); it_Dice++)
	{
		if (it_Dice->first == iSelectNumber)
		{
			continue;
		}
		else
		{
			if ((*it_Dice).second->GetColor() != color || (*it_Dice).second->GetDiceLevel() != iLevel)
			{
				(*it_Dice).second->SetDiceOn(true);
			}
		}
	}



}

void GameSystem::SetDiceListOff()
{
	for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end(); it_Dice++)
	{
		(*it_Dice).second->SetDiceOn(false);

	}
}

void GameSystem::EnemyProDuce()
{
	{
		fDeltaTime -= TIMEMANAGER->GetElapsedTime();

		if (fDeltaTime <= 0)
		{
			if (!q_Enemy.empty())
			{
				enemyList.push_back(q_Enemy.front());
				q_Enemy.pop();
			}
			fDeltaTime = 1.f;
		}

	}
}

std::pair<int, POINT> GameSystem::TargetUpdate(std::pair<int, POINT> _target)
{

	for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
	{
		if (!(*it_Enemy).second->GetActivate())
		{
			break;
		}
		else
		{
			if ((*it_Enemy).first == _target.first)
			{
				_target.first = (*it_Enemy).first;
				_target.second.x = (*it_Enemy).second->GetPosX();
				_target.second.y = (*it_Enemy).second->GetPosY();
				return _target;
			}
			else
			{
			}
		}
		
	}

	_target.first = -1;
	_target.second.x = 0;
	_target.second.y = 0;

	return _target;
}

void GameSystem::EnemyDamage(int _index, Dice* _dice)
{
	eDiceColor color= _dice->GetColor();
	if (!enemyList.empty())
	{
		for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
		{
			if (!(*it_Enemy).second->GetActivate())
			{
				break;
			}

			rc = (*it_Enemy).second->GetEnemyRect();
			if (isFire && color == eDiceColor::DICE_RED)
			{
				if (CollisionCircleAndRect(GetCircleFireRadius(),
					ptSave.x, ptSave.y, rc))
				{
					(*it_Enemy).second->DreaseHp(attackPoint);
				}
			}

		}
	}


}


void GameSystem::ChainDamage(int _targetNumber, Dice* _dice)
{
	int iCount = 0;
	std::list<std::pair<int, Enemy*>>::iterator iter = enemyList.begin();

	if (!enemyList.empty())
	{
		for (; iter != enemyList.end(); iter++)
		{
			if (iter->first == _targetNumber)
			{
				break;
			}
		}
		//chainCount = 6;
		
		int index = 0;
		while (chainCount > 0)
		{
			chainList[index].pt.x = (*iter).second->GetPosX();
			chainList[index].pt.y = (*iter).second->GetPosY();


			(*iter).second->DreaseHp(attackPoint);
			EFFECTMANAGER->Play(TEXT("ChainEffect"), chainList[index].pt.x, chainList[index].pt.y);

			iter = std::next(iter, 1);

			chainCount--;
			index++;
			if (iter == enemyList.end())  
			{
				break;
			}
		}
		chainCount = 2;
	}
	//iCount;


}

void GameSystem::DiceEffect(eDiceColor _color, Dice* _dice, int _index)
{
	switch (_color)
	{
	case eDiceColor::DICE_BLACK:
		EFFECTMANAGER->Play(TEXT("BlackBulletEffect"), _dice->GetBulletList()[_index]->GetBulletCenterX(), _dice->GetBulletList()[_index]->GetBulletCenterY());
		break;
	case eDiceColor::DICE_BLUE:
		EFFECTMANAGER->Play(TEXT("BlueBulletEffect"), _dice->GetBulletList()[_index]->GetBulletCenterX(), _dice->GetBulletList()[_index]->GetBulletCenterY());
		slowCount++;
		break;
	case eDiceColor::DICE_GRAY:
		EFFECTMANAGER->Play(TEXT("GrayBulletEffect"), _dice->GetBulletList()[_index]->GetBulletCenterX(), _dice->GetBulletList()[_index]->GetBulletCenterY());
		break;
	case eDiceColor::DICE_GREEN:
		EFFECTMANAGER->Play(TEXT("GreenBullectEffect"), _dice->GetBulletList()[_index]->GetBulletCenterX(), _dice->GetBulletList()[_index]->GetBulletCenterY());
		poisonNumber = RAND->GetFromIntoTo(1, 3);
		break;
	case eDiceColor::DICE_RED:
		EFFECTMANAGER->Play(TEXT("RedBulletEffect"), _dice->GetBulletList()[_index]->GetBulletCenterX(), _dice->GetBulletList()[_index]->GetBulletCenterY());
		break;
	case eDiceColor::DICE_YELLOW:
		EFFECTMANAGER->Play(TEXT("YellowBulletEffect"), _dice->GetBulletList()[_index]->GetBulletCenterX(), _dice->GetBulletList()[_index]->GetBulletCenterY());

		break;

	}

	SOUNDMANAGER->Play(TEXT("Sound"), 1.f);

}

void GameSystem::DiceEffect(eDiceColor _color, int x, int y)
{
	switch (_color)
	{
	case eDiceColor::DICE_BLACK:
		EFFECTMANAGER->Play(TEXT("BlackBulletEffect"), x, y);
		break;
	case eDiceColor::DICE_BLUE:
		EFFECTMANAGER->Play(TEXT("BlueBulletEffect"), x, y);
		break;
	case eDiceColor::DICE_GRAY:
		EFFECTMANAGER->Play(TEXT("GrayBulletEffect"), x, y);
		break;
	case eDiceColor::DICE_GREEN:
		EFFECTMANAGER->Play(TEXT("GreenBullectEffect"), x, y);
		break;
	case eDiceColor::DICE_RED:
		EFFECTMANAGER->Play(TEXT("RedBulletEffect"), x, y);
		break;
	case eDiceColor::DICE_YELLOW:
		EFFECTMANAGER->Play(TEXT("YellowBulletEffect"), x, y);
		break;

	}
	SOUNDMANAGER->Play(TEXT("Sound"), 1.f);

}

void GameSystem::SetGoldSale(int _gold)
{
	iGold = iGold - _gold; 
}

bool GameSystem::GameActivate(Dice* _dice, int index)
{
	if (!enemyList.empty())
	{
		(it_Enemy) = enemyList.begin();

		if (!(*it_Enemy).second->GetActivate())
		{
			for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end(); it_Dice++)
			{
				for (int i = 0; i < 6; i++)
				{
					(*it_Dice).second->GetBulletList()[i]->SetFire(false);
					(*it_Dice).second->GetBulletList()[i]->ResetPosition();
					(*it_Dice).second->SetTargeting(false);
				}
			}

			return true;
		}
	}

	return false;
}

void GameSystem::IsSpeedUp()
{
	speedUp = 4;
}

void GameSystem::IsSpeedIDle()
{
	speedUp = 2;
}

void GameSystem::Reset()
{
	//Init();
	iRound = 1;
	std::vector<std::pair<bool, POINT>>::iterator iter;
	for (iter = pSaveInfo.begin(); iter != pSaveInfo.end(); iter++)
	{
		(*iter).first = false;
	}
	g_DiceList.clear();
	iBoardCount = 0;

	DICEMANAGER->Reset();
	//AddDice();

}

bool GameSystem::GetDiceFull()
{
	if (g_DiceList.size() >= 25)
	{
		return true;
	}
	return false;
}
