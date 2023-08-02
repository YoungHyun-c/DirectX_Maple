#pragma once
#include "GameEngineObject.h"

// ���� :
class GameEngineComponent
{
public:
	// constructer destructer
	GameEngineComponent();
	~GameEngineComponent();

	// delete Function
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator = (const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator = (GameEngineComponent&& _Other) noexcept = delete;

protected:

private:

};

