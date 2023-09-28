#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SkillManager : public GameEngineActor
{
public:
	// constructer destructer
	SkillManager();
	~SkillManager();

	// delete Function
	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator = (const SkillManager& _Other) = delete;
	SkillManager& operator = (SkillManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer;

};

