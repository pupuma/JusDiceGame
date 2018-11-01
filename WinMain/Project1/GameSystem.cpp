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
	fSpeedUp = 1.f;
	iMaxSpeed = 30;
	fSpeed = 5.0f;
	fDeltaTime = 0.5f;
	chainCount = 2;
	isEnemyActivate = false;
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

	//font
	{
	HFONT font = CreateFont(10, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Adobe Caslon Pro Bold"));
	fontMap.insert({ TEXT("AdobeSS"), font });

	font = CreateFont(15, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Adobe Caslon Pro Bold"));
	fontMap.insert({ TEXT("AdobeS"), font });

	font = CreateFont(20, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Adobe Caslon Pro Bold"));
	fontMap.insert({ TEXT("AdobeB"), font });


	}
	return true;
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
	//float centerX = _pData.second.left + ((_pData.second.right - _pData.second.left) / 2);
	//float centerY = _pData.second.top + ((_pData.second.bottom - _pData.second.top) / 2);

	if (!enemyList.empty())
	{
		for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
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

						if (_dice->GetColor() != eDiceColor::DICE_RED  && _dice->GetColor() != eDiceColor::DICE_YELLOW)
						{
							(*it_Enemy).second->DreaseHp(attackPoint);
							_dice->GetBulletList()[_index]->SetFire(false);
							_dice->GetBulletList()[_index]->SetCollision(true);
							_dice->GetBulletList()[_index]->ResetPosition();
							dice = _dice;

						}
						else
						{
							ptSave = { _dice->GetBulletList()[_index]->GetBulletCenterX(),
										_dice->GetBulletList()[_index]->GetBulletCenterY() };
							_dice->GetBulletList()[_index]->SetFire(false);
							_dice->GetBulletList()[_index]->SetCollision(true);
							_dice->GetBulletList()[_index]->ResetPosition();
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
		EnemyDamage(_index, dice);
	}
	


}

void GameSystem::CollisionObject(std::list<Enemy*> _enemyList)
{
	//enemyList = _enemyList;

	//if (!enemyList.empty())
	//{
	//	std::list<Enemy*>::iterator iter = enemyList.begin();
	//	if (!(*iter)->GetActivate())
	//	{
	//		return;
	//	}
	//}
	//

	//if (!enemyList.empty())
	//{
	//	it_Enemy = enemyList.begin();
	//	if (!g_DiceList.empty())
	//	{
	//		//test = new TimeCheck("Collison");
	//		for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end(); it_Dice++)
	//		{
	//			for (size_t i = 0; i < (*it_Dice).second->GetBulletList().size(); i++)
	//			{
	//				if ((*it_Dice).second->GetBulletList()[i]->IsFire())
	//				{
	//					if (CollisionCircleAndCircle(7, (*it_Enemy)->GetPosX(), (*it_Enemy)->GetPosY(), 7,
	//						(*it_Dice).second->GetBulletList()[i]->GetBulletCenterX(),
	//						(*it_Dice).second->GetBulletList()[i]->GetBulletCenterY()))
	//					{

	//						(*it_Enemy)->SetStateAbnormalEffect((*it_Dice).second->GetStateAbnormalEffect());
	//						attackPoint = (*it_Dice).second->GetAttackPoint();
	//						DiceStateAdnormal((*it_Dice).second);

	//						{
	//							if ((*it_Dice).second->GetColor() != eDiceColor::DICE_RED)
	//							{

	//								(*it_Enemy)->DreaseHp(attackPoint);
	//								(*it_Dice).second->GetBulletList()[i]->SetFire(false);
	//								(*it_Dice).second->GetBulletList()[i]->SetCollision(true);
	//								(*it_Dice).second->GetBulletList()[i]->ResetPosition();
	//							}
	//							else
	//							{
	//								//rc = (*it_Enemy)->GetEnemyRect();
	//								ptSave = { (*it_Dice).second->GetBulletList()[i]->GetBulletCenterX(),
	//											(*it_Dice).second->GetBulletList()[i]->GetBulletCenterY() };

	//								(*it_Dice).second->GetBulletList()[i]->SetFire(false);
	//								(*it_Dice).second->GetBulletList()[i]->SetCollision(true);
	//								(*it_Dice).second->GetBulletList()[i]->ResetPosition();

	//							}
	//							break;
	//						}

	//					}
	//				}

	//			}
	//		}
	//	}
	//}
	//if (!enemyList.empty())
	//{
	//	for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
	//	{
	//		rc = (*it_Enemy)->GetEnemyRect();
	//		if (isFire)
	//		{
	//			if (CollisionCircleAndRect(GetCircleFireRadius(),
	//				ptSave.x, ptSave.y, rc))
	//			{
	//				(*it_Enemy)->DreaseHp(attackPoint);
	//			}
	//		}
	//	}
	//}



	//if (!enemyList.empty())
	//{
	//	for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); )
	//	{
	//		if ((*it_Enemy)->GetHp() == 0 || !(*it_Enemy)->IsLive())
	//		{
	//			SAFE_DELETE(*it_Enemy);
	//			it_Enemy = enemyList.erase(it_Enemy);
	//			
	//		}
	//		else
	//		{
	//			++it_Enemy;
	//		}
	//	}
	//}

	//

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

std::pair<int, POINT> GameSystem::GetPosEnemy(Dice* dice)
{
	int iCount = 0;

	if (enemyList.size()> 0)
	{
		//for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
		//{
		//	if ((*it_Enemy).second->GetActivate())
		//	{
		//		iCount++;
		//	}
		//}
		iCount = enemyList.size();
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
				//iRand /= 4;
				it_Target = std::next(it_Enemy, (iRand) );
			}
			else
			{
				it_Target = std::next(it_Enemy, (iRand));
			}
			
			//rc = (*it_Target).second->GetEnemyRect();
			pt.x = (*it_Target).second->GetPosX();
			pt.y = (*it_Target).second->GetPosY();

			pData.first = it_Target->first;
			pData.second = pt;
		}
	

	}
	

	//for (it = enemyList.begin(); it != enemyList.end(); it++)
	//{
	//	rc = (*it)->GetEnemyRect();
	//	break;
	//}

	return pData;
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
		//Dice* dice = new Dice();
		diceColor = eDiceColor::DICE_YELLOW;
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

	//std::list<std::pair<int, Dice*>>::iterator it;

	//for(it = g_DiceList.begin(); it != g_DiceList.end(); it++)
	//{
	//	if (it->first == iDiceIndex)
	//	{
	//		(*it).second->SetColor(diceColor);
	//		break;
	//	}
	//}
	//

	
	
}


void GameSystem::RenderText(HDC hdc, const std::string fontName, const std::string strText, POINT* pos, COLORREF color)
{
	TCHAR szStr[256] = { 0, };
	HFONT oldFont;

	it_Font = fontMap.find(fontName);
	if (it_Font != fontMap.end())
	{
		HFONT font = (HFONT)(it_Font->second);
		oldFont = (HFONT)SelectObject(hdc, font);
		COLORREF oldColor = SetTextColor(hdc, color);
		
		

		TextOut(hdc, pos->x, pos->y, strText.c_str(), strText.size());

		SelectObject(hdc, oldFont);
		SetTextColor(hdc, oldColor);
	}
}

void GameSystem::TextEnemyHpRender(HDC hdc, int iHp, RECT * rc, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szStr[256] = { 0, };
	HFONT oldFont;

	std::string fontName;
	if (iHp >= 1000 && iHp < 100000)
	{
		fontName = TEXT("AdobeSS");

	}
	else if (iHp > 100 && iHp < 1000)
	{
		fontName = TEXT("AdobeS");

	}
	else
	{
		fontName = TEXT("AdobeB");
	}

	it_Font = fontMap.find(fontName);

	if (it_Font != fontMap.end())
	{
		HFONT font = (HFONT)(it_Font->second);
		oldFont = (HFONT)SelectObject(hdc, font);
		COLORREF oldColor = SetTextColor(hdc, color);

		TCHAR strHp[256];
		_stprintf(strHp, TEXT("%d"), iHp);

		//TextOut(hdc, pos->x, pos->y, strText.c_str(), strText.size());
		DrawText(hdc, strHp, _tcslen(strHp), rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);


		SelectObject(hdc, oldFont);
		SetTextColor(hdc, oldColor);
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
			fDeltaTime = 0.5f;
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
			else if(color == eDiceColor::DICE_YELLOW)
			{
				if (_dice->IsChain())
				{
					
				}
			}
		}
	}

	if (!enemyList.empty())
	{
		for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); )
		{
			if (!(*it_Enemy).second->GetActivate())
			{
				break;
			}

			if ((*it_Enemy).second->GetHp() == 0 || !(*it_Enemy).second->IsLive())
			{
				SAFE_DELETE((*it_Enemy).second);
				it_Enemy = enemyList.erase(it_Enemy);
				_dice->SetTargeting(false);
				_dice->GetBulletList()[_index]->SetFire(false);
				_dice->GetBulletList()[_index]->SetCollision(true);
				_dice->GetBulletList()[_index]->ResetPosition();
			}
			else
			{
				++it_Enemy;
			}
		}
	}

}

void GameSystem::ChainRender(HDC hdc, BYTE _key)
{
}
