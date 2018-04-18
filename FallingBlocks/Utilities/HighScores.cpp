#include "HighScores.h"
#include <fstream>

int HighScores::mScores[NUM_SCORES];

void HighScores::init() {
	loadFromFile();
}

int HighScores::tryInsertScore(int score) {
	bool insert = false;
	int insertionIndex;
	for (insertionIndex = 0; insertionIndex < NUM_SCORES; insertionIndex++) {
		if (score >= mScores[insertionIndex]) {
			insert = true;
			break;
		}
	}

	if (insert) {
		for (int i = NUM_SCORES - 1; i >= insertionIndex; i--) {
			mScores[i] = mScores[i - 1];
		}
		mScores[insertionIndex] = score;
		saveToFile();
		return insertionIndex + 1;
	}
	return -1;
}

int HighScores::getScore(int position) {
	return mScores[position];
}

void HighScores::loadFromFile() {
	using namespace std;
	streampos size;
	ifstream file("res/hiscores.bin", ios::in | ios::binary | ios::ate);

	if (file.is_open()) {
		size = file.tellg();
		file.seekg(0, ios::beg);
		for (int i = 0; i < NUM_SCORES; i++) {
			int score;
			file.read(reinterpret_cast<char*>(&score), sizeof(score));
			mScores[i] = score;
		}
	}
	else {
		loadDefaultScores();
	}
}

void HighScores::saveToFile() {
	using namespace std;
	ofstream file("res/hiscores.bin", ios::out | ios::binary | ios::trunc);
	if (file.is_open()) {
		for (int i = 0; i < NUM_SCORES; i++) {
			file.write((const char*)(mScores + i), sizeof(int));
		}
	}
}

void HighScores::loadDefaultScores() {
	for (int i = 0; i < NUM_SCORES; i++) {
		mScores[i] = 0;
	}
}

