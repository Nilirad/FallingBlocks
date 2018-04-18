#pragma once
#include <SFML/Graphics/Font.hpp>

const int PLAYFIELD_WIDTH = 10; ///< The width of the playfield in blocks.
const int PLAYFIELD_HEIGHT = 22; ///< The height of the playfield in blocks.
const int PLAYFIELD_HIDDEN = 2; ///< The number of top lines hidden from the view.
const int PLAYFIELD_HEIGHT_VISIBLE = PLAYFIELD_HEIGHT - PLAYFIELD_HIDDEN;
const float PX_BLOCK = 32; ///< The size of the block's side, in pixels.
const float PX_PLAYFIELD_WIDTH = PX_BLOCK * PLAYFIELD_WIDTH; ///< The width of the playfield, in pixels.
const float PX_PLAYFIELD_HEIGHT = PX_BLOCK * PLAYFIELD_HEIGHT; ///< The size of the playfield, in pixels.
const float PX_PLAYFIELD_HEIGHT_VISIBLE = PX_BLOCK * PLAYFIELD_HEIGHT_VISIBLE;
const float PLAYFIELD_X = 220; ///< The X offset of the playfield position.
const float PLAYFIELD_Y = 50; ///< The Y offset of the playfield position.
const float SCORE_X = 20; ///< The X offset of the score position.
const float SCORE_Y = 50; ///< The Y offset of the score position.
const float NEXT_X = 20; ///< The X offset of the next piece position.
const float NEXT_Y = 190; ///< The Y offset of the next piece position.
const float PX_SMALL_FRAME = 180; ///< The size in pixel for the small frame.
const float HOLD_X = 20; ///< The X offset of the hold frame position.
const float HOLD_Y = NEXT_Y + PX_SMALL_FRAME + 60; ///< The Y offset of the hold frame position.

const float PX_WINDOW_WIDTH = PLAYFIELD_X + (int)PX_PLAYFIELD_WIDTH; ///< The width of the window in pixels.
const float PX_WINDOW_HEIGHT = PLAYFIELD_Y + (int)PX_PLAYFIELD_HEIGHT_VISIBLE; ///< The height of the window in pixels.

const int LATERAL_KEY_REPEAT_FIRST_DELAY = 15; ///< The delay for the first key repeat for lateral movement.
const int VERTICAL_KEY_REPEAT_FIRST_DELAY = 25; ///< The delay for the first key repeat for vertical movement.
const int KEY_REPEAT_DELAY = 2; ///< The delay for a non-first key repeat.

class Constants {
public:
	/// \brief Initializes the static member data of the class.
	static void init();
	
	static sf::Font font; ///< The font.
};