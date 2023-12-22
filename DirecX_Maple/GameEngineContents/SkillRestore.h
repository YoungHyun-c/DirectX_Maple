#pragma once
#include "SkillFunction.h"

// Ό³Έν :
class SkillRestore : public SkillFunction
{
public:
	// constructer destructer
	SkillRestore();
	~SkillRestore();

	// delete Function
	SkillRestore(const SkillRestore& _Other) = delete;
	SkillRestore(SkillRestore&& _Other) noexcept = delete;
	SkillRestore& operator = (const SkillRestore& _Other) = delete;
	SkillRestore& operator = (SkillRestore&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

	bool UseFirst = false;
	void RenderEvent(GameEngineRenderer* _Renderer);
	void CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup);

private:
	EventParameter HitEvent;

	EventParameter SkillEvent;

	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;

	std::shared_ptr<class DamageRenderer> NewDR = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Restore;
	int RestoreHitCount = 3;
	void AttackEvent();

	float RestoreTime = 30.0f;
	float CurTime = 0.0f;
	float LimitTime = 3.0f;
};

