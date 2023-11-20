#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class TestLevel : public GameEngineLevel
{
public:
	// constructer destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator = (const TestLevel& _Other) = delete;
	TestLevel& operator = (TestLevel&& _Other) noexcept = delete;

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



	std::shared_ptr<class JinHillaBoss> BossJin = nullptr;



	std::shared_ptr<class CandleUi> CandleTest1 = nullptr;
	bool Fire1 = false;
	bool CandleCut1 = false;

	std::shared_ptr<class CandleUi> CandleTest2 = nullptr;
	bool Fire2 = false;
	bool CandleCut2 = false;

	std::shared_ptr<class CandleUi> CandleTest3 = nullptr;
	bool Fire3 = false;
	bool CandleCut3 = false;

	std::shared_ptr<class AltarUi> AltarTest = nullptr;

	std::shared_ptr<class HandAttack> HandTest1 = nullptr;
	std::shared_ptr<class HandAttack> HandTest2 = nullptr;
	std::shared_ptr<class HandAttack> HandTest3 = nullptr;
	std::shared_ptr<class HandAttack> HandTest4 = nullptr;
	std::shared_ptr<class HandAttack> HandTest5 = nullptr;
	std::shared_ptr<class HandAttack> HandTest6 = nullptr;
	std::shared_ptr<class HandAttack> HandTest7 = nullptr;

	float CurPlayerDeathCount = 0.0f;

	float EventTime1 = 0.0f;
	float EventCoolTime1 = 7.0f;

	float EventTime2 = 0.0f;
	float EventCoolTime2 = 7.5f;

	float EventTime3 = 0.0f;
	float EventCoolTime3 = 8.0f;

	bool HandApeear1 = false;
	bool HandApeear2 = false;
	bool HandApeear3 = false;
};

