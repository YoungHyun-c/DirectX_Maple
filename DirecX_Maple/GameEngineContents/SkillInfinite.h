#pragma once
#include "SkillFunction.h"

// Ό³Έν :
class SkillInfinite : public SkillFunction
{
public:
	// constructer destructer
	SkillInfinite();
	~SkillInfinite();

	// delete Function
	SkillInfinite(const SkillInfinite& _Other) = delete;
	SkillInfinite(SkillInfinite&& _Other) noexcept = delete;
	SkillInfinite& operator = (const SkillInfinite& _Other) = delete;
	SkillInfinite& operator = (SkillInfinite&& _Other) noexcept = delete;


	void UseSkill() override;
	void EndSkill() override;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	bool UseFirst = false;
	void RenderEvent(GameEngineRenderer* _Renderer);

	void CreateInfinite();
	int InfiniteCount = 0;
	int InfiniteLimitCount = 18;

	void InfinitePosCal();

	float InfiTime = 0.0f;
	float InfiLimitTime = 30.0f;

	float4 CurInfiPos = float4::ZERO;
	GameEngineRandom InfiRandPos;
	float InfiRand = 0.0f;

private:
	std::vector<std::shared_ptr<class SkillInfiniteActor>> AllInfiniteActor;

	std::shared_ptr<class GameEngineSpriteRenderer> InfiBack;
	std::shared_ptr<class GameEngineSpriteRenderer> InfiFront;
};

