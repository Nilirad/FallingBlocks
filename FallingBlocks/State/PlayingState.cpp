#include "PlayingState.h"
#include <cassert>
#include "StateStack.h"
#include "../Utilities/KeyboardManager.h"
#include "../Utilities/KeyBindings.h"
#include "../Utilities/AudioManager.h"
#include "../Utilities/HighScores.h"
#include "../Utilities/Localization.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  STATIC DATA  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

sf::RectangleShape PlayingState::sPlayfieldShape =
	sf::RectangleShape(sf::Vector2f(PX_PLAYFIELD_WIDTH, PX_PLAYFIELD_HEIGHT_VISIBLE));
sf::RectangleShape PlayingState::sSmallFrameShape = sf::RectangleShape(sf::Vector2f(PX_SMALL_FRAME, PX_SMALL_FRAME));
sf::RectangleShape PlayingState::sBlockShape = sf::RectangleShape(sf::Vector2f(PX_BLOCK, PX_BLOCK));
sf::RectangleShape PlayingState::sBackgroundShape = sf::RectangleShape(sf::Vector2f(PX_WINDOW_WIDTH, PX_WINDOW_HEIGHT));



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

PlayingState::PlayingState(StateStack* stack)
	: ApplicationState(stack)
	, mHeldPiece()
	, mLevelUpTimer(0)
	, mIsComboTextVisible(false)
	, mScoreText()
	, mLevelText()
	, mLinesText()
	, mComboText()
	, mNextText()
	, mHoldText()
	, mLevelUpText()
	, mGameOverText()
	, mGameOverPositionText()
{
	mScoreText.setFont(Constants::font);
	mScoreText.setCharacterSize(24);
	mScoreText.setFillColor(sf::Color::White);
	mScoreText.setPosition(sf::Vector2f(SCORE_X, SCORE_Y));
	
	mLevelText.setFont(Constants::font);
	mLevelText.setCharacterSize(24);
	mLevelText.setFillColor(sf::Color::White);
	mLevelText.setPosition(sf::Vector2f(SCORE_X, SCORE_Y + 30));

	mLinesText.setFont(Constants::font);
	mLinesText.setCharacterSize(24);
	mLinesText.setFillColor(sf::Color::White);
	mLinesText.setPosition(sf::Vector2f(SCORE_X, SCORE_Y + 2 * 30));

	mComboText.setFont(Constants::font);
	mComboText.setCharacterSize(27);
	mComboText.setFillColor(sf::Color::White);
	mComboText.setPosition(sf::Vector2f(PLAYFIELD_X + 4, PLAYFIELD_Y + 4));

	mNextText.setFont(Constants::font);
	mNextText.setCharacterSize(24);
	mNextText.setFillColor(sf::Color::White);
	mNextText.setString(Localization::getString(STRING_NEXT));
	mNextText.setPosition(sf::Vector2f(NEXT_X, NEXT_Y - 30));

	mHoldText.setFont(Constants::font);
	mHoldText.setCharacterSize(24);
	mHoldText.setFillColor(sf::Color::White);
	mHoldText.setString(Localization::getString(STRING_HOLD));
	mHoldText.setPosition(sf::Vector2f(HOLD_X, HOLD_Y - 30));

	mLevelUpText.setFont(Constants::font);
	mLevelUpText.setCharacterSize(20);
	mLevelUpText.setFillColor(sf::Color::White);
	mLevelUpText.setString(Localization::getString(STRING_LEVEL_UP));
	float posX = PX_WINDOW_WIDTH - mLevelUpText.getGlobalBounds().width - 4;
	float posY = PLAYFIELD_Y + 4;
	mLevelUpText.setPosition(sf::Vector2f(posX, posY));
	
	mGameOverText.setFont(Constants::font);
	mGameOverText.setFillColor(sf::Color::White);
	mGameOverText.setString(Localization::getString(STRING_GAME_OVER));
	mGameOverText.setCharacterSize(50);
	mGameOverText.setPosition(sf::Vector2f(0, 0));

	mGameOverScoreText.setFont(Constants::font);
	mGameOverScoreText.setFillColor(sf::Color::White);
	mGameOverScoreText.setCharacterSize(30);
	mGameOverScoreText.setPosition(sf::Vector2f(0, 80));

	mGameOverPositionText.setFont(Constants::font);
	mGameOverPositionText.setFillColor(sf::Color::White);
	mGameOverPositionText.setCharacterSize(20);
	mGameOverPositionText.setPosition(sf::Vector2f(0, 130));

	sBackgroundShape.setFillColor(sf::Color(0, 0, 64));
	sPlayfieldShape.setFillColor(sf::Color::Black);
	sPlayfieldShape.setPosition(sf::Vector2f(PLAYFIELD_X, PLAYFIELD_Y));
	sSmallFrameShape.setFillColor(sf::Color::Black);
	sBlockShape.setFillColor(sf::Color::Green);
	sBlockShape.setOutlineThickness(BLOCK_OUTLINE);
	sBlockShape.setOutlineColor(sf::Color::Black);
	mRandomGenerator = RandomGenerator();
	std::fill_n(mBlockStack, PLAYFIELD_WIDTH * PLAYFIELD_HEIGHT, EMPTY);
	mFallingTimer = 0;
	mTotalLines = 0;
	mLevel = 0;
	mComboCounter = 0;
	mScore = 0;
	mJustMadeHoldAction = false;
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::start() {
	mNextPiece = mRandomGenerator.next();
	setState(ARE);
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::handleInput() {
	if (mState != TOP_OUT) {
		handleSceneInput();
	} else {
		handleGameOverScreenInput();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::update(sf::Time dt) {
	mIsComboTextVisible = (mComboCounter > 1);
	mLevelUpTimer -= 1;

	switch (mState) {
	case FALLING:
		if (mFallingTimer >= FALLING_FRAMES / (mLevel * LEVEL_UP_FACTOR + 1)) {
			mFallingTimer = 0;
			move(0, -1);
		}
		else {
			mFallingTimer += 1;
		}
		break;

	case LANDING:
		setState(ARE);
		break;

	case ARE:
		if (mFallingTimer >= 1.5 * FALLING_FRAMES) {
			setState(FALLING);
		}
		else {
			mFallingTimer += 1;
		}
		break;

	case TOP_OUT:
		// TODO: Using this variable here is unelegant. Consider if layer solution works.
		mFallingTimer += 1;
		break;

	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::render(sf::RenderWindow* window) {
	if (mState != TOP_OUT) {
		renderScene(window);
	} else {
		renderGameOverScreen(window);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::hold() {
	mFallingTimer = 0;
	mJustMadeHoldAction = true;
	mFallingPiece.setPosition(SPAWN_POSITION);
	mFallingPiece.rotate(ZERO, Point{ 0, 0 });
	mHeldPiece.setValue(mFallingPiece);
	setState(ARE);
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::unhold() {
	mFallingTimer = 0;
	mJustMadeHoldAction = true;
	mFallingPiece = mHeldPiece.getValue();
	mHeldPiece.removeValue();
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::move(int x, int y) {
	int nextX = mFallingPiece.getPosition().x + x;
	int nextY = mFallingPiece.getPosition().y + y;

	Point const* blocks = mFallingPiece.getBlockPositions();
	for (int i = 0; i < TETROMINO_SIZE; i++) {
		int blockX = nextX + blocks[i].x;
		int blockY = nextY + blocks[i].y;
		if (blockY < 0 || y < 0 && mBlockStack[blockY * PLAYFIELD_WIDTH + blockX] != EMPTY) {
			setState(LANDING);
			return;
		}
		if (blockX < 0 || blockX >= PLAYFIELD_WIDTH || blockY >= PLAYFIELD_HEIGHT
			|| mBlockStack[blockY * PLAYFIELD_WIDTH + blockX] != EMPTY)
		{
			return;
		}

	}
	mFallingPiece.setPosition(Point{ nextX, nextY });
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::rotate(RotateDirection direction) {
	RotationState target = mFallingPiece.getTargetRotationState(direction);
	Point kickTests[NUM_KICK_TESTS];
	mFallingPiece.calculateKickOffsets(direction, kickTests);

	for (int i = 0; i < NUM_KICK_TESTS; i++) {
		if (testKick(target, kickTests[i])) {
			mFallingPiece.rotate(target, kickTests[i]);
			AudioManager::playSound(SOUND_ROTATE);
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

bool PlayingState::testKick(RotationState target, Point offset) {
	Point const* blockPositions = mFallingPiece.getBlockPositions(target);
	int targetX = mFallingPiece.getPosition().x + offset.x;
	int targetY = mFallingPiece.getPosition().y + offset.y;

	for (int i = 0; i < TETROMINO_SIZE; i++) {
		int blockX = targetX + blockPositions[i].x;
		int blockY = targetY + blockPositions[i].y;
		if (blockX < 0 || blockX >= PLAYFIELD_WIDTH || blockY < 0 || blockY >= PLAYFIELD_HEIGHT
			|| mBlockStack[blockY * PLAYFIELD_WIDTH + blockX] != EMPTY)
		{
			return false;
		}
	}
	for (int i = 0; i < TETROMINO_SIZE; i++) {
		int blockX = targetX + blockPositions[i].x;
		int blockY = targetY + blockPositions[i].y;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

int PlayingState::checkLines() {
	int lineCount = 0;
	bool cleared = false;
	for (int y = 0; y < PLAYFIELD_HEIGHT; y++) {
		for (int x = 0; x < PLAYFIELD_WIDTH; x++) {
			if (mBlockStack[y * PLAYFIELD_WIDTH + x] == EMPTY) {
				break;
			}
			if (x == 9) {
				lineCount += 1;
				clearLine(y);
				pushDown(y);
				cleared = true;
				y -= 1;
			}
		}
	}

	if (cleared) {
		mComboCounter += 1;
	} else {
		mComboCounter = 0;
	}
	mTotalLines += lineCount;
	return lineCount;
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::clearLine(int line) {
	for (int x = 0; x < PLAYFIELD_WIDTH; x++) {
		mBlockStack[line * PLAYFIELD_WIDTH + x] = EMPTY;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::pushDown(int line) {
	for (int y = line; y < PLAYFIELD_HEIGHT - 1; y++) {
		for (int x = 0; x < PLAYFIELD_WIDTH; x++) {
			mBlockStack[y * PLAYFIELD_WIDTH + x] = mBlockStack[(y + 1) * PLAYFIELD_WIDTH + x];
		}
	}
	clearLine(PLAYFIELD_HEIGHT - 1);
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::updateScore(int numLines) {
	if (numLines == 1) {
		AudioManager::playSound(SOUND_LINE);
		mScore += 100 * (mLevel + 1);
	}
	else if (numLines == 2) {
		AudioManager::playSound(SOUND_LINE_2);
		mScore += 300 * (mLevel + 1);
	}
	else if (numLines == 3) {
		AudioManager::playSound(SOUND_LINE_3);
		mScore += 500 * (mLevel + 1);
	}
	else if (numLines == 4) {
		AudioManager::playSound(SOUND_Q_LINE);
		mScore += 800 * (mLevel + 1);
	}

	if (mComboCounter > 1) {
		mScore += 50 * (mLevel + 1) * (mComboCounter - 1);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::checkLevel() {
	int level = mTotalLines / LINES_PER_LEVEL;

	if (level > mLevel) {
		AudioManager::playSound(SOUND_LEVEL_UP);
		mLevelUpTimer = 120;
		mLevel = level;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::checkTopOut() {
	Point position = mFallingPiece.getPosition();
	const Point* blocks = mFallingPiece.getBlockPositions();
	for (int i = 0; i < TETROMINO_SIZE; i++) {
		const Point block = Point{ blocks[i].x + position.x, blocks[i].y + position.y };
		if (mBlockStack[block.y * PLAYFIELD_WIDTH + block.x] != EMPTY) {
			setState(TOP_OUT);
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::setState(PlayState state) {
	mState = state;

	switch (state) {
	case FALLING:
		onFalling();
		break;
	case ARE:
		onARE();
		break;
	case LANDING:
		onLanding();
		break;
	case TOP_OUT:
		onTopOut();
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::onFalling() {
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::onLanding() {
	AudioManager::playSound(SOUND_LANDING);
	mJustMadeHoldAction = false;
	Point position = mFallingPiece.getPosition();
	const Point* blocks = mFallingPiece.getBlockPositions();
	for (int i = 0; i < TETROMINO_SIZE; i++) {
		const Point block = Point{ blocks[i].x + position.x, blocks[i].y + position.y };
		mBlockStack[block.y * PLAYFIELD_WIDTH + block.x] = (BlockState)((int)mFallingPiece.getType() + 1);
		assert(block.y * PLAYFIELD_WIDTH + block.x >= 0);
		assert(block.y * PLAYFIELD_WIDTH + block.x < PLAYFIELD_WIDTH * PLAYFIELD_HEIGHT);
	}

	int numLines = checkLines();
	if (numLines > 0) {
		updateScore(numLines);
		checkLevel();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::onARE() {
	KeyboardManager::resetKeyDelay(KeyBindings::getKey(ACTION_MOVE_DOWN));
	mFallingPiece = mNextPiece;
	mNextPiece = mRandomGenerator.next();
	mFallingPiece.setPosition(SPAWN_POSITION);
	checkTopOut();
}

/////////////////////////////////////////////////////////////////////////////////////////

void PlayingState::onTopOut() {
	AudioManager::playSound(SOUND_GAME_OVER);
	int position = HighScores::tryInsertScore(mScore);
	mGameOverScoreText.setString(Localization::getString(STRING_GAME_OVER_SCORE) + std::to_wstring(mScore));

	if (position != -1) {
		mGameOverPositionText.setString(Localization::getString(STRING_GAME_OVER_ENTER_CHART) + std::to_wstring(position));
	} else {
		mGameOverPositionText.setString(Localization::getString(STRING_GAME_OVER_NOT_ENTER_CHART));
	}
	mFallingTimer = 0;
}

void PlayingState::renderScene(sf::RenderWindow * window) {
	// Draw frames
	window->draw(sBackgroundShape);
	window->draw(sPlayfieldShape);
	sSmallFrameShape.setPosition(sf::Vector2f(NEXT_X, NEXT_Y));
	window->draw(sSmallFrameShape);
	sSmallFrameShape.setPosition(sf::Vector2f(HOLD_X, HOLD_Y));
	window->draw(sSmallFrameShape);

	// Draw Stack
	for (int y = 0; y < PLAYFIELD_HEIGHT_VISIBLE; y++) {
		for (int x = 0; x < PLAYFIELD_WIDTH; x++) {
			if (mBlockStack[y * PLAYFIELD_WIDTH + x] != EMPTY) {
				float blockX = PLAYFIELD_X + x * PX_BLOCK;
				float blockY = PLAYFIELD_Y + PX_PLAYFIELD_HEIGHT_VISIBLE - (y + 1) * PX_BLOCK;
				assert(blockX >= PLAYFIELD_X);
				assert(blockX <= PLAYFIELD_X + PX_PLAYFIELD_WIDTH - PX_BLOCK);
				assert(blockY >= PLAYFIELD_Y);
				assert(blockY <= PLAYFIELD_Y + PX_PLAYFIELD_HEIGHT_VISIBLE - PX_BLOCK);
				sBlockShape.setPosition(sf::Vector2f(blockX, blockY));
				switch (mBlockStack[y * PLAYFIELD_WIDTH + x])
				{
				case BLUE:
					sBlockShape.setFillColor(sf::Color(0, 64, 255));
					break;
				case ORANGE:
					sBlockShape.setFillColor(sf::Color(255, 69, 0));
					break;
				case GREEN:
					sBlockShape.setFillColor(sf::Color::Green);
					break;
				case PURPLE:
					sBlockShape.setFillColor(sf::Color(128, 0, 128));
					break;
				case RED:
					sBlockShape.setFillColor(sf::Color::Red);
					break;
				case CYAN:
					sBlockShape.setFillColor(sf::Color::Cyan);
					break;
				case YELLOW:
					sBlockShape.setFillColor(sf::Color::Yellow);
					break;
				default:
					break;
				}
				window->draw(sBlockShape);
			}
		}
	}

	// Draw Falling piece
	Point const* blocks = mFallingPiece.getBlockPositions();
	sBlockShape.setFillColor(mFallingPiece.getColor());
	for (int i = 0; i < TETROMINO_SIZE; i++) {
		int x = mFallingPiece.getPosition().x + blocks[i].x;
		int y = mFallingPiece.getPosition().y + blocks[i].y;
		float blockX = PLAYFIELD_X + x * PX_BLOCK;
		float blockY = PLAYFIELD_Y + PX_PLAYFIELD_HEIGHT_VISIBLE - (y + 1) * PX_BLOCK;
		if (y < PLAYFIELD_HEIGHT_VISIBLE) {
			assert(blockX >= PLAYFIELD_X);
			assert(blockX <= PLAYFIELD_X + PX_PLAYFIELD_WIDTH - PX_BLOCK);
			assert(blockY >= PLAYFIELD_Y);
			assert(blockY <= PLAYFIELD_Y + PX_PLAYFIELD_HEIGHT_VISIBLE - PX_BLOCK);
			sBlockShape.setPosition(sf::Vector2f(blockX, blockY));
			window->draw(sBlockShape);
		}
	}

	// Draw ghost
	sf::Color ghostColor = sBlockShape.getFillColor();
	ghostColor.a = 50;
	sBlockShape.setFillColor(ghostColor);
	int ghostY = mFallingPiece.getPosition().y;
	while (true) {
		bool breakFlag = false;
		for (int i = 0; i < TETROMINO_SIZE; i++) {
			int blockX = mFallingPiece.getPosition().x + blocks[i].x;
			int blockY = ghostY - 1 + blocks[i].y;
			if (blockY < 0 || mBlockStack[blockY * PLAYFIELD_WIDTH + blockX] != EMPTY) {
				breakFlag = true;
				break;
			}
		}
		if (breakFlag) {
			break;
		}
		ghostY -= 1;
	}

	for (int i = 0; i < TETROMINO_SIZE; i++) {
		int x = mFallingPiece.getPosition().x + blocks[i].x;
		int y = ghostY + blocks[i].y;
		float blockX = PLAYFIELD_X + x * PX_BLOCK;
		float blockY = PLAYFIELD_Y + PX_PLAYFIELD_HEIGHT_VISIBLE - (y + 1) * PX_BLOCK;
		if (y < PLAYFIELD_HEIGHT_VISIBLE) {
			sBlockShape.setPosition(sf::Vector2f(blockX, blockY));
			window->draw(sBlockShape);
		}
	}

	// Draw Next
	blocks = mNextPiece.getBlockPositions();
	sBlockShape.setFillColor(mNextPiece.getColor());
	float originX = NEXT_X + PX_SMALL_FRAME / 2 - PX_BLOCK / 2;
	float originY = NEXT_Y + PX_SMALL_FRAME / 2 - PX_BLOCK / 2;
	for (int i = 0; i < TETROMINO_SIZE; i++) {
		float blockX = originX + blocks[i].x * PX_BLOCK;
		float blockY = originY - blocks[i].y * PX_BLOCK;
		sBlockShape.setPosition(sf::Vector2f(blockX, blockY));
		window->draw(sBlockShape);
	}

	// Draw Held
	if (mHeldPiece.hasValue()) {
		blocks = mHeldPiece.getValue().getBlockPositions();
		sBlockShape.setFillColor(mHeldPiece.getValue().getColor());
		float originX = HOLD_X + PX_SMALL_FRAME / 2 - PX_BLOCK / 2;
		float originY = HOLD_Y + PX_SMALL_FRAME / 2 - PX_BLOCK / 2;
		for (int i = 0; i < TETROMINO_SIZE; i++) {
			float blockX = originX + blocks[i].x * PX_BLOCK;
			float blockY = originY - blocks[i].y * PX_BLOCK;
			sBlockShape.setPosition(sf::Vector2f(blockX, blockY));
			window->draw(sBlockShape);
		}
	}

	// Draw Text
	mScoreText.setString(Localization::getString(STRING_SCORE) + std::to_wstring(mScore));
	mLevelText.setString(Localization::getString(STRING_LEVEL) + std::to_wstring(mLevel));
	mLinesText.setString(Localization::getString(STRING_LINES) + std::to_wstring(mTotalLines));
	mComboText.setString(std::to_wstring(mComboCounter) + Localization::getString(STRING_COMBO));
	window->draw(mScoreText);
	window->draw(mLevelText);
	window->draw(mLinesText);
	window->draw(mNextText);
	window->draw(mHoldText);
	if (mIsComboTextVisible) {
		window->draw(mComboText);
	}
	if (mLevelUpTimer > 0) {
		window->draw(mLevelUpText);
	}
}

void PlayingState::renderGameOverScreen(sf::RenderWindow* window) {
	window->draw(mGameOverText);
	window->draw(mGameOverScoreText);
	window->draw(mGameOverPositionText);
}

void PlayingState::handleSceneInput() {
	if (KeyboardManager::isKeyPressed(KeyBindings::getKey(ACTION_MOVE_LEFT),
		LATERAL_KEY_REPEAT_FIRST_DELAY, KEY_REPEAT_DELAY))
	{
		AudioManager::playSound(SOUND_MOVE);
		move(-1, 0);
	}
	if (KeyboardManager::isKeyPressed(KeyBindings::getKey(ACTION_MOVE_RIGHT),
		LATERAL_KEY_REPEAT_FIRST_DELAY, KEY_REPEAT_DELAY))
	{
		AudioManager::playSound(SOUND_MOVE);
		move(1, 0);
	}
	if (KeyboardManager::isKeyPressed(KeyBindings::getKey(ACTION_MOVE_DOWN),
		VERTICAL_KEY_REPEAT_FIRST_DELAY, KEY_REPEAT_DELAY))
	{
		AudioManager::playSound(SOUND_MOVE);
		if (mState == ARE) {
			setState(FALLING);
		}
		mFallingTimer = 0;
		move(0, -1);
	}
	if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_ROTATE_LEFT))) {
		rotate(COUNTERCLOCKWISE);
	}
	if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_ROTATE_RIGHT))) {
		rotate(CLOCKWISE);
	}
	if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_HOLD))) {
		if (!mJustMadeHoldAction) {
			AudioManager::playSound(SOUND_CONFIRM);
			if (mHeldPiece.hasValue()) {
				unhold();
			}
			else {
				hold();
			}
		}
		else {
			AudioManager::playSound(SOUND_ERROR);
		}
	}
	if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_CONFIRM))) {
		mStack->requestPush(PAUSE_STATE);
	}
}

void PlayingState::handleGameOverScreenInput() {
	if (mFallingTimer > 60 && KeyboardManager::getKey() != sf::Keyboard::Unknown) {
		mStack->requestPop();
		mStack->requestPush(MAIN_MENU_STATE);
	}
}
