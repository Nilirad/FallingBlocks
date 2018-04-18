#include "Command.h"

void Command::execute(CommandID command) {
	switch (command)
	{
	case COMMAND_SAVE_OPTIONS:
		KeyBindings::saveToFile();
		Localization::saveToFile();
		break;
	case COMMAND_SET_ENGLISH_LANGUAGE:
		Localization::setLanguage(LANGUAGE_ENGLISH);
		break;
	case COMMAND_SET_ITALIAN_LANGUAGE:
		Localization::setLanguage(LANGUAGE_ITALIAN);
		break;
	default:
		break;
	}
}
