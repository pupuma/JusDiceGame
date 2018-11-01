#pragma once


enum eStateType
{
	STATE_NONE,
	STATE_IDLE,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_SUFFER,
	STATE_DIE,
};


enum eStateAbnormal
{
	SA_SlOW,
	SA_POISON,
	SA_DIE,
	SA_NONE,
};
