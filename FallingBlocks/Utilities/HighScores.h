#pragma once

const int NUM_SCORES = 10;

class HighScores {
public:
	static void init();

	static int tryInsertScore(int score);

	static int getScore(int position);

private:
	static void loadFromFile();

	static void saveToFile();

	static void loadDefaultScores();

	static int mScores[NUM_SCORES];
};