#pragma once
#include "MonsterFunction.h"

// Ό³Έν :
class CraneMonster : public MonsterFunction
{
	friend class GlobalValue;
public:
	// constructer destructer
	CraneMonster();
	~CraneMonster();

	// delete Function
	CraneMonster(const CraneMonster& _Other) = delete;
	CraneMonster(CraneMonster&& _Other) noexcept = delete;
	CraneMonster& operator = (const CraneMonster& _Other) = delete;
	CraneMonster& operator = (CraneMonster&& _Other) noexcept = delete;

	void Hit(long long _Damage, bool _Attack) override;


protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

	void StandStart() override;
	void StandUpdate(float _Delta) override;

	void MoveStart() override;
	void MoveUpdate(float _Delta) override;

	void AttackStart() override;
	void AttackUpdate(float _Delta) override;

	void DeathStart() override;
	void DeathUpdate(float _Delta) override;

	void AttackEvent(float _Delta);

	void Spawn(float _Delta) override;

private:
	float MoveSpeed = 30.0f;
	
	long long Hp = 0;
	int Defense = 10;

	bool DeathCount = false;
	bool DeathValue = false;
	float RegenCool = 7.0f;
	float IsRegenStart = 0.0f;

	float AttackCool = 3.0f;
	float IsAttackStart = 0.0f;
	bool IsAttack = false;

	float4 CurPos = float4::ZERO;
	float4 LeftCheck = { -20.0f, 120.0f };
	float4 RightCheck = { 20.0f, 120.0f };
	float4 CheckPos = float4::ZERO;

	float MoveDistance = 0.0f;
	float MoveLimitDistance = 200.0f;

	std::shared_ptr<GameEngineCollision> CraneSkillCol;
	std::shared_ptr<GameEngineCollision> CraneAttackRangeCol;
	std::shared_ptr<GameEngineTexture> ColMap;

	void SetDropItemList();
	std::vector<std::pair<std::string, int>> DropItemList;
};

