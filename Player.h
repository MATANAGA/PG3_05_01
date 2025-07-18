#pragma once
#include "math/Vector2.h"

using namespace KamataEngine;

class Player {
private:
	Vector2 position_;
	float speed_ = 2.0f;

public:
	void Initialize();
	void Update();
	void Draw();
	void MoveRight();
	void MoveLeft();
};
