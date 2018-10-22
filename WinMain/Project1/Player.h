#pragma once

enum ePlayerDirection
{
	DIR_PLAYER_LEFT,
	DIR_PLAYER_RIGHT,
};

class Player
{
private:
	Image*	_player;
	RECT _rcPlayer;
	ePlayerDirection eDir;
	int		_nCount;
	int		_iIndex;
	bool _dirChange;
	POINT* pPos;

private:
	float _gravity;
	float _jumpPower;
	float _crashPower;
	float _speed;
	int _crashDir;

	bool isGround;
	bool _isJump;
	bool _isCrash;
public:
	Player();
	~Player();
public:
	void Update();
	void Render(HDC hdc);
public:
	void SetPos(POINT* p) { pPos = p; }
	POINT* GetPos() { return pPos; }
public:
	void CollisionCheck();
	void CrashObject(int eDirNumber);
	RECT GetRectPlayer() { return _rcPlayer; }
	Image* GetImage() { return _player; }
};

