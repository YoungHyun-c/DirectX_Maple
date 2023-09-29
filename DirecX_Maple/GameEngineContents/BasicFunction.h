#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BasicFunction : public GameEngineActor
{
public:
	// constructer destructer
	BasicFunction();
	~BasicFunction();

	// delete Function
	BasicFunction(const BasicFunction& _Other) = delete;
	BasicFunction(BasicFunction&& _Other) noexcept = delete;
	BasicFunction& operator = (const BasicFunction& _Other) = delete;
	BasicFunction& operator = (BasicFunction&& _Other) noexcept = delete;

protected:
	void TimeCounting();

	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;

private:

};

