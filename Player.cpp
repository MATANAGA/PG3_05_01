#include "Player.h"
#include <Novice.h>

void Player::Initialize() {
	position_ = { 0, 0 };
}

void Player::Update() {}

void Player::Draw() {

	Novice::DrawBox((int)position_.x, (int)position_.y, 40, 40, 0.0f, RED, kFillModeWireFrame);
	
	

} 

void Player::MoveRight() {
	position_.x += speed_;
}

void Player::MoveLeft() {
	position_.x -= speed_;
}

void Player::MoveUp() {
	position_.y -= speed_;
}

void Player::MoveDown() {
	position_.y += speed_;
}
