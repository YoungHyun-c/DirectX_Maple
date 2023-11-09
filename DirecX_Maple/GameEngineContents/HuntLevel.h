#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class HuntLevel : public GameEngineLevel
{
public:
	// constructer destructer
	HuntLevel();
	~HuntLevel();

	// delete Function
	HuntLevel(const HuntLevel& _Other) = delete;
	HuntLevel(HuntLevel&& _Other) noexcept = delete;
	HuntLevel& operator = (const HuntLevel& _Other) = delete;
	HuntLevel& operator = (HuntLevel&& _Other) noexcept = delete;

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

	std::shared_ptr<class CraneMonster> CraneMob = nullptr;
	
	float RegenTime = 0.0f;
	float RegenCoolTime = 7.0f;

	std::shared_ptr<class MainUIActor> UIObject = nullptr;
	std::shared_ptr<class Mouse> MouseObject = nullptr;


	std::shared_ptr<class MonsterSpawnZone> Zone1 = nullptr;
	std::shared_ptr<class MonsterSpawnZone> Zone2 = nullptr;
	std::shared_ptr<class MonsterSpawnZone> Zone3 = nullptr;
};

