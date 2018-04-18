#include <cassert>
#include "Tetromino.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  STATIC DATA  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


// columns: kick test offsets (test 1, test 2, test 3, test 4, test 5)
const Point Tetromino::OFFSET_DATA_NORMAL[NUM_ROTATIONS * NUM_KICK_TESTS] = {
	Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 },      // 0
	Point{ 0, 0 }, Point{ 1, 0 }, Point{ 1, -1 }, Point{ 0, 2 }, Point{ 1, 2 },     // R
	Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 },      // 2
	Point{ 0, 0 }, Point{ -1, 0 }, Point{ -1, -1 }, Point{ 0, 2 }, Point{ -1, 2 },  // L
};

const Point Tetromino::OFFSET_DATA_I[NUM_ROTATIONS * NUM_KICK_TESTS] = {
	Point{ 0, 0 }, Point{ -1, 0 }, Point{ 2, 0 }, Point{ -1, 0 }, Point{ 2, 0 },	// 0
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 1 }, Point{ 0, -2 },	// R
	Point{ -1, 1 }, Point{ 1, 1 }, Point{ -2, 1 }, Point{ 1, 0 }, Point{ -2, 0 },	// 2
	Point{ 0, 1 }, Point{ 0, 1 }, Point{ 0, 1 }, Point{ 0, -1 }, Point{ 0, 2 },		// L
};

const Point Tetromino::OFFSET_DATA_O[NUM_ROTATIONS * NUM_KICK_TESTS] = {
	Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 }, Point{ 0, 0 },			  // 0
	Point{ 0, -1 }, Point{ 0, -1 }, Point{ 0, -1 }, Point{ 0, -1 }, Point{ 0, -1 },		  // R
	Point{ -1, -1 }, Point{ -1, -1 }, Point{ -1, -1 }, Point{ -1, -1 }, Point{ -1, -1 },  // 2
	Point{ -1, 0 }, Point{ -1, 0 }, Point{ -1, 0 }, Point{ -1, 0 }, Point{ -1, 0 },		  // L
};

const Point Tetromino::BLOCK_POSITIONS_J[TETROMINO_SIZE * NUM_ROTATIONS] = {
	Point{ -1, 1 }, Point{ -1, 0 }, Point{ 0, 0 }, Point{ 1, 0 },             // 0
	Point{ 1, 1 }, Point{ 0, 1 }, Point{ 0, 0 }, Point{ 0, -1 },              // R
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ 1, 0 }, Point{ 1, -1 },             // 2
	Point{ 0, 1 }, Point{ 0, 0 }, Point{ 0, -1 }, Point{ -1, -1 }             // L
};

const Point Tetromino::BLOCK_POSITIONS_L[TETROMINO_SIZE * NUM_ROTATIONS] = {
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ 1, 0 }, Point{ 1, 1 },              // 0
	Point{ 0, 1 }, Point{ 0, 0 }, Point{ 0, -1 }, Point{ 1, -1 },			  // R
	Point{ -1, -1 }, Point{ -1, 0 }, Point{ 0, 0 }, Point{ 1, 0 },			  // 2
	Point{ -1, 1 }, Point{ 0, 1 }, Point{ 0, 0 }, Point{ 0, -1 }			  // L
};

const Point Tetromino::BLOCK_POSITIONS_S[TETROMINO_SIZE * NUM_ROTATIONS] = {
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 1 },			  // 0
	Point{ 0, 1 }, Point{ 0, 0 }, Point{ 1, 0 }, Point{ 1, -1 },			  // R
	Point{ -1, -1 }, Point{ 0, -1 }, Point{ 0, 0 }, Point{ 1, 0 },			  // 2
	Point{ -1, 1 }, Point{ -1, 0 }, Point{ 0, 0 }, Point{ 0, -1 }			  // L
};

const Point Tetromino::BLOCK_POSITIONS_T[TETROMINO_SIZE * NUM_ROTATIONS] = {
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ 1, 0 }, Point{ 0, 1 },			  // 0
	Point{ 0, 1 }, Point{ 0, 0 }, Point{ 0, -1 }, Point{ 1, 0 },			  // R
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ 1, 0 }, Point{ 0, -1 },			  // 2
	Point{ 0, 1 }, Point{ 0, 0 }, Point{ 0, -1 }, Point{ -1, 0 }			  // L
};

const Point Tetromino::BLOCK_POSITIONS_Z[TETROMINO_SIZE * NUM_ROTATIONS] = {
	Point{ -1, 1 }, Point{ 0, 1 }, Point{ 0, 0 }, Point{ 1, 0 },			  // 0
	Point{ 1, 1 }, Point{ 1, 0 }, Point{ 0, 0 }, Point{ 0, -1 },			  // R
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ 0, -1 }, Point{ 1, -1 },			  // 2
	Point{ 0, 1 }, Point{ 0, 0 }, Point{ -1, 0 }, Point{ -1, -1 },			  // L
};

const Point Tetromino::BLOCK_POSITIONS_I[TETROMINO_SIZE * NUM_ROTATIONS] = {
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ 1, 0 }, Point{ 2, 0 },              // 0
	Point{ 0, 1 }, Point{ 0, 0 }, Point{ 0, -1 }, Point{ 0, -2 },			  // R
	Point{ -2, 0 }, Point{ -1, 0 }, Point{ 0, 0 }, Point{ 1, 0 },			  // 2
	Point{ 0, 2 }, Point{ 0, 1 }, Point{ 0, 0 }, Point{ 0, -1 }				  // L
};

