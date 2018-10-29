#pragma once

#include "State.h"


class IdleState
	: public State
{
public:
	IdleState();
	~IdleState();
public:
	void Start();
	void Stop();
	void Update();
};

