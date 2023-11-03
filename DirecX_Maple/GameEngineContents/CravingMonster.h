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

	int GetMonsterDeathCount()
	{
		return DeathCount;
	}

	void CallRegen() override;
	void CallDie();

protected:
	void LevelEnd(GameEngineLevel* NexLevel) override;

	void Start() override;
	void Update(float _Delta) override;

	void StandStart() override;
	void AttackUpdate(float _Delta) override;
	
	void DieStart() override;
	void DieingStart() override;
	void DieingEnd() override;
	void DeathStart() override;
	void DeathUpdate(float _Delta) override;

	void AttackEvent(float _Delta);

private:
	float MoveSpeed = 70.0f;
	long long Hp = 10000000;
	int Defense = 300;
	float LeftCheck = 100.0f;
	float RightCheck = 1750.0f;

	float DeathTime = 0.0f;
	float RegenCool = 10.0f;
	float AttackCool = 6.0f;

	float AttackStart = 0.0f;

	bool IsAttack = false;

	int DeathCount = 3;

	std::shared_ptr<GameEngineCollision> CravingSkillCol;
	std::shared_ptr<GameEngineCollision> CravingDieCol;
	std::shared_ptr<GameEngineCollision> CravingAttackRangeCol;


	//std::shared_ptr<GameEngineSpriteRenderer> CravingMob;
	
	std::string CurState = "";
};

