#include "RandomGenerator.h"
#include <cassert>
#include <chrono>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

RandomGenerator::RandomGenerator()
	: mGenerator(std::chrono::system_clock::now().time_since_epoch().count())
{
	mIndex = 0;

	for (int i = 0; i < NUM_TETROMINO_TYPES; i++) {
		mBag[i] = (TetrominoType)i;
	}

	srand(0);
	shuffle();
}

/////////////////////////////////////////////////////////////////////////////////////////

Tetromino RandomGenerator::next() {
	if (mIndex == NUM_TETROMINO_TYPES) { // We've past the last element
		shuffle();
		mIndex = 0;
	}
	Tetromino next = Tetromino(mBag[mIndex]);
	mIndex += 1;
	return next;
}

/////////////////////////////////////////////////////////////////////////////////////////

void RandomGenerator::shuffle() {
	for (int i = 0; i < NUM_TETROMINO_TYPES - 1; i++) {
		std::uniform_int_distribution<int> distribution(i, NUM_TETROMINO_TYPES - 1);
		int j = distribution(mGenerator);
		
		assert(j >= i);
		assert(j < NUM_TETROMINO_TYPES);
		
		TetrominoType tmp = mBag[i];
		mBag[i] = mBag[j];
		mBag[j] = tmp;
		assert(true);
	}
}
