#include "Goal.h"



void Goal::Initialize(Vector2 pos) {
	position_ = pos;
}

void Goal::Draw() {
	Novice::DrawBox((int)position_.x , (int)position_.y ,
		(int)size_, (int)size_, 0.0f, 0x00FF00FF, kFillModeSolid); // 绿色线框
}
