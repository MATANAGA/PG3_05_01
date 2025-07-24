#pragma once
#include "math/Vector2.h"
using namespace KamataEngine;

class WhiteBlock {
public:
	Vector2 position_;
	float size_ = 30.0f;
	unsigned int color = 0xFFFFFFFF; 

	void Initialize(Vector2 pos);
	void Draw();
};
