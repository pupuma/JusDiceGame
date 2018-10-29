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


	isEnemyActivate = false;
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

bool GameSystem::CollisionBullet(Bullet* _bullet, const RECT _target)
{
	float fRadius = 7.0f;
	float fPosX = _bullet->GetBulletCenterX();
	float fPosY = _bullet->GetBulletCenterY();

	float fTargetPosX = _target.left + ((_target.right - _target.left) / 2);
	float fTargetPosY = _target.top + ((_target.bottom - _target.top) / 2);


	//fCoolTime -= TIMEMANAGER->GetElapsedTime();
	if (CollisionCircleAndPoint(fRadius, fPosX, fPosY, fTargetPosX, fTargetPosY))
	{
		_bullet->SetFire(false);
		_bullet->ResetPosition();
		_bullet->SetCollision(true);
		//_bullet->SetPosition(
		//fCoolTime = 1.0f;

		// Enemy

		return true;
	}

	return false;

}

void GameSystem::CollisionObject(std::list<Enemy*> _enemyList)
{
	enemyList = _enemyList;
	// monster6
	if (!enemyList.empty())
	{
		for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); it_Enemy++)
		{
			if (!g_DiceList.empty())
			{
				for (it_Dice = g_DiceList.begin(); it_Dice != g_DiceList.end(); it_Dice++)
				{
					for (size_t i = 0; i < (*it_Dice).second->GetBulletList().size(); i++)
					{
						if ((*it_Dice).second->GetBulletList()[i]->IsFire())
						{
							if (CollisionCircleAndCircle(2, (*it_Enemy)->GetPosX(), (*it_Enemy)->GetPosY(), 7,
								(*it_Dice).second->GetBulletList()[i]->GetBulletCenterX(),
								(*it_Dice).second->GetBulletList()[i]->GetBulletCenterY()))
							{
								int attackPoint = (*it_Dice).second->GetAttackPoint();
								(*it_Enemy)->DreaseHp(attackPoint);
								(*it_Dice).second->GetBulletList()[i]->SetFire(false);
								(*it_Dice).second->GetBulletList()[i]->SetCollision(true);
								(*it_Dice).second->GetBulletList()[i]->ResetPosition();

								break;
							}
						}

					}
				}
			}
		}
	}

	if (!enemyList.empty())
	{
		for (it_Enemy = enemyList.begin(); it_Enemy != enemyList.end(); )
		{
			if ((*it_Enemy)->GetHp() == 0)
			{
				it_Enemy = enemyList.erase(it_Enemy);
			}
			else
			{
				++it_Enemy;
			}
		}
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
