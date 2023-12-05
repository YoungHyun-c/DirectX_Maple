#pragma once
#include "SkillOrderSummonActor.h"

// Ό³Έν :
class SkillOrderActor : public SkillOrderSummonActor
{
public:
	// constructer destructer
	SkillOrderActor();
	~SkillOrderActor();

	// delete Function
	SkillOrderActor(const SkillOrderActor& _Other) = delete;
	SkillOrderActor(SkillOrderActor&& _Other) noexcept = delete;
	SkillOrderActor& operator = (const SkillOrderActor& _Other) = delete;
	SkillOrderActor& operator = (SkillOrderActor&& _Other) noexcept = delete;

	float4 GetOrderPos()
	{
		OrderPos = Order->Transform.GetWorldPosition();
		return OrderPos;
	}

protected:
	void Start() override;

	float4 OrderPos = float4::ZERO;
private:
	float DieStartTime = 0.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> OrderBack;
};

