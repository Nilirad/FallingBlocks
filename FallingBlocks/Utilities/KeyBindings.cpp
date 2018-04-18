#include "KeyBindings.h"
#include <fstream>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  STATIC DATA  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

std::map<UserAction, sf::Keyboard::Key> KeyBindings::mKeyBindings = 
	std::map<UserAction, sf::Keyboard::Key>();



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void KeyBindings::init() {
	loadFromFile();
}

/////////////////////////////////////////////////////////////////////////////////////////

sf::Keyboard::Key KeyBindings::getKey(UserAction action) {
	return mKeyBindings[action];
}

/////////////////////////////////////////////////////////////////////////////////////////

void KeyBindings::setKey(UserAction action, sf::Keyboard::Key key) {
	mKeyBindings[action] = key;
}

/////////////////////////////////////////////////////////////////////////////////////////

void KeyBindings::loadFromFile() {
	using namespace std;
	streampos size;
	ifstream file("res/keybind.bin", ios::in | ios::binary | ios::ate);

	if (file.is_open()) {
		size = file.tellg();
		file.seekg(0, ios::beg);
		char* memblock = new char[size];
		file.read(memblock, size);
		file.close();

		const int keySize = sizeof(sf::Keyboard::Key);
		char keyString[keySize];
		for (int i = 0; i < NUM_ACTIONS; i++) {
			strncpy(keyString, memblock + i * keySize, keySize);
			auto ptr = reinterpret_cast<sf::Keyboard::Key*>(keyString);
			mKeyBindings[(UserAction)i] = *ptr;
		}
		delete memblock;
	}
	else {
		loadDefaultKeys();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void KeyBindings::saveToFile() {
	using namespace std;
	ofstream file("res/keybind.bin", ios::out | ios::binary | ios::trunc);
	if (file.is_open()) {
		for each (auto pair in mKeyBindings) {
			file.write((const char*)(&pair.second), sizeof(sf::Keyboard::Key));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void KeyBindings::loadDefaultKeys() {
	mKeyBindings[ACTION_MOVE_UP] = sf::Keyboard::W;
	mKeyBindings[ACTION_MOVE_DOWN] = sf::Keyboard::S;
	mKeyBindings[ACTION_MOVE_LEFT] = sf::Keyboard::A;
	mKeyBindings[ACTION_MOVE_RIGHT] = sf::Keyboard::D;
	mKeyBindings[ACTION_ROTATE_LEFT] = sf::Keyboard::Left;
	mKeyBindings[ACTION_ROTATE_RIGHT] = sf::Keyboard::Right;
	mKeyBindings[ACTION_HOLD] = sf::Keyboard::Space;
	mKeyBindings[ACTION_CONFIRM] = sf::Keyboard::Return;
	mKeyBindings[ACTION_CANCEL] = sf::Keyboard::Escape;
}
