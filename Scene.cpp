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
	phase_ = Phase::kTitle;

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
		int x = (rand() % 31) * 40;
		int y = (rand() % 14) * 40;
		WhiteBlock block;
		block.Initialize({ (float)x, (float)y });
		whiteBlocks_.push_back(block);
	}
	goal_.Initialize({ 600.0f, 400.0f });

}

void Scene::Update() {
	char keys[256];
	Novice::GetHitKeyStateAll(keys);
	inputHandler_->UpdateKeyState();

	switch (phase_) {
	case Phase::kTitle:
		if (keys[DIK_SPACE]) {
			Initialize();  // 重新初始化游戏内容
			phase_ = Phase::kPlay;
		}
		break;

	case Phase::kPlay: {
		ICommand* iCommand_ = inputHandler_->HandleInput();

		Vector2 moveDelta = { 0, 0 };
		if (iCommand_) {
			if (dynamic_cast<MoveRightCommand*>(iCommand_)) moveDelta = { 40, 0 };
			else if (dynamic_cast<MoveLeftCommand*>(iCommand_)) moveDelta = { -40, 0 };
			else if (dynamic_cast<MoveUpCommand*>(iCommand_)) moveDelta = { 0, -40 };
			else if (dynamic_cast<MoveDownCommand*>(iCommand_)) moveDelta = { 0, 40 };
		}

		bool isSpacePressed = keys[DIK_SPACE];
		bool isZPressed = keys[DIK_Z];

		// SPACE 处理：拿起/放下/搬运箱子
		if (isSpacePressed && !preSpaceKey_) {
			if (isCarrying_) {
				// 如果搬运中，并且碰到终点，就移除箱子
				if (targetBlock_ && IsHit(targetBlock_->position_, targetBlock_->size_, goal_.position_, goal_.size_)) {
					for (auto it = whiteBlocks_.begin(); it != whiteBlocks_.end(); ++it) {
						if (&(*it) == targetBlock_) {
							whiteBlocks_.erase(it);
							break;
						}
					}
					targetBlock_ = nullptr;
					isCarrying_ = false;
					stepCount_ = 0;
					undoHistory_.clear();
				}
				else {
					// 没有放在终点，就只是放下
					isCarrying_ = false;
					targetBlock_ = nullptr;
					stepCount_ = 0;
					undoHistory_.clear();
				}
			}
			else {
				// 尝试拾取附近的箱子
				for (auto& block : whiteBlocks_) {
					if (IsHit(player_->GetPosition(), 40.0f, block.position_, block.size_)) {
						isCarrying_ = true;
						targetBlock_ = &block;
						break;
					}
				}
			}
		}

		// 玩家与箱子移动处理
		if (moveDelta.x != 0 || moveDelta.y != 0) {
			Vector2 nextPlayerPos = { player_->GetPosition().x + moveDelta.x, player_->GetPosition().y + moveDelta.y };

			if (isCarrying_ && targetBlock_) {
				Vector2 nextBlockPos = { targetBlock_->position_.x + moveDelta.x, targetBlock_->position_.y + moveDelta.y };

				bool canMove = true;
				for (auto& block : whiteBlocks_) {
					if (&block == targetBlock_) continue;
					if (IsHit(nextPlayerPos, 40.0f, block.position_, block.size_) ||
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
				player_->SetPosition(nextPlayerPos);
			}
		}

		// Ctrl+Z 撤销搬运
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

		// 通关判断
		if (whiteBlocks_.empty()) {
			isClear_ = true;
			phase_ = Phase::kClear;
		}

		// 状态更新
		preSpaceKey_ = isSpacePressed;
		preZKey_ = isZPressed;

		break;
	}

	case Phase::kClear:
		if (keys[DIK_SPACE] && !preSpaceKey_) {
			phase_ = Phase::kTitle;
		}
		preSpaceKey_ = keys[DIK_SPACE];
		break;
	}
}

void Scene::Draw() {
	switch (phase_) {
	case Phase::kTitle:
		Novice::ScreenPrintf(100, 300, "=== PUSH SPACE TO START ===");
		break;

	case Phase::kPlay:
		map_->DrawGrid();

		for (auto& block : whiteBlocks_) {
			block.Draw();
			if (isCarrying_) {
				if (IsHit(player_->GetPosition(), 40.0f, block.position_, block.size_)) {
					block.color = 0xFF0000FF;
				}
			}
			else {
				block.color = 0xFFFFFFFF;
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
		}

		player_->Draw();
		goal_.Draw();

		break;

	case Phase::kClear:
		Novice::ScreenPrintf(100, 300, "CLEAR!! All blocks delivered.");
		Novice::ScreenPrintf(100, 350, "Press SPACE to return to Title.");
		break;
	}
}

