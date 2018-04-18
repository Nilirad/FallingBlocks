#include "CommandMenuItem.h"
#include "../Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>


CommandMenuItem::CommandMenuItem()
	: mText()
	, mCommand()
{
}

CommandMenuItem::CommandMenuItem(const wchar_t* text, sf::Vector2f position, CommandID command)
	: mText()
	, mCommand(command)
{
	mText.setFont(Constants::font);
	mText.setFillColor(sf::Color::White);
	mText.setCharacterSize(20);
	mText.setString(text);
	mText.setPosition(position);
}

void CommandMenuItem::select() {
	mText.setFillColor(sf::Color::Red);
}

void CommandMenuItem::unselect() {
	mText.setFillColor(sf::Color::White);
}

void CommandMenuItem::draw(sf::RenderWindow* window) {
	window->draw(mText);
}

void CommandMenuItem::handleInput()
{
}

MenuItemType CommandMenuItem::getType() {
	return ITEM_COMMAND;
}

void CommandMenuItem::execute() {
	Command::execute(mCommand);
}

bool CommandMenuItem::isActive() {
	return false;
}
