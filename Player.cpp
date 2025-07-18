#include "Player.h"
#include <Novice.h>

void Player::Initialize() {
	position_ = { 200.0f, 200.0f };
}

void Player::Update() {}

void Player::Draw() {
	Novice::DrawBox((int)position_.x, (int)position_.y, 100, 100, 0.0f, WHITE, kFillModeSolid);
}

void Player::MoveRight() {
	position_.x += speed_;
}

void Player::MoveLeft() {
	position_.x -= speed_;
}
