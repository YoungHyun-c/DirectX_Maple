#pragma once
#include "MonsterFunction.h"
#include <GameEngineCore/GameEngineState.h>

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

	void DeathStart();
	void DeathUpdate(float _Delta);

	void BossStateCheck();

private:
	ActorDir Dir = ActorDir::Max;
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

	bool IsAttack = false;
	bool PlayerBind = false;
	int TestPattern = 1;

	std::shared_ptr<class CravingMonster> CravingMob;

	void CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup);
	void SkillAnimation();

	int Test = 0;


	class Skill
	{
	public:
		bool IsControll;
		float MaxCoolTime;
		float CurCoolTime;
		float4 SkillUsePos;
		ActorDir SkillUseDir = ActorDir::Max;
		int TargetCollisionOrder;
		GameEngineState StateTest;

		// void CoolUpdate();

		void Update(float _Delta)
		{
			StateTest.Update(_Delta);
		}
	};

	bool SkillUseCheck();
	Skill* CurSkill = nullptr;
	std::map<const char, Skill > SkillState;
	int Green = 0;
	int Purple = 2;

	bool GreenAttack = false;
	bool PurpleAttack = false;
};

