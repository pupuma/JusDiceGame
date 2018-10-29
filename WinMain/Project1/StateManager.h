#pragma once

class State;
class StateManager 
	: public SingletonBase<StateManager>
{
private:
	eStateType stateType;
	std::map<eStateType, State*> m_State;
public:
	StateManager();
	~StateManager();
public:
	void StateInit();
};

