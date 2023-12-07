#pragma once
#include "SkillInfiniteSummonActor.h"

// Ό³Έν :
class SkillInfiniteActor : public SkillInfiniteSummonActor
{
public:
	// constructer destructer
	SkillInfiniteActor();
	~SkillInfiniteActor();

	// delete Function
	SkillInfiniteActor(const SkillInfiniteActor& _Other) = delete;
	SkillInfiniteActor(SkillInfiniteActor&& _Other) noexcept = delete;
	SkillInfiniteActor& operator = (const SkillInfiniteActor& _Other) = delete;
	SkillInfiniteActor& operator = (SkillInfiniteActor&& _Other) noexcept = delete;

	float4 GetInfinitePos()
	{
		InfinitePos = InfiOrder->Transform.GetWorldPosition();
		return InfinitePos;
	}

protected:
	void Start() override;

	float4 InfinitePos = float4::ZERO;
private:

};

