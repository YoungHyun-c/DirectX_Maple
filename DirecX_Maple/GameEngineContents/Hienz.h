#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Hienz : public GameEngineActor
{
public:
	// constructer destructer
	Hienz();
	~Hienz();

	// delete Function
	Hienz(const Hienz& _Other) = delete;
	Hienz(Hienz&& _Other) noexcept = delete;
	Hienz& operator = (const Hienz& _Other) = delete;
	Hienz& operator = (Hienz&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineCollision> HienzCol = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Dark = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Clear = nullptr;

	bool Click = false;
};

