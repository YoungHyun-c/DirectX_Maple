#pragma once
#include "SkillFunction.h"

// Ό³Έν :
class SkillBInd : public SkillFunction
{
public:
	// constructer destructer
	SkillBInd();
	~SkillBInd();

	// delete Function
	SkillBInd(const SkillBInd& _Other) = delete;
	SkillBInd(SkillBInd&& _Other) noexcept = delete;
	SkillBInd& operator = (const SkillBInd& _Other) = delete;
	SkillBInd& operator = (SkillBInd&& _Other) noexcept = delete;

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

	size_t ScollHitCount;

	EventParameter HitEvent;
	bool UseFirst = false;
	EventParameter SkillEvent;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Scoll;
	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;
	void AttackEvent();
};