const Point Tetromino::BLOCK_POSITIONS_O[TETROMINO_SIZE * NUM_ROTATIONS] = {
	Point{ 0, 0 }, Point{ 1, 0 }, Point{ 0, 1 }, Point{ 1, 1 },				  // 0
	Point{ 0, 0 }, Point{ 1, 0 }, Point{ 0, -1 }, Point{ 1, -1 },			  // R
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ -1, -1 }, Point{ 0, -1 },			  // 2
	Point{ -1, 0 }, Point{ 0, 0 }, Point{ -1, 1 }, Point{ 0, 1 }			  // L
};



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

Tetromino::Tetromino() {
}

/////////////////////////////////////////////////////////////////////////////////////////

Tetromino::Tetromino(TetrominoType type) {
	mType = type;
	mPosition = Point{ 0, 0 };
	mRotation = RotationState::ZERO;
	mBlockPositions = getBlockPositions(type);
	mOffsetData = getOffsetData(type);
}

/////////////////////////////////////////////////////////////////////////////////////////

void Tetromino::move(int x, int y) {
	mPosition.x += x;
	mPosition.y += y;
}

/////////////////////////////////////////////////////////////////////////////////////////

void Tetromino::rotate(RotationState target, Point offset) {
	move(offset.x, offset.y);
	setBlockPositions(target);
	mRotation = target;
}

/////////////////////////////////////////////////////////////////////////////////////////

void Tetromino::calculateKickOffsets(RotateDirection direction, Point* dest) {
	RotationState target = getTargetRotationState(direction);
	
	Point const* currentOffsets = mOffsetData + (int)mRotation * NUM_KICK_TESTS;
	Point const* targetOffsets = mOffsetData + (int)target * NUM_KICK_TESTS;


	for (int i = 0; i < NUM_KICK_TESTS; i++) {
		dest[i].x = currentOffsets[i].x - targetOffsets[i].x;
		dest[i].y = currentOffsets[i].y - targetOffsets[i].y;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

TetrominoType Tetromino::getType() {
	return mType;
}

/////////////////////////////////////////////////////////////////////////////////////////

Point Tetromino::getPosition() {
	return mPosition;
}

/////////////////////////////////////////////////////////////////////////////////////////

void Tetromino::setPosition(Point position) {
	mPosition = position;
}

/////////////////////////////////////////////////////////////////////////////////////////

Point const* Tetromino::getBlockPositions() {
	return mBlockPositions;
}

/////////////////////////////////////////////////////////////////////////////////////////

Point const* Tetromino::getBlockPositions(RotationState rotation) {
	Point const* base = getBlockPositions(mType) + TETROMINO_SIZE * (int)rotation;
	return base;
}

/////////////////////////////////////////////////////////////////////////////////////////

void Tetromino::setBlockPositions(RotationState rotation) {
	mBlockPositions = getBlockPositions(mType) + (int)rotation * TETROMINO_SIZE;
	assert(mBlockPositions >= getBlockPositions(mType));
	assert(mBlockPositions < getBlockPositions(mType) + TETROMINO_SIZE * NUM_ROTATIONS);
}

/////////////////////////////////////////////////////////////////////////////////////////

RotationState Tetromino::getRotation() {
	return mRotation;
}

/////////////////////////////////////////////////////////////////////////////////////////

void Tetromino::setRotation(RotationState rotation) {
	mRotation = rotation;
}

sf::Color Tetromino::getColor()
{
	switch (mType)
	{
	case J:
		return sf::Color(0, 64, 255); // Blue(ish)
	case L:
		return sf::Color(255, 69, 0); // Orange
	case S:
		return sf::Color::Green;
	case T:
		return sf::Color(128, 0, 128); // Purple
	case Z:
		return sf::Color::Red;
	case I:
		return sf::Color::Cyan;
	case O:
		return sf::Color::Yellow;
	default:
		throw;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

RotationState Tetromino::getTargetRotationState(RotateDirection direction) {
	int targetRotation;
	switch (direction) {
	case CLOCKWISE:
		targetRotation = ((int)mRotation + 1) % NUM_ROTATIONS;
		break;
	case COUNTERCLOCKWISE:
		targetRotation = (int)mRotation - 1;
		if (targetRotation == -1) {
			targetRotation = NUM_ROTATIONS - 1;
		}
		break;
	default:
		break;
	}
	return (RotationState)targetRotation;
}

/////////////////////////////////////////////////////////////////////////////////////////

Point const* Tetromino::getBlockPositions(TetrominoType type) {
	switch (type) {
	case J:
		return BLOCK_POSITIONS_J;
	case L:
		return BLOCK_POSITIONS_L;
	case S:
		return BLOCK_POSITIONS_S;
	case T:
		return BLOCK_POSITIONS_T;
	case Z:
		return BLOCK_POSITIONS_Z;
	case I:
		return BLOCK_POSITIONS_I;
	case O:
		return BLOCK_POSITIONS_O;
	default:
		throw;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

Point const* Tetromino::getOffsetData(TetrominoType type) {
	switch (type) {
	case J:
	case L:
	case S:
	case T:
	case Z:
		return OFFSET_DATA_NORMAL;
	case I:
		return OFFSET_DATA_I;
	case O:
		return OFFSET_DATA_O;
	default:
		throw;
	}
}
