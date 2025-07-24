#include "Command.h"
#include "Player.h"


void MoveRightCommand::Execute(Player& player) {
	player.MoveRight();
}

void MoveLeftCommand::Execute(Player& player) {
	player.MoveLeft();
}

void MoveUpCommand::Execute(Player& player) {
	player.MoveUp();
}

void MoveDownCommand::Execute(Player& player) {
	player.MoveDown();
}
