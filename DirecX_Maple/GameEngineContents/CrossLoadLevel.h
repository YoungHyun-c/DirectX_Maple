#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CrossLoadLevel : public GameEngineLevel
{
public:
	// constructer destructer
	CrossLoadLevel();
	~CrossLoadLevel();

	// delete Function
	CrossLoadLevel(const CrossLoadLevel& _Other) = delete;
	CrossLoadLevel(CrossLoadLevel&& _Other) noexcept = delete;
	CrossLoadLevel& operator = (const CrossLoadLevel& _Other) = delete;
	CrossLoadLevel& operator = (CrossLoadLevel&& _Other) noexcept = delete;

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
	std::shared_ptr<class QuestIcon> QuestObject = nullptr;
	std::shared_ptr<class SolErdaGauge> SolObject = nullptr;
};

