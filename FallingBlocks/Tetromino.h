#pragma once

#include "Point.h"
#include <SFML\Graphics\Color.hpp>

const int TETROMINO_SIZE = 4;
const int NUM_TETROMINO_TYPES = 7;
const int NUM_ROTATIONS = 4;
const int NUM_KICK_TESTS = 5;

enum TetrominoType { J, L, S, T, Z, I, O };
enum RotationState { ZERO, RIGHT, TWO, LEFT };
enum RotateDirection { CLOCKWISE, COUNTERCLOCKWISE };

class Tetromino {
public:
	/// \brief Default constructor.
	Tetromino();

	/// \brief Constructor that takes the type of the tetromino that will be created.
	Tetromino(TetrominoType type);

	/// \brief Moves the tetromino by the specified offset.
	void move(int x, int y);

	/// \brief Rotates the tetromino to the target rotation.
	/// \param offset How much to move the tetromino while rotating.
	void rotate(RotationState target, Point offset);
	
	/// \brief Gets the next rotation state given the rotation direction.
	RotationState getTargetRotationState(RotateDirection direction);

	/// \brief Calculates the kick offsets of the current tetromino given the rotate
	///        direction.
	/// \param dest Array to put information in.
	void calculateKickOffsets(RotateDirection direction, Point* dest);

	/// \brief Gets the type of the current tetromino.
	TetrominoType getType();

	/// \brief Gets the position of the current tetromino.
	Point getPosition();

	/// \brief Sets the position of the current tetromino.
	void setPosition(Point position);

	/// \brief Gets the pointer to the positions of the blocks of the current rotation
	///        of the current tetromino.
	Point const* getBlockPositions();

	/// \brief Gets the pointer to the positions of the blocks of the specified
	///        rotation of the current tetromino.
	Point const* getBlockPositions(RotationState rotation);

	/// \brief Sets the pointer to the block positions based on the specified rotation.
	void setBlockPositions(RotationState rotation);

	/// \brief Gets the rotation of the current tetromino.
	RotationState getRotation();

	/// \brief Sets the rotation of the current tetromino.
	void setRotation(RotationState rotation);

	/// \brief Gets the color of the tetromino based on its type.
	sf::Color getColor();

private:
	TetrominoType mType; ///< The shape of the tetromino.
	Point mPosition; ///< The position of the center of the tetromino.
	RotationState mRotation; ///< The rotation state of the tetromino
	Point const* mBlockPositions; ///< The pointer to the positions of the blocks.
	Point const* mOffsetData; ///< The pointer to the kick offset data.

	static const Point OFFSET_DATA_NORMAL[NUM_ROTATIONS * NUM_KICK_TESTS];
	///< The offset data for the J, L, S, T, Z tetrominos.

	static const Point OFFSET_DATA_I[NUM_ROTATIONS * NUM_KICK_TESTS];
	///< The offset data for the I tetromino.

	static const Point OFFSET_DATA_O[NUM_ROTATIONS * NUM_KICK_TESTS];
	///< The offset data for the O tetromino.

	static const Point BLOCK_POSITIONS_J[TETROMINO_SIZE * NUM_ROTATIONS];
	///< The block positions for every rotation state of the J tetromino.

	static const Point BLOCK_POSITIONS_L[TETROMINO_SIZE * NUM_ROTATIONS];
	///< The block positions for every rotation state of the L tetromino.

	static const Point BLOCK_POSITIONS_S[TETROMINO_SIZE * NUM_ROTATIONS];
	///< The block positions for every rotation state of the S tetromino.

	static const Point BLOCK_POSITIONS_T[TETROMINO_SIZE * NUM_ROTATIONS];
	///< The block positions for every rotation state of the T tetromino.

	static const Point BLOCK_POSITIONS_Z[TETROMINO_SIZE * NUM_ROTATIONS];
	///< The block positions for every rotation state of the Z tetromino.

	static const Point BLOCK_POSITIONS_I[TETROMINO_SIZE * NUM_ROTATIONS];
	///< The block positions for every rotation state of the I tetromino.

	static const Point BLOCK_POSITIONS_O[TETROMINO_SIZE * NUM_ROTATIONS];
	///< The block positions for every rotation state of the O tetromino.
	
	static Point const* getBlockPositions(TetrominoType type);
	///< Gets the base pointer to the block positions of the specified tetromino type.

	static Point const* getOffsetData(TetrominoType type);
	///< Gets the base pointer to the offset data of the specified tetromino type.
};
