#include "Scene.h"
#include <Novice.h>
#include <cstdlib>
#include <vector>

bool IsHit(const Vector2& aPos, float aSize, const Vector2& bPos, float bSize) {
	return (
		aPos.x < bPos.x + bSize &&
		aPos.x + aSize > bPos.x &&
		aPos.y < bPos.y + bSize &&
		aPos.y + aSize > bPos.y
		);
}

void Scene::Initialize() {
	inputHandler_ = new InputHandler();
	inputHandler_->AssignMoveLeftCommand2PressKeyA();
	inputHandler_->AssignMoveRightCommand2PressKeyD();
	inputHandler_->AssignMoveUpCommand2PressKeyW();
	inputHandler_->AssignMoveDownCommand2PressKeyS();

	map_ = new Map();
	player_ = new Player();
	player_->Initialize();

	stepCount_ = 0;
	preSpaceKey_ = false;
	preZKey_ = false; // 初始化新增变量
	isCarrying_ = false;
	targetBlock_ = nullptr;
	undoHistory_.clear();

	for (int i = 0; i < 5; ++i) {
		int x = (rand() % 32) * 40;
		int y = (rand() % 18) * 40;
		WhiteBlock block;
		block.Initialize({ (float)x, (float)y });
		whiteBlocks_.push_back(block);
	}
}

void Scene::Update() {
	char keys[256];
	Novice::GetHitKeyStateAll(keys);
	Novice::GetHitKeyStateAll(keys);

	inputHandler_->UpdateKeyState();
	ICommand* iCommand_ = inputHandler_->HandleInput();

	Vector2 moveDelta = { 0, 0 };
	if (iCommand_) {
		if (dynamic_cast<MoveRightCommand*>(iCommand_)) moveDelta = { 40, 0 };
		else if (dynamic_cast<MoveLeftCommand*>(iCommand_)) moveDelta = { -40, 0 };
		else if (dynamic_cast<MoveUpCommand*>(iCommand_)) moveDelta = { 0, -40 };
		else if (dynamic_cast<MoveDownCommand*>(iCommand_)) moveDelta = { 0, 40 };
	}

	bool isSpacePressed = keys[DIK_SPACE];
	bool isZPressed = keys[DIK_Z]; // 新增：Z键状态

	// 空格切换搬运状态
	if (isSpacePressed && !preSpaceKey_) {
		if (isCarrying_) {
			isCarrying_ = false;
			targetBlock_ = nullptr;
			stepCount_ = 0;
			undoHistory_.clear();
		}
		else {
			for (auto& block : whiteBlocks_) {
				if (IsHit(player_->GetPosition(), 40, block.position_, block.size_)) {
					isCarrying_ = true;
					targetBlock_ = &block;
					break;
				}
			}
		}
	}

	// 执行移动
	if (moveDelta.x != 0 || moveDelta.y != 0) {
		Vector2 nextPlayerPos = { player_->GetPosition().x + moveDelta.x, player_->GetPosition().y + moveDelta.y };

		if (isCarrying_ && targetBlock_) {
			Vector2 nextBlockPos = { targetBlock_->position_.x + moveDelta.x, targetBlock_->position_.y + moveDelta.y };

			bool canMove = true;
			for (auto& block : whiteBlocks_) {
				if (&block == targetBlock_) continue;
				if (IsHit(nextPlayerPos, 40, block.position_, block.size_) ||
					IsHit(nextBlockPos, targetBlock_->size_, block.position_, block.size_)) {
					canMove = false;
					break;
				}
			}

			if (canMove) {
				GameState state;
				state.playerPos = player_->GetPosition();
				state.blockPos = targetBlock_->position_;
				undoHistory_.push_back(state);

				player_->SetPosition(nextPlayerPos);
				targetBlock_->position_ = nextBlockPos;
				stepCount_++;
			}
		}
		else {
			// 自由状态直接移动
			player_->SetPosition(nextPlayerPos);
		}
	}

	// Ctrl+Z 撤销（只在Z键刚按下时执行）
	if (isCarrying_) {
		if (keys[DIK_LCONTROL] && isZPressed && !preZKey_) {
			if (!undoHistory_.empty()) {
				GameState state = undoHistory_.back();
				undoHistory_.pop_back();
				player_->SetPosition(state.playerPos);
				if (targetBlock_) {
					targetBlock_->position_ = state.blockPos;
				}
				stepCount_--;
			}
		}
	}

	// 更新上一帧状态
	preSpaceKey_ = isSpacePressed;
	preZKey_ = isZPressed;
}

void Scene::Draw() {
	map_->DrawGrid();
	for (auto& block : whiteBlocks_) {
		block.Draw();
		if (isCarrying_)
		{
			if (IsHit(player_->GetPosition(), 40.0f, block.position_, block.size_)) {
				block.color = 0xFF0000FF; // 红色
			}
		}
		else
		{

			block.color = 0xFFFFFFFF; // 白色

		}


	}


	if (isCarrying_) {
		Novice::DrawBox(0, 720 - 120, 1280, 120, 0.0f, BLACK, kFillModeSolid);
		Novice::ScreenPrintf(100, 720 - 100, "WASD / arrow: move | SPACE: change block | Ctrl+Z: Undo");
		Novice::ScreenPrintf(100, 720 - 60, "You have %d more 'UnDo' actions available.", stepCount_);
	}
	else {
		Novice::DrawBox(0, 720 - 120, 1280, 120, 0.0f, BLACK, kFillModeSolid);
		Novice::ScreenPrintf(100, 720 - 100, "WASD / arrow: move | SPACE: change block");
		Novice::ScreenPrintf(100, 720 - 60, "In Selector Mode, you cannot use the 'Undo' action.");
		player_->Draw();

	}
}
