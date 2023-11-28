#pragma once
#include "MonsterFunction.h"
#include <GameEngineCore/GameEngineState.h>
#include "BossSkillManager.h"

// 설명 :
class JinHillaBoss : public MonsterFunction
{
private:
	static JinHillaBoss* MainBoss;
public:
	static JinHillaBoss* GetMainBoss()
	{
		return MainBoss;
	}

	inline ActorDir GetDir()
	{
		return Dir;
	}

	float4 GetJinHillaTransform()
	{
		return Pos;
	}

	// constructer destructer
	JinHillaBoss();
	~JinHillaBoss();

	// delete Function
	JinHillaBoss(const JinHillaBoss& _Other) = delete;
	JinHillaBoss(JinHillaBoss&& _Other) noexcept = delete;
	JinHillaBoss& operator = (const JinHillaBoss& _Other) = delete;
	JinHillaBoss& operator = (JinHillaBoss&& _Other) noexcept = delete;

	void Hit(long long _Damage, bool _Attack) override;

	void CallRegen() override;

	long long GetCurBossHp()
	{
		return JinHillaCurHp;
	}

	long long GetMainBossHp()
	{
		return JinHillaHp;
	}

protected:
	void LevelStart(GameEngineLevel* _PreveLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start();
	void Update(float _Delta) override;

	void StandStart();
	void StandUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);
	
	void RegenUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void AttackEvent(float _Delta);

	void Skill_1Start();
	void Skill_1AfterUpdate(float _Delta);
	//void Skill_1End();
	//void Skill_1After();

	//void SKill_2Start();
	void Skill_3Start();
	void Skill_3Update(float _Delta);


	void DeathStart();
	void DeathUpdate(float _Delta);

	void BossStateCheck();

	void CallMobDeathCheck(float _Delta);

private:
	ActorDir Dir = ActorDir::Max;
	float4 Pos = float4::ZERO;
	void JinDirCheck();
	float4 JinBossScale = float4::ZERO;

	float MoveSpeed = 50.0f;
	long long JinHillaHp = 176000000000000; // 하드 176조
	long long JinHillaCurHp = 0; // 하드 176조
	//long long JinHillaHp = 1000000000; // 하드 176조
	int Defense = 300;
	float LeftCheck = 100.0f;
	float RightCheck = 1750.0f;
	float MoveLimit = 50.0f;

	float AppearCool = 1.5f;
	float StartAttack = 0.0f;
	float AttackCool = 8.0f;

	std::shared_ptr<GameEngineCollision> JinHillaAttackRangeCol;
	std::shared_ptr<GameEngineCollision> JinHillBodyCol;

	std::shared_ptr<GameEngineCollision> JinHillBindSkillCol;
	std::shared_ptr<GameEngineCollision> JinHillKnockSkillCol;
	std::shared_ptr<GameEngineCollision> JinHillFrontSlapSkillCol;
	std::shared_ptr<GameEngineCollision> JinHillSideSlapSkillCol;
	std::shared_ptr<GameEngineCollision> JinHillChoppingSkillCol;

	std::shared_ptr<class BossSkillEffect> BossEffect;

	bool CallMob = false;
	bool IsAttack = false;
	bool PlayerBind = false;
	int TestPattern = 1;

	std::shared_ptr<class CravingMonster> CravingMob1 = nullptr;
	std::shared_ptr<class CravingMonster> CravingMob2 = nullptr;
	std::shared_ptr<class GhostDamien> DamienMob = nullptr;

	bool CallCraving1 = false;
	bool CallCraving2 = false;
	bool CallDamien = false;
	
	float Craving1DeathTime = 0.0f;
	float Craving2DeathTime = 0.0f;
	float DamienDeathTime = 0.0f;
	float DeathLimitTime = 20.0f;

	void BindCollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup);
	void KnockBackCollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup);
	void SkillAnimation();

	std::shared_ptr<class BossChat> Chat = nullptr;
	std::shared_ptr<class AchieveUI> Achieve = nullptr;

	float ChangeTime = 0.0f;
	float ChangeLevelTime = 6.0f;
	std::shared_ptr<class GameEngineUIRenderer> DarkRenderer;
};

