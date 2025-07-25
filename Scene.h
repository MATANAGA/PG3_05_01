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
	void PlayBGM(int bgmHandle);


private:
    Player* player_ = nullptr;
    InputHandler* inputHandler_ = nullptr;
    Map* map_ = nullptr;
    std::vector<WhiteBlock> whiteBlocks_;
    std::vector<GameState> undoHistory_;

    int stepCount_ = 0;
    bool preSpaceKey_ = false;
    bool preZKey_ = false;

    WhiteBlock* targetBlock_ = nullptr;

    Goal goal_;
    bool isClear_ = false;
    int clearTexture_ = -1;
    int titleTexture_ = -1;

    // BGM 相关
    int titleBgmHandle_ = -1;
    

    int currentBgmPlaying_ = -1;  // 播放句柄
    int currentBgmResource_ = -1; // 当前播放的资源句柄，用于判断是否切换BGM

};

