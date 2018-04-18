#include "SwitchElement.h"
#include "Command.h"

SwitchElement::SwitchElement()
	: mText()
	, mCommand()
{
}

// TODO: command is leaking. Please fix.
SwitchElement::~SwitchElement() {
//	delete mCommand;
}

SwitchElement::SwitchElement(std::wstring text, CommandID command)
	: mText(text)
	, mCommand(command)
{
}

void SwitchElement::execute() {
	Command::execute(mCommand);
}

std::wstring SwitchElement::getText() {
	return mText;
}
