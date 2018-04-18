#pragma once

enum UserAction {
	ACTION_MOVE_UP,
	ACTION_MOVE_DOWN,
	ACTION_MOVE_LEFT,
	ACTION_MOVE_RIGHT,
	ACTION_ROTATE_LEFT,
	ACTION_ROTATE_RIGHT,
	ACTION_HOLD,
	ACTION_CONFIRM,
	ACTION_CANCEL,
	NUM_ACTIONS, ///< Keep last - Counts the total number of actions.
}; ///< The actions the user can perform.