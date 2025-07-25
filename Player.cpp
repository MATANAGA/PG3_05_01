#include "Player.h"
#include <Novice.h>

void Player::Initialize() {
	position_ = { 0, 0 };
	textureHandle_ = Novice::LoadTexture("./NoviceResources/player.png");

}

void Player::Update() {}

void Player::Draw() {

	Novice::DrawSprite((int)position_.x, (int)position_.y,
		textureHandle_, 0.25f, 0.25f, 0.0f, 0xFFFFFFFF);
	
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
