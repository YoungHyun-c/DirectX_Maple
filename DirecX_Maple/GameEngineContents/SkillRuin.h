#pragma once
#include "SkillFunction.h"

// Ό³Έν :
class SkillRuin : public SkillFunction
{
public:
	// constructer destructer
	SkillRuin();
	~SkillRuin();

	// delete Function
	SkillRuin(const SkillRuin& _Other) = delete;
	SkillRuin(SkillRuin&& _Other) noexcept = delete;
	SkillRuin& operator = (const SkillRuin& _Other) = delete;
	SkillRuin& operator = (SkillRuin&& _Other) noexcept = delete;

protected:
	void UseSkill() override;
	void EndSkill() override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void RenderEvent(GameEngineRenderer* _Renderer);
	void CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup);


	int RuinHitCount = 6;

	float CurTime = 0.0f;
	float LimitTime = 2.0f;

	EventParameter HitEvent;
	bool UseFirst = false;
	EventParameter SkillEvent;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Ruin;
	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;
	void AttackEvent();
};

