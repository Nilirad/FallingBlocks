#include "MenuSelector.h"
#include "KeyboardManager.h"
#include "KeyBindings.h"
#include "AudioManager.h"
#include "MenuItemFactory.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

MenuSelector::MenuSelector()
	: mItems()
	, mSelected(0)
	, mPositionY(35)
{
}

/////////////////////////////////////////////////////////////////////////////////////////

MenuSelector::~MenuSelector() {
	for each (MenuItem* item in mItems) {
		delete item;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void MenuSelector::start() {
	mItems[0]->select();
}

/////////////////////////////////////////////////////////////////////////////////////////

void MenuSelector::handleInput() {
	for each (MenuItem* item in mItems) {
		item->handleInput();
	}

	if (!mItems[mSelected]->isActive()) {
		if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_MOVE_UP))) {
			AudioManager::playSound(SOUND_MENU_MOVE);
			mItems[mSelected]->unselect();
			mSelected -= 1;
			if (mSelected < 0) {
				mSelected = mItems.size() - 1;
			}
			mItems[mSelected]->select();
		}
		if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_MOVE_DOWN))) {
			AudioManager::playSound(SOUND_MENU_MOVE);
			mItems[mSelected]->unselect();
			mSelected += 1;
			if (mSelected >= mItems.size()) {
				mSelected = 0;
			}
			mItems[mSelected]->select();
		}
		if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_CONFIRM))) {
			AudioManager::playSound(SOUND_CONFIRM);
			mItems[mSelected]->execute();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void MenuSelector::draw(sf::RenderWindow* window) {
	for each (MenuItem* item in mItems) {
		item->draw(window);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void MenuSelector::addMenuItem(MenuItem* item) {
	mItems.push_back(item);
}

void MenuSelector::addStateChangerMenuItem(const wchar_t* text, StateID targetState, bool popsState) {
	MenuItem* item = MenuItemFactory::createStateChangerMenuItem(text, sf::Vector2f(20, mPositionY), targetState, popsState);
	mItems.push_back(item);
	mPositionY += 25;
}

void MenuSelector::addKeyBindMenuItem(const wchar_t* text, UserAction action) {
	MenuItem* item = MenuItemFactory::createKeyBindMenuItem(text, sf::Vector2f(20, mPositionY), action);
	mItems.push_back(item);
	mPositionY += 25;
}

void MenuSelector::addCommandMenuItem(const wchar_t* text, CommandID commandID) {
	MenuItem* item = MenuItemFactory::createCommandMenuItem(text, sf::Vector2f(20, mPositionY), commandID);
	mItems.push_back(item);
	mPositionY += 25;
}

void MenuSelector::addSwitchMenuItem(const wchar_t* text, SwitchID switchID) {
	MenuItem* item = MenuItemFactory::createSwitchMenuItem(text, sf::Vector2f(20, mPositionY), switchID);
	mItems.push_back(item);
	mPositionY += 25;
}

void MenuSelector::addSpace() {
	mPositionY += 5;
}

/////////////////////////////////////////////////////////////////////////////////////////

MenuItem* MenuSelector::getSelectedItem() {
	return mItems[mSelected];
}
