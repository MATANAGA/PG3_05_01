#pragma once
#include "Player.h"
#include "InputHandler.h"
#include "Block.h"
#include "Map.h"
#include <vector>
#include "Goal.h"

class Scene {
public:
	enum class Phase {
		kTitle,
		kPlay,
		kClear
	};
	Phase phase_ = Phase::kTitle;

	struct GameState {
		Vector2 playerPos;
		Vector2 blockPos;
	};
	void Initialize();
	void Update();
	void Draw();
	bool isCarrying_ = false;


private:
	Player* player_ = nullptr;
	InputHandler* inputHandler_ = nullptr;
	Map*map_= nullptr;
	std::vector<WhiteBlock> whiteBlocks_;
	std::vector<GameState> undoHistory_;  

	int stepCount_ = 0; // 搬运中走的步数
	// Scene.h 中 Scene 类的成员变量：
	bool preSpaceKey_;
	bool preZKey_; // ← 新增这个变量

	//
	WhiteBlock* targetBlock_ = nullptr;

	Goal goal_;                  // ← 终点
	bool isClear_ = false;       // ← 是否通关
};

