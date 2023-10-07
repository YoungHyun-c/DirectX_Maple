#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SummonUi : public GameEngineActor
{
public:
	// constructer destructer
	SummonUi();
	~SummonUi();

	// delete Function
	SummonUi(const SummonUi& _Other) = delete;
	SummonUi(SummonUi&& _Other) noexcept = delete;
	SummonUi& operator = (const SummonUi& _Other) = delete;
	SummonUi& operator = (SummonUi&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void PosUpdate();

private:
	std::shared_ptr<class GameEngineUIRenderer> SummonButton;
	std::shared_ptr<class GameEngineUIRenderer> ClearButton;

	std::shared_ptr<GameEngineCollision> SummonCol;
	std::shared_ptr<GameEngineCollision> ClearCol;

	float4 SummonPos = { -550.0f, 330.0f };
	float4 ClearPos = { -550.0f, 250.0f };

	bool MonsterSummon = false;
};

