#pragma once

// Ό³Έν 
class SkillFunction : public GameEngineActor
{
	friend class SkillManager;
public:
	// constructer destructer
	SkillFunction();
	~SkillFunction();

	// delete Function
	SkillFunction(const SkillFunction& _Other) = delete;
	SkillFunction(SkillFunction&& _Other) noexcept = delete;
	SkillFunction& operator = (const SkillFunction& _Other) = delete;
	SkillFunction& operator = (SkillFunction&& _Other) noexcept = delete;

	virtual void Init() {};
	virtual void UseSkill();

	virtual void EndSkill()
	{
		IsSkillStart = false;
		IsSkillEnd = true;
	}

	bool IsSkillUsing()
	{
		return true == IsSkillStart && false == IsSkillEnd ? true : false;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	bool IsSkillStart = false;
	bool IsSkillEnd = true;

	ActorDir PlayerDir = ActorDir::Right;
	float4 PlayerPos = float4::ZERO;
	float4 CurPlayerPos = float4::ZERO;
	float4 PlayerScale = float4::ZERO;

	std::shared_ptr<class GameEngineSpriteRenderer> SkillRender1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SkillRender2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SkillRender3 = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> AfterSkillImage = nullptr;
private:


};

