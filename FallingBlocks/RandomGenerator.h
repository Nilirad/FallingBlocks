#pragma once

#include "Tetromino.h"
#include <random>

class RandomGenerator {
public:
	///< Default constructor.
	RandomGenerator();

	///< Gets the next random tetromino.
	Tetromino next();

private:
	void shuffle(); ///< Performs a random permutation of the bag.

	std::default_random_engine mGenerator; ///< The random number generator.
	int mIndex; ///< The position of the next element to be picked up from the bag.
	TetrominoType mBag[NUM_TETROMINO_TYPES]; ///< The bag containing all the seven unique tetrominoes.
};