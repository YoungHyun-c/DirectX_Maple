#pragma once
#include "MonsterFunction.h"

//enum class CravingState
//{
//	Regen,
//	Stand,
//	Move,
//	Attack,
//	Die,
//	Dieing,
//	Awake,
//	Death,
//	Max,
//};


class CravingMonster : public MonsterFunction
{
public:
	static std::list<CravingMonster*> CravingMonsters;
public:
	// constructer destructer
	CravingMonster();
	~CravingMonster();

	// delete Function
	CravingMonster(const CravingMonster& _Other) = delete;
	CravingMonster(CravingMonster&& _Other) noexcept = delete;
	CravingMonster& operator = (const CravingMonster& _Other) = delete;
	CravingMonster& operator = (CravingMonster&& _Other) noexcept = delete;
	
	void Hit(long long _Damage, bool _Attack) override;

	long long &GetMonsterHp()
	{
		return Hp;
	}

protected:
	void Start();
	void Update(float _Delta) override;

	void StandStart() override;
	void AttackUpdate(float _Delta) override;
	
	void DieStart() override;
	void DieingStart() override;
	void DieingEnd() override;
	void DeathUpdate(float _Delta) override;

	void AttackEvent(float _Delta);

	/*void StateUpdate(float _Delta);

	void RegenStart();
	void RegenUpdate(float _Delta);

	void StandStart();
	void StandUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DieStart();
	void DieUpdate(float _Delta);

	void DieingStart();
	void DieingUpdate(float _Delta);

	void AwakeStart();
	void AwakeUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void ChangeState(CravingState _State);
	void ChangeAnimationState(const std::string& _StateName);*/

private:
	float MoveSpeed = 70.0f;
	long long Hp = 10000000;
	int Defense = 300;
	float LeftCheck = 100.0f;
	float RightCheck = 1750.0f;

	float DeathTime = 0.0f;
	float RegenCool = 10.0f;
	float AttackCool = 6.0f;
	float Attacking = 1.0f;
	float AttackStart = 0.0f;
	float AttackEnd = 1.3f;
	bool IsAttack = false;

	int DeathCount = 3;

	std::shared_ptr<GameEngineCollision> CravingSkillCol;
	std::shared_ptr<GameEngineCollision> CravingDieCol;
	std::shared_ptr<GameEngineCollision> CravingAttackRangeCol;


	//std::shared_ptr<GameEngineSpriteRenderer> CravingMob;

};

