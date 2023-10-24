#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BossSkillEffect : public GameEngineActor
{
public:
	// constructer destructer
	BossSkillEffect();
	~BossSkillEffect();

	// delete Function
	BossSkillEffect(const BossSkillEffect& _Other) = delete;
	BossSkillEffect(BossSkillEffect&& _Other) noexcept = delete;
	BossSkillEffect& operator = (const BossSkillEffect& _Other) = delete;
	BossSkillEffect& operator = (BossSkillEffect&& _Other) noexcept = delete;

	void ChangeAnimationState(const std::string& _Name)
	{
		EffectName = _Name;
		SkillEffect->ChangeAnimation(EffectName);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> SkillEffect;

	std::string EffectName = "";
};

