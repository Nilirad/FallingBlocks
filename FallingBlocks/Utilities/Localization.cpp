#include "Localization.h"
#include <fstream>

wchar_t* Localization::sStrings[STRING_COUNT * LANGUAGE_COUNT];
Language Localization::sCurrentLanguage;

void Localization::init() {
	loadFromFile();
	
	setString(STRING_GAME_TITLE, LANGUAGE_ENGLISH, L"Falling Blocks");
	setString(STRING_PRESS_ANY_KEY, LANGUAGE_ENGLISH, L"Press any key");
	setString(STRING_PLAY, LANGUAGE_ENGLISH, L"Play");
	setString(STRING_OPTIONS, LANGUAGE_ENGLISH, L"Options");
	setString(STRING_EXIT, LANGUAGE_ENGLISH, L"Exit");
	setString(STRING_SCORE, LANGUAGE_ENGLISH, L"Score: ");
	setString(STRING_LEVEL, LANGUAGE_ENGLISH, L"Level: ");
	setString(STRING_LINES, LANGUAGE_ENGLISH, L"Lines: ");
	setString(STRING_COMBO, LANGUAGE_ENGLISH, L" Combo!");
	setString(STRING_NEXT, LANGUAGE_ENGLISH, L"Next");
	setString(STRING_HOLD, LANGUAGE_ENGLISH, L"Hold");
	setString(STRING_LEVEL_UP, LANGUAGE_ENGLISH, L"Level Up!");
	setString(STRING_PAUSE, LANGUAGE_ENGLISH, L"PAUSE");
	setString(STRING_GAME_OVER, LANGUAGE_ENGLISH, L"Game Over");
	setString(STRING_GAME_OVER_SCORE, LANGUAGE_ENGLISH, L"Your score is ");
	setString(STRING_GAME_OVER_ENTER_CHART, LANGUAGE_ENGLISH, L"and your chart position is ");
	setString(STRING_GAME_OVER_NOT_ENTER_CHART, LANGUAGE_ENGLISH, L"but you don't get into the chart...");
	setString(STRING_ACTION_UP, LANGUAGE_ENGLISH, L"Up");
	setString(STRING_ACTION_DOWN, LANGUAGE_ENGLISH, L"Down");
	setString(STRING_ACTION_LEFT, LANGUAGE_ENGLISH, L"Left");
	setString(STRING_ACTION_RIGHT, LANGUAGE_ENGLISH, L"Right");
	setString(STRING_ACTION_ROTATE_LEFT, LANGUAGE_ENGLISH, L"Rotate counterclockwise");
	setString(STRING_ACTION_ROTATE_RIGHT, LANGUAGE_ENGLISH, L"Rotate clockwise");
	setString(STRING_ACTION_HOLD, LANGUAGE_ENGLISH, L"Hold");
	setString(STRING_ACTION_LANGUAGE, LANGUAGE_ENGLISH, L"Language");
	setString(STRING_ACTION_BACK, LANGUAGE_ENGLISH, L"Back");
	setString(STRING_ACTION_SAVE, LANGUAGE_ENGLISH, L"Save");

	setString(STRING_GAME_TITLE, LANGUAGE_ITALIAN, L"Falling Blocks");
	setString(STRING_PRESS_ANY_KEY, LANGUAGE_ITALIAN, L"Premi un tasto qualsiasi");
	setString(STRING_PLAY, LANGUAGE_ITALIAN, L"Gioca");
	setString(STRING_OPTIONS, LANGUAGE_ITALIAN, L"Opzioni");
	setString(STRING_EXIT, LANGUAGE_ITALIAN, L"Esci");
	setString(STRING_SCORE, LANGUAGE_ITALIAN, L"Punti: ");
	setString(STRING_LEVEL, LANGUAGE_ITALIAN, L"Livello: ");
	setString(STRING_LINES, LANGUAGE_ITALIAN, L"Linee: ");
	setString(STRING_COMBO, LANGUAGE_ITALIAN, L" Combo!");
	setString(STRING_NEXT, LANGUAGE_ITALIAN, L"Prossimo");
	setString(STRING_HOLD, LANGUAGE_ITALIAN, L"Riserva");
	setString(STRING_LEVEL_UP, LANGUAGE_ITALIAN, L"Nuovo Livello!");
	setString(STRING_PAUSE, LANGUAGE_ITALIAN, L"PAUSA");
	setString(STRING_GAME_OVER, LANGUAGE_ITALIAN, L"Game Over");
	setString(STRING_GAME_OVER_SCORE, LANGUAGE_ITALIAN, L"Il tuo punteggio è ");
	setString(STRING_GAME_OVER_ENTER_CHART, LANGUAGE_ITALIAN, L"e la tua posizione in classifica è ");
	setString(STRING_GAME_OVER_NOT_ENTER_CHART, LANGUAGE_ITALIAN, L"ma non entri in classifica...");
	setString(STRING_ACTION_UP, LANGUAGE_ITALIAN, L"Su");
	setString(STRING_ACTION_DOWN, LANGUAGE_ITALIAN, L"Giù");
	setString(STRING_ACTION_LEFT, LANGUAGE_ITALIAN, L"Sinistra");
	setString(STRING_ACTION_RIGHT, LANGUAGE_ITALIAN, L"Destra");
	setString(STRING_ACTION_ROTATE_LEFT, LANGUAGE_ITALIAN, L"Rotazione antioraria");
	setString(STRING_ACTION_ROTATE_RIGHT, LANGUAGE_ITALIAN, L"Rotazione oraria");
	setString(STRING_ACTION_HOLD, LANGUAGE_ITALIAN, L"Riserva");
	setString(STRING_ACTION_LANGUAGE, LANGUAGE_ITALIAN, L"Lingua");
	setString(STRING_ACTION_BACK, LANGUAGE_ITALIAN, L"Indietro");
	setString(STRING_ACTION_SAVE, LANGUAGE_ITALIAN, L"Salva");
}

wchar_t* Localization::getString(LocalizedString string) {
	return sStrings[sCurrentLanguage * STRING_COUNT + string];
}

void Localization::setLanguage(Language language) {
	sCurrentLanguage = language;
}

void Localization::saveToFile() {
	using namespace std;
	ofstream file("res/language.bin", ios::out | ios::binary | ios::trunc);
	if (file.is_open()) {
		file.write((const char*)(&sCurrentLanguage), sizeof(Language));
	}
}

void Localization::loadFromFile() {
	using namespace std;
	streampos size;
	ifstream file("res/language.bin", ios::in | ios::binary | ios::ate);

	if (file.is_open()) {
		size = file.tellg();
		file.seekg(0, ios::beg);
		file.read(reinterpret_cast<char*>(&sCurrentLanguage), sizeof(Language));
		file.close();
	}
	else {
		sCurrentLanguage = LANGUAGE_ENGLISH;
	}
}

void Localization::setString(LocalizedString string, Language language, wchar_t* text) {
	sStrings[language * STRING_COUNT + string] = text;
}
