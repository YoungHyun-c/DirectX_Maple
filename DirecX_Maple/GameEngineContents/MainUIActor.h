#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MainUIActor : public GameEngineActor
{
public:
	// constructer destructer
	MainUIActor();
	~MainUIActor();

	// delete Function
	MainUIActor(const MainUIActor& _Other) = delete;
	MainUIActor(MainUIActor&& _Other) noexcept = delete;
	MainUIActor& operator = (const MainUIActor& _Other) = delete;
	MainUIActor& operator = (MainUIActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta)override;

private:
	float4 WindowHalfPos = float4::ZERO;
	std::shared_ptr<GameEngineUIRenderer> AtereGaugeBack;
	std::shared_ptr<GameEngineUIRenderer> AtereGauge;
	std::shared_ptr<GameEngineUIRenderer> AtereAnime;

	std::shared_ptr<GameEngineUIRenderer> ExpBarUi;
	std::shared_ptr<GameEngineUIRenderer> ExpBarMin;

	std::shared_ptr<GameEngineUIRenderer> EldaGaugeBar;
	std::shared_ptr<GameEngineUIRenderer> EldaGauge;
	std::shared_ptr<class GameEngineSpriteRenderer> EldaMax;
};

