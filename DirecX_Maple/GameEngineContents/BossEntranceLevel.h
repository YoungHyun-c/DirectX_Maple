#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class BossEntranceLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BossEntranceLevel();
	~BossEntranceLevel();

	// delete Function
	BossEntranceLevel(const BossEntranceLevel& _Other) = delete;
	BossEntranceLevel(BossEntranceLevel&& _Other) noexcept = delete;
	BossEntranceLevel& operator = (const BossEntranceLevel& _Other) = delete;
	BossEntranceLevel& operator = (BossEntranceLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class BackGroundMap> Map = nullptr;

	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class AdeleSkill> PlayerSkill = nullptr;
	std::shared_ptr<class SkillManager> Skill = nullptr;

	std::shared_ptr<class MainUIActor> UIObject = nullptr;
	std::shared_ptr<class Mouse> MouseObject = nullptr;
};

