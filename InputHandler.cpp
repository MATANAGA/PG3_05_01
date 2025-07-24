#include "InputHandler.h"
#include <Novice.h>
#include <cstring>

void InputHandler::UpdateKeyState() {
	std::memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
}

ICommand* InputHandler::HandleInput() {
	if (keys_[DIK_W] && !preKeys_[DIK_W]) return pressKeyW_;
	if (keys_[DIK_S] && !preKeys_[DIK_S]) return pressKeyS_;
	if (keys_[DIK_A] && !preKeys_[DIK_A]) return pressKeyA_;
	if (keys_[DIK_D] && !preKeys_[DIK_D]) return pressKeyD_;
	return nullptr;
}

void InputHandler::AssignMoveLeftCommand2PressKeyA() {
	pressKeyA_ = new MoveLeftCommand();
}
void InputHandler::AssignMoveRightCommand2PressKeyD() {
	pressKeyD_ = new MoveRightCommand();
}
void InputHandler::AssignMoveUpCommand2PressKeyW() {
	pressKeyW_ = new MoveUpCommand();
}
void InputHandler::AssignMoveDownCommand2PressKeyS() {
	pressKeyS_ = new MoveDownCommand();
}
