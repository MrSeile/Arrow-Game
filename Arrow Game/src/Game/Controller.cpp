#include "Controller.h"

Controller::Controller()
{
	m_state = State::Menu;
	level = 0;
}

void Controller::SetState(const State& newState/*, UserInterface& UI*/)
{
	m_state = newState;
	//UI.BeginPlay(*this);
}

const State& Controller::GetState()
{
	return m_state;
}
