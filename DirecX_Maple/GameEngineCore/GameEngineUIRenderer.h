#pragma once
#include "GameEngineSpriteRenderer.h"

// ���� :
class GameEngineUIRenderer : public GameEngineSpriteRenderer
{
public:
	// constructer destructer
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

	// delete Function
	GameEngineUIRenderer(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer(GameEngineUIRenderer&& _Other) noexcept = delete;
	GameEngineUIRenderer& operator = (const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer& operator = (GameEngineUIRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

