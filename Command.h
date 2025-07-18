#pragma once

class Player;

// コマンドクラス
class ICommand {
public:
	virtual ~ICommand();
	virtual void Execute(Player& player) = 0;
};

// 右移動コマンド
class MoveRightCommand : public ICommand {
public:
	void Execute(Player& player) override;
};

// 左移動コマンド
class MoveLeftCommand : public ICommand {
public:
	void Execute(Player& player) override;
};
