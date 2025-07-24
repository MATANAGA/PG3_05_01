#pragma once
#include "math/Vector2.h"
using namespace KamataEngine;

class Player {
private:
	Vector2 position_;
	float speed_ = 40.0f;

public:
	void Initialize();
	void Update();
	void Draw();

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	Vector2 GetPosition() const {
		return position_;
	}
	void SetPosition(const Vector2& pos) {
		position_ = pos;
	}
};
