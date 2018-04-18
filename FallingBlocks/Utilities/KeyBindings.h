#pragma once

#include "UserAction.h"
#include <SFML/Window/Keyboard.hpp>
#include <map>


class KeyBindings {
public:
	/// \brief Initialize the static member data of the class.
	static void init();

	/// \brief Gets the bounded key to the specified action.
	static sf::Keyboard::Key getKey(UserAction action);

	static void setKey(UserAction action, sf::Keyboard::Key key);

	/// \brief Loads the key bindings from the res/keybind.bin file.
	static void loadFromFile();

	/// \brief Saves the current key bindings to the res/keybind.bin file.
	static void saveToFile();

private:
	/// \brief Loads the default key bindings.
	static void loadDefaultKeys();
	
	static std::map<UserAction, sf::Keyboard::Key> mKeyBindings; ///< The association map defining
	                                                             ///< the key bindings.
};