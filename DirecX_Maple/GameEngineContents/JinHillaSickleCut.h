#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class JinHillaSickleCut : public GameEngineActor
{
public:
	// constructer destructer
	JinHillaSickleCut();
	~JinHillaSickleCut();

	// delete Function
	JinHillaSickleCut(const JinHillaSickleCut& _Other) = delete;
	JinHillaSickleCut(JinHillaSickleCut&& _Other) noexcept = delete;
	JinHillaSickleCut& operator = (const JinHillaSickleCut& _Other) = delete;
	JinHillaSickleCut& operator = (JinHillaSickleCut&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrveLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> SickleCutAni = nullptr;
	std::shared_ptr<class ContentsTimer> BossTimer = nullptr;

	float CurTime = 0.0f;
	float AttackTime = 150.0f;
	double CurBossHp = 0.0f;
	double PercentFrontHp = 0.0f;
	//                                              60%					30%
	// float AttackTime = 150.0f; float AttackTime = 125.0f; float AttackTime = 100.0f;
};

