#include "Game.h"
#include "Player.h"
#include "GameSystem.h"


Player::Player()
{
	//_player = new Image();
	//_player->Init(TEXT("../Resource/Sprite/SivaRun.bmp"), 440, 108, 8, 2, true, RGB(255, 0, 255));
	_player = IMAGEMANAGER->FindImage(TEXT("Player"));
	assert(_player != NULL);

	_player->SetX(WINSIZEX / 2 - 200);
	_player->SetY(WINSIZEY - 100);
	isGround = true;
	_gravity = 0.0f;
	_jumpPower = 0.0f;
	_speed = 5;
	_isJump = false;
	eDir = ePlayerDirection::DIR_PLAYER_LEFT;

	pPos = new POINT();
	pPos->x = WINSIZEX / 2 - 200;
	pPos->y = WINSIZEY - 200;


}


Player::~Player()
{
	//SAFE_DELETE(_player);

}

void Player::Update()
{
	_rcPlayer = _player->BoundingBox();



	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		_player->SetX(_player->GetX() - _speed);
		//_player->SetX(_rcPlayer.left - _speed);
		_dirChange = true;
		_player->SetFrameY(1);
		pPos->x -= 3;
		eDir = ePlayerDirection::DIR_PLAYER_LEFT;

	}

	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		_player->SetX(_player->GetX() + _speed);
		//_player->SetX(_rcPlayer.left + _speed);

		_dirChange = false;
		_player->SetFrameY(0);
		pPos->x += 3;

		eDir = ePlayerDirection::DIR_PLAYER_RIGHT;

	}

	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		if (isGround)
		{
			_gravity = 0.9f;
			_jumpPower = 21.5f;
			_isJump = true;
		}
	}

	//_pos.x = _player->GetX();
	//_pos.y = _player->GetY();

	if (_isJump)
	{
		isGround = false;
		_player->SetY(_player->GetY() - _jumpPower);
		_jumpPower -= _gravity;

		if (_player->GetY() >= WINSIZEY - 100)
		{
			_player->SetY(WINSIZEY - 100);

			_gravity = 0;
			isGround = true;
			_isJump = false;
			_isCrash = false;
		}
	}

	CollisionCheck();

	if (_isCrash)
	{
		_crashPower = 10;
		_player->SetX(_player->GetX() - _crashPower * _crashDir);
	}

	_nCount++;

	if (0 == _nCount % 10)
	{
		if (_dirChange)
		{
			if (_iIndex <= 0)
			{
				_iIndex = 5;
			}
			_iIndex--;

			_player->SetFrameX(_iIndex);
		}
		else
		{
			if (_iIndex >= _player->GetMaxFrameX())
			{
				_iIndex = 2;
			}
			_iIndex++;
			_player->SetFrameX(_iIndex);
		}
		_nCount = 0;
	}
}

void Player::Render(HDC hdc)
{
	_player->FrameRender(hdc, pPos->x - CAMERA->GetPosition()->x,
		_player->GetY() - CAMERA->GetPosition()->y,
		_player->GetFrameX(), _player->GetFrameY());
}

void Player::CollisionCheck()
{

	if ((_rcPlayer.left) <= 0)
	{
		_player->SetX(5);
	}

	if ((_rcPlayer.right) >= WINSIZEX)
	{
		_player->SetX(WINSIZEX - _player->GetFrameWidth() - 5);
	}

	_rcPlayer = _player->BoundingBox();

	//GameSystem::GetSingleton()->CrashCharacter(this);
	//_isCrash = true;
}

void Player::CrashObject(int eDirNumber)
{
	if (0 == eDirNumber)
	{
		_gravity = 0.3f;
		_jumpPower = 5.0f;
		_isJump = true;

		_player->SetY(_player->GetY() - _jumpPower);


		_isCrash = true;
		_crashDir = 1;
	}
	else if (1 == eDirNumber)
	{
		_gravity = 0.3f;
		_jumpPower = 5.0f;
		_isJump = true;

		_player->SetY(_player->GetY() - _jumpPower);

		_isCrash = true;
		_crashDir = -1;
	}
}
