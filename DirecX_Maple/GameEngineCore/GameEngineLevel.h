#pragma once
#include "GameEngineObject.h"

// Ό³Έν :
class GameEngineLevel : public GameEngineObject
{
public:
	// constructer destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator = (const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator = (GameEngineLevel&& _Other) noexcept = delete;

protected:

private:

};

