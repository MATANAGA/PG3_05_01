#pragma once
#include "InputHandler.h"
#include "Command.h"
#include "Player.h"

class Scene {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	InputHandler* inputHandler_ = nullptr;
	ICommand* iCommand_ = nullptr;
	Player* player_ = nullptr;
};
