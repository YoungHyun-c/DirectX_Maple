#pragma once

// Ό³Έν :
class GameEngineRenderUnit
{
public:
	// constructer destructer
	GameEngineRenderUnit();
	~GameEngineRenderUnit();

	// delete Function
	GameEngineRenderUnit(const GameEngineRenderUnit& _Other) = delete;
	GameEngineRenderUnit(GameEngineRenderUnit&& _Other) noexcept = delete;
	GameEngineRenderUnit& operator = (const GameEngineRenderUnit& _Other) = delete;
	GameEngineRenderUnit& operator = (GameEngineRenderUnit&& _Other) noexcept = delete;

protected:

private:

};

