#include "Game.h"
#include "Monster.h"

Monster::Monster()
{
	_monster = new Image();
	//FrameX : x개수 / FrameY
	_monster->Init(TEXT("../Resource/Sprite/Monster.bmp"), 358, 632, 2, 4, true, RGB(255, 0, 255));
	_monster->SetX(WINSIZEX / 2);
	_monster->SetY(WINSIZEY - _monster->GetFrameHeight() - 50);
	_dir = 1;
	_dirChange = true;
	eDir = eMonsterDirection::DIR_MONSTER_LEFT;
}


Monster::~Monster()
{
	SAFE_DELETE(_monster);
}

void Monster::Update()
{
	MonsterAI();

	//if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	//{
	//	_monster->SetX(_monster->GetX() - 3);
	//	_dirChange = true;
	//	_monster->SetFrameX(0);
	//}
	//if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	//{
	//	_monster->SetX(_monster->GetX() + 3);
	//	_dirChange = false;
	//	_monster->SetFrameX(1);
	//}

	//_nCount++;
	//// 프레임 간격 조절 
	//// 게임의 신장  
	//// 프레임 스키핑 : 프레임 랜더 
	//if (_nCount % 10 == 0)
	//{
	//	if (_dirChange)
	//	{
	//		if (_iIndex >= _monster->GetMaxFrameY())
	//		{
	//			_iIndex = 0;
	//		}

	//		_iIndex++;

	//		_monster->SetFrameY(_iIndex);
	//	}
	//	else
	//	{
	//		if (_iIndex >= _monster->GetMaxFrameY())
	//		{
	//			_iIndex = 0;
	//		}

	//		_iIndex++;

	//		_monster->SetFrameY(_iIndex);
	//	}
	//	_nCount = 0;
	//}
}

void Monster::Render(HDC hdc)
{
	_monster->FrameRender(hdc, _monster->GetX(), _monster->GetY(),
		_monster->GetFrameX(), _monster->GetFrameY());
}


void Monster::MonsterAI()
{
	_monster->SetX(_monster->GetX() - 3 * _dir);
	//OffsetRect(&_rcMonster, (-3 * _dir), 0);

	CollisionCheck();
	_nCount++;
	if (_nCount % 10 == 0)
	{
		if (_dirChange)
		{
			if (_iIndex >= _monster->GetMaxFrameY())
			{
				_iIndex = 0;
			}

			_iIndex++;

			_monster->SetFrameY(_iIndex);
		}
		else if(!_dirChange)
		{
			if (_iIndex >= _monster->GetMaxFrameY())
			{
				_iIndex = 0;
			}

			_iIndex++;

			_monster->SetFrameY(_iIndex);
		}
		_nCount = 0;
	}
}

void Monster::CollisionCheck()
{
	_rcMonster = _monster->BoundingBox();


	if ((_rcMonster.left) <= 0)
	{
		_monster->SetFrameX(1);

		_dirChange = false;
		_dir *= -1;
		eDir = eMonsterDirection::DIR_MONSTER_RIGHT;

	}
	//if ((_monster->GetX() + _monster->GetFrameWidth()) >= WINSIZEX)
	if ((_rcMonster.right) >= WINSIZEX)

	{
		_monster->SetFrameX(0);
		_dirChange = true;
		_dir *= -1;
		eDir = eMonsterDirection::DIR_MONSTER_LEFT;

	}

}