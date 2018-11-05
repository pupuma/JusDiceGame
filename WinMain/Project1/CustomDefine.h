#pragma once

// 사용자 정의 자료형
enum OBJ_TYPE
{
	ELLIPSE = 0,
	RECTANGLE,
	ROUNDRECT
};

enum DS_STATE
{
	DS_LEFT = -1,
	DS_NONE,
	DS_RIGHT,
};


struct SPERE
{
	float x, y;
	float r;
};

enum eDiceColor
{
	DICE_BLUE,
	DICE_RED,
	DICE_GREEN,
	DICE_YELLOW,
	DICE_GRAY,
	DICE_BLACK,
	DICE_NONE,

};

enum eEnemyType
{
	ENEMY_NONE,
	ENEMY_BOSS,
};


struct tagChainInfo
{
	bool chainAcitve;
	POINT pt;
};


typedef enum eButtom
{
	DCBUTTONDIR_NONE,
	DCBUTTONDIR_UP,
	DCBUTTONDIR_DOWN,

}eDCButtom;

typedef enum eGameState
{
	GAMESTATE_IDLE,
	GAMESTATE_START,
	GAMESTATE_DIE,
	GAMESTATE_STOP,
	GAMESTATE_NONE,

}eGState;


// Extern
extern HWND			_hWnd;
extern HINSTANCE	_hInst;
extern POINT		_ptMouse;
extern POINT		_ptSave;