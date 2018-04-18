#pragma once

#include "../RandomGenerator.h"
#include "../Constants.h"
#include "ApplicationState.h"
#include "../Utilities/Option.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

const int BLOCK_OUTLINE = -2; ///< Thickness of the block outline.
const int FALLING_FRAMES = 30; ///< The number of frames to make the current piece fall of one block.
const int LINES_PER_LEVEL = 10; ///< The lines needed to level up.
const float LEVEL_UP_FACTOR = 0.5; ///< The factor by how much speed grows for each level.
const Point SPAWN_POSITION = Point{ (PLAYFIELD_WIDTH - 1) / 2, PLAYFIELD_HEIGHT - 2 };
///< The spawn position of the falling piece.

enum PlayState { FALLING, LANDING, ARE, TOP_OUT }; ///< The possible states for a play.
enum BlockState { EMPTY, BLUE, ORANGE, GREEN, PURPLE, RED, CYAN, YELLOW };
///< The possible states for a block in the playfield


class PlayingState : public ApplicationState {
public:
	/// \brief The constructor.
	PlayingState(StateStack* stack);
	
	// ApplicationState virtual functions
	virtual void start();
	virtual void handleInput();
	virtual void update(sf::Time dt);
	virtual void render(sf::RenderWindow* window);

private:
	RandomGenerator mRandomGenerator; ///< The random generator for the tetrominoes.
	BlockState mBlockStack[PLAYFIELD_WIDTH * PLAYFIELD_HEIGHT];
	///< States, for each position in the playfield, if the position is occupied or not.
	Tetromino mFallingPiece; ///< The current controllable piece.
	Tetromino mNextPiece; ///< The next controllable piece.
	Option<Tetromino> mHeldPiece; ///< The held piece.
	PlayState mState; ///< The state for the current play.
	bool mJustMadeHoldAction; ///< Tracks if holding or unholding has been done before any landing.
	int mFallingTimer; ///< Counts up until the falling piece must decrease its position.
	int mTotalLines; ///< Tracks the total lines made for the current play.
	int mLevel; ///< Tracks the current level.
	int mComboCounter; ///< The combo counter.
	int mScore; ///< Tracks the current score.
	int mLevelUpTimer;
	bool mIsComboTextVisible;
	sf::Text mScoreText; ///< The text to show the score.
	sf::Text mLevelText;
	sf::Text mLinesText;
	sf::Text mComboText;
	sf::Text mNextText;
	sf::Text mHoldText;
	sf::Text mLevelUpText;
	sf::Text mGameOverText;
	sf::Text mGameOverScoreText;
	sf::Text mGameOverPositionText;

	static sf::RectangleShape sPlayfieldShape; ///< The shape for the playfield.
	static sf::RectangleShape sSmallFrameShape; ///< The shape for a small frame.
	static sf::RectangleShape sBlockShape; ///< The shape for the block.
	static sf::RectangleShape sBackgroundShape;

	/// \brief Holds the current piece for further use.
	void hold();

	/// \brief Unholds the held piece.
	void unhold();

	/// \brief Moves the current piece by the specified offset.
	void move(int x, int y);

	/// \brief Rotates the current piece according to the specified direction.
	void rotate(RotateDirection direction);

	/// \brief Tests if the specified rotation and kick for the current piece fits in the playfield.
	bool testKick(RotationState target, Point offset);

	/// \brief Checks how many lines are made and removes them.
	/// \see RemoveRow
	/// \see PushDown
	/// \return The number of lines.
	int checkLines();

	/// \brief Clears the specified line.
	/// \see PushDown.
	void clearLine(int line);

	/// \brief Pushes down the stack from the current line and above.
	void pushDown(int line);

	/// \brief Updates the score.
	/// \param numLines The number of lines made with a single move.
	void updateScore(int numLines);

	/// \brief Checks if there has been a level up.
	void checkLevel();

	/// \brief Checks if there has been a top out.
	void checkTopOut();

	/// \brief Sets the state for the current play.
	void setState(PlayState state);

	/// \brief The falling state initialization function.
	void onFalling();

	/// \brief The landing state initialization function.
	void onLanding();

	/// \brief The ARE state initialization function.
	void onARE();

	/// \brief The top out state initialization function.
	void onTopOut();

	void renderScene(sf::RenderWindow* window);

	void renderGameOverScreen(sf::RenderWindow* window);

	void handleSceneInput();

	void handleGameOverScreenInput();
};