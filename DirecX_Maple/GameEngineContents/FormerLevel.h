#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class FormerLevel : public GameEngineLevel
{
public:
	// constructer destructer
	FormerLevel();
	~FormerLevel();

	// delete Function
	FormerLevel(const FormerLevel& _Other) = delete;
	FormerLevel(FormerLevel&& _Other) noexcept = delete;
	FormerLevel& operator = (const FormerLevel& _Other) = delete;
	FormerLevel& operator = (FormerLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class BackGroundMap> Map = nullptr;
	std::shared_ptr<class BackGroundMap> BackMap = nullptr;
	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class Monster> MonsterObject = nullptr;
	std::shared_ptr<class AdeleSkill> PlayerSkill = nullptr;
	std::shared_ptr<class SkillManager> Skill = nullptr;

	std::shared_ptr<class Mouse> MouseObject = nullptr;
	std::shared_ptr<class MainUIActor> UIObject = nullptr;
	std::shared_ptr<class SolErdaGauge> SolObject = nullptr;

	std::shared_ptr<class GrandisGoddess> FormerNpc = nullptr;

};