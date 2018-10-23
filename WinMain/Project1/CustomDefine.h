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

// Extern
extern HWND			_hWnd;
extern HINSTANCE	_hInst;
extern POINT		_ptMouse;
extern POINT		_ptSave;