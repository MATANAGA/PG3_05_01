// Block.cpp
#include "Block.h"
#include <Novice.h>

void WhiteBlock::Initialize(Vector2 pos) {
	position_ = pos;
	color = 0xFFFFFFFF; // 初始化为白色
	textureHandle_ = Novice::LoadTexture("./NoviceResources/block.png");

}

void WhiteBlock::Draw() {
	Novice::DrawSprite((int)position_.x, (int)position_.y,
		textureHandle_, 1.0f, 1.0f, 0.0f, color);
}
