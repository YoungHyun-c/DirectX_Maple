#pragma once
#include "SkillFunction.h"

// Ό³Έν :
class SkillStorm : public SkillFunction
{
public:
	// constructer destructer
	SkillStorm();
	~SkillStorm();

	// delete Function
	SkillStorm(const SkillStorm& _Other) = delete;
	SkillStorm(SkillStorm&& _Other) noexcept = delete;
	SkillStorm& operator = (const SkillStorm& _Other) = delete;
	SkillStorm& operator = (SkillStorm&& _Other) noexcept = delete;

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

	size_t StormHitCount = 8;

	float CurTime = 0.0f;
	float LimitTime = 0.9f;

	float StormTime = 0.0f;
	float StormLimitTime = 14.0f;

	EventParameter HitEvent;
	bool UseFirst = false;
	EventParameter SkillEvent;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Ruin;
	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;
	void AttackEvent();
};

