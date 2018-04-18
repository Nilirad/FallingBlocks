#pragma once

#include "StateID.h"

class StateStack;
class ApplicationState;

class StateFactory {
public:
	static void init(StateStack* stack);
	static ApplicationState* createState(StateID stateID);

private:
	static StateStack* mStack;
};