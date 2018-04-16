#include "Controller.h"

Controller::Controller()
{
	m_state = State::Menu;
	level = 0;
}

void Controller::SetState(const State& newState)
{
	m_state = newState;
}

const State& Controller::GetState()
{
	return m_state;
}
