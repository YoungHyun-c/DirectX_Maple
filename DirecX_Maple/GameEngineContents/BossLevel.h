#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class BossLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BossLevel();
	~BossLevel();

	// delete Function
	BossLevel(const BossLevel& _Other) = delete;
	BossLevel(BossLevel&& _Other) noexcept = delete;
	BossLevel& operator = (const BossLevel& _Other) = delete;
	BossLevel& operator = (BossLevel&& _Other) noexcept = delete;

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

	std::shared_ptr<class JinHillaAnime> JinHillaAttackAni = nullptr;

	std::shared_ptr<class JinHillaBoss> BossJin = nullptr;
	std::shared_ptr<class BossSkillManager> BossJinSkill = nullptr;
	/*std::shared_ptr<class CravingMonster> CravingMob;
	std::shared_ptr<class GhostSwoo> GhostSwooMob;
	std::shared_ptr<class GhostDamien> GhostDamienMob;*/
	//std::shared_ptr<class GhostSwoo> SwooBall;

	//std::shared_ptr<class BossSkillEffect> BossEffect;
	// Ui
	std::shared_ptr<class MainUIActor> UIObject = nullptr;
	std::shared_ptr<class Mouse> MouseObject = nullptr;
	std::shared_ptr<class BossLevelUi> BossUi = nullptr;

	float CurTime = 29.44f;
	bool AniEnd = false;
};

