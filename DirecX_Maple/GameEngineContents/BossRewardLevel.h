#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class BossRewardLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BossRewardLevel();
	~BossRewardLevel();

	// delete Function
	BossRewardLevel(const BossRewardLevel& _Other) = delete;
	BossRewardLevel(BossRewardLevel&& _Other) noexcept = delete;
	BossRewardLevel& operator = (const BossRewardLevel& _Other) = delete;
	BossRewardLevel& operator = (BossRewardLevel&& _Other) noexcept = delete;

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

	std::shared_ptr<class BossBoxReward> BossBox = nullptr;
};

