#pragma once
#include "Command.h"

class InputHandler {
private:
	ICommand* pressKeyA_ = nullptr;
	ICommand* pressKeyD_ = nullptr;
	ICommand* pressKeyW_ = nullptr;
	ICommand* pressKeyS_ = nullptr;

	char keys_[256] = {};
	char preKeys_[256] = {};

public:
	void UpdateKeyState();
	ICommand* HandleInput();

	void AssignMoveLeftCommand2PressKeyA();
	void AssignMoveRightCommand2PressKeyD();
	void AssignMoveUpCommand2PressKeyW();
	void AssignMoveDownCommand2PressKeyS();
};
