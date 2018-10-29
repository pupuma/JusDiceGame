#include "Game.h"
#include "StateManager.h"
#include "State.h"

#include "IdleState.h"
#include "AttackState.h"

StateManager::StateManager()
{
	stateType = eStateType::STATE_NONE;

}


StateManager::~StateManager()
{
}

void StateManager::StateInit()
{
	{
		stateType = eStateType::STATE_IDLE;
		State* state = new IdleState();
		m_State[stateType] = state;

	}

	{
		stateType = eStateType::STATE_ATTACK;
		State* state = new AttackState();
		m_State[stateType] = state;

	}

	{
		stateType = eStateType::STATE_MOVE;

	}

	{
		stateType = eStateType::STATE_SUFFER;

	}

	{
		stateType = eStateType::STATE_DIE;

	}

}
