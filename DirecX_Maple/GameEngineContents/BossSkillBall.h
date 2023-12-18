#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BossSkillBall : public GameEngineActor
{
public:
	// constructer destructer
	BossSkillBall();
	~BossSkillBall();

	// delete Function
	BossSkillBall(const BossSkillBall& _Other) = delete;
	BossSkillBall(BossSkillBall&& _Other) noexcept = delete;
	BossSkillBall& operator = (const BossSkillBall& _Other) = delete;
	BossSkillBall& operator = (BossSkillBall&& _Other) noexcept = delete;

	void SetDir(ActorDir _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> SkillBall;
	std::shared_ptr<GameEngineCollision> SkillBallCollision;

	float LiveTime = 0.0f;
	float LimitTime = 6.0f;
	ActorDir Dir = ActorDir::Max;
};

