#include "AudioManager.h"
#include <Windows.h>

std::map<SFX, sf::SoundBuffer> AudioManager::mBuffers;
std::map<SFX, sf::Sound> AudioManager::mSounds;

void AudioManager::init() {
	mBuffers = std::map<SFX, sf::SoundBuffer>();
	mSounds = std::map<SFX, sf::Sound>();

	TCHAR tSfxDirPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, tSfxDirPath);
	wcscat_s(tSfxDirPath, L"\\res\\sfx\\");
	char fontPath[MAX_PATH];
	wcstombs(fontPath, tSfxDirPath, MAX_PATH);

	for (int i = 0; i < (int)SOUND_COUNT; i++) {
		std::string path = fontPath;
		switch ((SFX)i) {
		case SOUND_MENU_MOVE:
			path += "menu-move";
			break;
		case SOUND_CONFIRM:
			path += "confirm";
			break;
		case SOUND_CANCEL:
			path += "cancel";
			break;
		case SOUND_MOVE:
			path += "move";
			break;
		case SOUND_ROTATE:
			path += "rotate";
			break;
		case SOUND_LANDING:
			path += "landing";
			break;
		case SOUND_LINE:
			path += "line";
			break;
		case SOUND_LINE_2:
			path += "line-2";
			break;
		case SOUND_LINE_3:
			path += "line-3";
			break;
		case SOUND_Q_LINE:
			path += "quad-line";
			break;
		case SOUND_LEVEL_UP:
			path += "level-up";
			break;
		case SOUND_GAME_OVER:
			path += "game-over";
			break;
		case SOUND_ERROR:
			path += "error";
			break;
		default:
			break;
		}
		path += ".wav";

		mBuffers[(SFX)i] = sf::SoundBuffer();
		if (!mBuffers[(SFX)i].loadFromFile(path)) {
			throw;
		}
		mSounds[(SFX)i] = sf::Sound(mBuffers[(SFX)i]);
	}
}

void AudioManager::playSound(SFX sfx) {
	mSounds[sfx].play();
}
