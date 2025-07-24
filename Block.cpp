// Block.cpp
#include "Block.h"
#include <Novice.h>

void WhiteBlock::Initialize(Vector2 pos) {
	position_ = pos;
	color = 0xFFFFFFFF; // 初始化为白色
}

void WhiteBlock::Draw() {
	Novice::DrawBox((int)position_.x + 5, (int)position_.y + 5,
		(int)size_, (int)size_, 0.0f, color, kFillModeSolid);
}
