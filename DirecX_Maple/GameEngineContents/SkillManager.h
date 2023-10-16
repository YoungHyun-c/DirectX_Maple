#pragma once

class SkillManager : public GameEngineActor
{
public:
	static SkillManager* PlayerSkillManager;
public:
	// constructer destructer
	SkillManager();
	~SkillManager();

	// delete function
	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;


protected:
	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	std::map<std::string, std::shared_ptr<class AdeleSkill>> AllSkills;

};

