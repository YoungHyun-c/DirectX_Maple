#pragma once
#include "SkillFunction.h"

// Ό³Έν :
class SkillDivide : public SkillFunction
{
public:
	// constructer destructer
	SkillDivide();
	~SkillDivide();

	// delete Function
	SkillDivide(const SkillDivide& _Other) = delete;
	SkillDivide(SkillDivide&& _Other) noexcept = delete;
	SkillDivide& operator = (const SkillDivide& _Other) = delete;
	SkillDivide& operator = (SkillDivide&& _Other) noexcept = delete;


protected:
	void UseSkill() override;
	void EndSkill() override;

private:
	void Start();
	void Update(float _Delta);

	void RenderEvent(GameEngineRenderer* _Renderer);
	void CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup);

	bool UseFirst = false;
	EventParameter SkillEvent;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;


	size_t DivideHitCount;

	std::shared_ptr<class GameEngineSpriteRenderer> Divide1;
	//std::shared_ptr<class GameEngineSpriteRenderer> Divide2;
	//std::shared_ptr<class GameEngineSpriteRenderer> Divide3;
	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;
	void AttackEvent();

	float CurTime = 0.0f;
	float LimitTime = 0.12f;
};

