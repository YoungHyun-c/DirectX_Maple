#pragma once
#include "SkillFunction.h"


// Ό³Έν :
class SkillMaestro : public SkillFunction
{
public:
	// constructer destructer
	SkillMaestro();
	~SkillMaestro();

	// delete Function
	SkillMaestro(const SkillMaestro& _Other) = delete;
	SkillMaestro(SkillMaestro&& _Other) noexcept = delete;
	SkillMaestro& operator = (const SkillMaestro& _Other) = delete;
	SkillMaestro& operator = (SkillMaestro&& _Other) noexcept = delete;

protected:
	void UseSkill() override;
	void EndSkill() override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	void RenderEvent(GameEngineRenderer* _Renderer);
	void CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup);

	size_t MaestroHitCount;

	float CurTime = 0.0f;
	float LimitTime = 0.558f;

	EventParameter HitEvent;
	bool UseFirst = false;
	EventParameter SkillEvent;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Maestro;
	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;
	void AttackEvent();
};

