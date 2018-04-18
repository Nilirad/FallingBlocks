#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>

enum SFX {
	SOUND_MENU_MOVE,
	SOUND_CONFIRM,
	SOUND_CANCEL,
	SOUND_MOVE,
	SOUND_ROTATE,
	SOUND_LANDING,
	SOUND_LINE,
	SOUND_LINE_2,
	SOUND_LINE_3,
	SOUND_Q_LINE,
	SOUND_LEVEL_UP,
	SOUND_GAME_OVER,
	SOUND_ERROR,
	SOUND_COUNT, ///< Keep last.
};

class AudioManager {
public:
	static void init();
	static void playSound(SFX sfx);

private:
	static std::map<SFX, sf::SoundBuffer> mBuffers;
	static std::map<SFX, sf::Sound> mSounds;
};