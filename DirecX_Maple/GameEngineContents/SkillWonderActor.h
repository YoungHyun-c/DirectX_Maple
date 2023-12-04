#pragma once
#include "BaseSummonActor.h"

// Ό³Έν :
class SkillWonderActor : public BaseSummonActor
{
public:
	// constructer destructer
	SkillWonderActor();
	~SkillWonderActor();

	// delete Function
	SkillWonderActor(const SkillWonderActor& _Other) = delete;
	SkillWonderActor(SkillWonderActor&& _Other) noexcept = delete;
	SkillWonderActor& operator = (const SkillWonderActor& _Other) = delete;
	SkillWonderActor& operator = (SkillWonderActor&& _Other) noexcept = delete;

protected:
	void ReadyStart() override;
	void AttackStart() override;
	void HitStart() override;
	void DeathStart() override;

	void DeathUpdate(float _Delta) override;

	void Start() override;
private:
	float DieStartTime = 0.0f;
};

