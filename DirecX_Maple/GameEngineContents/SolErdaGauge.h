#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SolErdaGauge : public GameEngineActor
{
public:
	// constructer destructer
	SolErdaGauge();
	~SolErdaGauge();

	// delete Function
	SolErdaGauge(const SolErdaGauge& _Other) = delete;
	SolErdaGauge(SolErdaGauge&& _Other) noexcept = delete;
	SolErdaGauge& operator = (const SolErdaGauge& _Other) = delete;
	SolErdaGauge& operator = (SolErdaGauge&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta)override;

private:
	float4 WindowHalfPos = float4::ZERO;

	std::shared_ptr<GameEngineUIRenderer> EldaGaugeBar;
	std::shared_ptr<GameEngineUIRenderer> EldaGauge;
	std::shared_ptr<class GameEngineSpriteRenderer> EldaMax;
	bool EldaMaxEffect = false;
};

