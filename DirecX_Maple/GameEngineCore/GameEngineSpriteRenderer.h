#pragma once
#include "GameEngineRenderer.h"

// Ό³Έν :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// constructer destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator = (const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator = (GameEngineSpriteRenderer&& _Other) noexcept = delete;

protected:
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	void SetSprite(std::string_view _Name);
};

