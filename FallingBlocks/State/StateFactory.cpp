#include "StateFactory.h"
#include "TitleScreenState.h"
#include "MainMenuState.h"
#include "OptionsState.h"
#include "PlayingState.h"
#include "PauseState.h"

StateStack* StateFactory::mStack;

void StateFactory::init(StateStack* stack) {
	mStack = stack;
}

ApplicationState* StateFactory::createState(StateID stateID) {
	switch (stateID)
	{
	case TITLE_SCREEN_STATE:
		return new TitleScreenState(mStack);
	case MAIN_MENU_STATE:
		return new MainMenuState(mStack);
	case OPTIONS_STATE:
		return new OptionsState(mStack);
	case PLAYING_STATE:
		return new PlayingState(mStack);
	case PAUSE_STATE:
		return new PauseState(mStack);
	default:
		return nullptr;
	}
}
