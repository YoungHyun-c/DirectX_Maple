#pragma once
#include "SkillFunction.h"

// Ό³Έν :
class SkillOrder : public SkillFunction
{
public:
	// constructer destructer
	SkillOrder();
	~SkillOrder();

	// delete Function
	SkillOrder(const SkillOrder& _Other) = delete;
	SkillOrder(SkillOrder&& _Other) noexcept = delete;
	SkillOrder& operator = (const SkillOrder& _Other) = delete;
	SkillOrder& operator = (SkillOrder&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void CreateOrder();
	void Release() override;

	bool UseFirst = false;
	void RenderEvent(GameEngineRenderer* _Renderer);
	int OrderCount = 0;

	void OrderPosCal();

	float4 CurOrderPos = float4::ZERO;

private:
	std::vector<std::shared_ptr<class SkillOrderActor>> AllOrderActor;
};

