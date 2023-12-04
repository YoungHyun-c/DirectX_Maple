#pragma once
#include "SkillFunction.h"

class SkillShard : public SkillFunction
{
public:
	// constructer destructer
	SkillShard();
	~SkillShard();

	// delete Function
	SkillShard(const SkillShard& _Other) = delete;
	SkillShard(SkillShard&& _Other) noexcept = delete;
	SkillShard& operator = (const SkillShard& _Other) = delete;
	SkillShard& operator = (SkillShard&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void CreateShard();
	void Release() override;

	bool UseFirst = false;
	void RenderEvent(GameEngineRenderer* _Renderer);
	void ShardPosCal();
	int ShardCount = 0;

private:
	std::vector<std::shared_ptr<class SkillWonderActor>> AllShardActor;
};

