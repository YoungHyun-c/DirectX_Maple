#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class BossBindEffect : public GameEngineActor
{
public:
	// constructer destructer
	BossBindEffect();
	~BossBindEffect();

	// delete Function
	BossBindEffect(const BossBindEffect& _Other) = delete;
	BossBindEffect(BossBindEffect&& _Other) noexcept = delete;
	BossBindEffect& operator = (const BossBindEffect& _Other) = delete;
	BossBindEffect& operator = (BossBindEffect&& _Other) noexcept = delete;

	void GetStartBindEffect()
	{
		BindEffect->On();
		BindEffect->ChangeAnimation("SkillBind");
	}

	void GetEndBindEffect()
	{
		BindEffect->Off();
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> BindEffect;

	float SkillBinding = 0.0f;
	float SkillBindTime = 10.0f;
	float FormerBinding = 0.0f;
	float FormerBindTime = 10.0f;
};

