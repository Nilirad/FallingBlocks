#pragma once

#include "CommandID.h"
#include "Localization.h"
#include "KeyBindings.h"

class Command {
public:
	static void execute(CommandID command);
};