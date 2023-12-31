#pragma once
#include "SkillFunction.h"

// ���� :
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
	
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void RenderEvent(GameEngineRenderer* _Renderer);
	void CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup);

	bool UseFirst = false;
	EventParameter SkillEvent;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;

	int DivideHitCount = 0;

	std::string SkillName = "";
	std::string SkillHitName = "";
	GameEngineRandom RandomSKillNum;
	int SkillNum = 0;
	std::shared_ptr<class GameEngineSpriteRenderer> Divide1;
	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;
	void AttackEvent();

	float CurTime = 0.0f;
	float LimitTime = 0.12f;
	EventParameter HitEvent;
	bool Hit = false;
};

