#pragma once

// Ό³Έν :
class GameEngineInputLayOut
{
public:
	// constructer destructer
	GameEngineInputLayOut();
	~GameEngineInputLayOut();

	// delete Function
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator = (const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator = (GameEngineInputLayOut&& _Other) noexcept = delete;

protected:

private:
	ID3D11InputLayout* LayOut = nullptr;

	void ResCreate();

	void Setting();

};

