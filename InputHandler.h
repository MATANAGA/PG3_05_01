#pragma once
#include "Command.h"

class InputHandler {
private:
	ICommand* pressKeyA_ = nullptr;
	ICommand* pressKeyD_ = nullptr;

public:
	ICommand* HandleInput();

	void AssignMoveLeftCommand2PressKeyA();
	void AssignMoveRightCommand2PressKeyD(); 
};
