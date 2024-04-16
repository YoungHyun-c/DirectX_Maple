#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 :
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

	// Ui
	std::shared_ptr<class MainUIActor> UIObject = nullptr;
	std::shared_ptr<class Mouse> MouseObject = nullptr;


	//////// 진힐라 관련////////////
	std::shared_ptr<class JinHillaBoss> BossJin = nullptr;
	//std::shared_ptr<class BossSkillManager> BossJinSkill = nullptr;


	/////////// HandAttack ///////////
	std::shared_ptr<class HandAttack> Hand1 = nullptr;
	std::shared_ptr<class HandAttack> Hand2 = nullptr;
	std::shared_ptr<class HandAttack> Hand3 = nullptr;
	std::shared_ptr<class HandAttack> Hand4 = nullptr;
	std::shared_ptr<class HandAttack> Hand5 = nullptr;
	std::shared_ptr<class HandAttack> Hand6 = nullptr;
	std::shared_ptr<class HandAttack> Hand7 = nullptr;
	
	float EventTime1 = 0.0f;
	float EventCoolTime1 = 7.0f;
	float EventTime2 = 0.0f;
	float EventCoolTime2 = 7.5f;
	float EventTime3 = 0.0f;
	float EventCoolTime3 = 8.0f;

	bool HandApeear1 = false;
	bool HandApeear2 = false;
	bool HandApeear3 = false;

	///////// Altar 제단 /////////////
	std::shared_ptr<class AltarUi> Altar = nullptr;


	//////// Candle 양초 /////////////
	std::shared_ptr<class CandleUi> Candle1 = nullptr;
	bool Fire1 = false;
	bool CandleCut1 = false;
	std::shared_ptr<class CandleUi> Candle2 = nullptr;
	bool Fire2 = false;
	bool CandleCut2 = false;
	std::shared_ptr<class CandleUi> Candle3 = nullptr;
	bool Fire3 = false;
	bool CandleCut3 = false;

	/////////// Timer 타이머 ////////
	std::shared_ptr<class ContentsTimer> BossTimer = nullptr;

	/////////// SickleCut 낫베기패턴 ///////
	std::shared_ptr<class JinHillaSickleCut> SickleAni = nullptr;

	/////////// DeathCount 데카관련 ////////
	std::shared_ptr<class PlayerDeathCountUI> DeathUI = nullptr;


	/////////// BossLevelUi 체력관련 ////////
	std::shared_ptr<class BossLevelUi> BossUi = nullptr;
};

