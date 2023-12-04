#pragma once
#include "SkillFunction.h"

// Ό³Έν :
class SkillWonder : public SkillFunction
{
	static float WonderCool;
public:
	// constructer destructer
	SkillWonder();
	~SkillWonder();

	// delete Function
	SkillWonder(const SkillWonder& _Other) = delete;
	SkillWonder(SkillWonder&& _Other) noexcept = delete;
	SkillWonder& operator = (const SkillWonder& _Other) = delete;
	SkillWonder& operator = (SkillWonder&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void CreateWonder();
	void Release() override;

	bool UseFirst = false;
	void RenderEvent(GameEngineRenderer* _Renderer);
	void WonderPosCal();

	int WonderCount = 0;
	
private:
	std::vector<std::shared_ptr<class SkillWonderActor>> AllWonderActor;
};

