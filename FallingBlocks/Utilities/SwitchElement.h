#pragma once

#include "CommandID.h"
#include <string>
#include <vector>

class SwitchElement {
public:
	SwitchElement();

	~SwitchElement();

	SwitchElement(std::wstring text, CommandID command);

	void execute();

	std::wstring getText();

private:
	std::wstring mText;
	CommandID mCommand;
};