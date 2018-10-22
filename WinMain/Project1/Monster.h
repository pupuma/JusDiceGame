#pragma once
enum eMonsterDirection
{
	DIR_MONSTER_LEFT,
	DIR_MONSTER_RIGHT,
};


class Monster
{
	Image*	_monster;
	RECT _rcMonster;
	eMonsterDirection eDir;
	int		_nCount;
	int		_iIndex;
	bool _dirChange;
	int _dir;
public:
	Monster();
	~Monster();
public:
	void Update();
	void Render(HDC hdc);
public:
	void MonsterAI();
	void CollisionCheck();
	RECT GetRectMonster() { return _rcMonster; }
	Image* GetImage() { return _monster; }
	eMonsterDirection GetDirection() { return eDir; }
};

