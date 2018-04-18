#pragma once

#include <string>

enum LocalizedString {
	STRING_GAME_TITLE,
	STRING_PRESS_ANY_KEY,
	STRING_PLAY,
	STRING_OPTIONS,
	STRING_EXIT,
	STRING_SCORE,
	STRING_LEVEL,
	STRING_LINES,
	STRING_COMBO,
	STRING_NEXT,
	STRING_HOLD,
	STRING_LEVEL_UP,
	STRING_PAUSE,
	STRING_GAME_OVER,
	STRING_GAME_OVER_SCORE,
	STRING_GAME_OVER_ENTER_CHART,
	STRING_GAME_OVER_NOT_ENTER_CHART,
	STRING_ACTION_UP,
	STRING_ACTION_DOWN,
	STRING_ACTION_LEFT,
	STRING_ACTION_RIGHT,
	STRING_ACTION_ROTATE_LEFT,
	STRING_ACTION_ROTATE_RIGHT,
	STRING_ACTION_HOLD,
	STRING_ACTION_LANGUAGE,
	STRING_ACTION_BACK,
	STRING_ACTION_SAVE,

	STRING_COUNT
};

enum Language {
	LANGUAGE_ENGLISH,
	LANGUAGE_ITALIAN,

	LANGUAGE_COUNT
};

class Localization {
public:
	static void init();
	static wchar_t* getString(LocalizedString string);
	static void setLanguage(Language language);
	static void saveToFile();
	static void loadFromFile();

private:
	static void setString(LocalizedString string, Language language, wchar_t* text);
	
	static wchar_t* sStrings[STRING_COUNT * LANGUAGE_COUNT];
	static Language sCurrentLanguage;
};