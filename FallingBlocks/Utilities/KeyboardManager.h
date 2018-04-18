#pragma once

#include <SFML/Window/Keyboard.hpp>

namespace sf {
	class String;
}

class KeyboardManager {
public:
	/// \brief Initialize the class.
	static void init();

	/// \brief Checks if the keys are pressed.
	static void checkKeyPresses();

	/// \brief Checks if a key is pressed or repeated.
	static bool isKeyPressed(sf::Keyboard::Key key, int firstRepeatDelay, int repeatDelay);

	/// \brief Checks if a key is pressed.
	static bool isKeyPressedSingle(sf::Keyboard::Key key);

	static sf::String getKeyName(sf::Keyboard::Key key);

	static sf::Keyboard::Key getKey();

	static void resetKeyDelay(sf::Keyboard::Key key);

	static void lockKeys();

private:
	static int mKeyHolds[(int)sf::Keyboard::KeyCount]; ///< Table of held keys.
};