#pragma once
#include <Novice.h>
#include <KamataEngine.h>
using namespace KamataEngine;
class Goal {
public:
	Vector2 position_;
	float size_ = 40.0f;

	void Initialize(Vector2 pos);
	void Draw();
};
