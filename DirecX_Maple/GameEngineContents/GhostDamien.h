#pragma once
#include "MonsterFunction.h"

// Ό³Έν :
class GhostDamien : public MonsterFunction
{
public:
	static GhostDamien* SummonDamien;
public:
	// constructer destructer
	GhostDamien();
	~GhostDamien();

	// delete Function
	GhostDamien(const GhostDamien& _Other) = delete;
	GhostDamien(GhostDamien&& _Other) noexcept = delete;
	GhostDamien& operator = (const GhostDamien& _Other) = delete;
	GhostDamien& operator = (GhostDamien&& _Other) noexcept = delete;

	void Hit(long long _Damage, bool _Attack) override;

	void CallRegen() override;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void Start()override;
	void Update(float _Delta) override;

	//void RegenUpdate(float _Delta);
	
	void StandStart() override;
	void StandUpdate(float _Delta) override;

	void AttackStart() override;
	void AttackUpdate(float _Delta) override;

	void Skill_1Start() override;
	void Skill_1After() override;
	void Skill_1AfterUpdate(float _Delta)override;

	void Skill_2Start() override;
	void Skill_2Update(float _Delta) override;
	void Skill_2After() override;
	void Skill_2AfterUpdate(float _Delta) override;

	void DeathStart();
	void DeathUpdate(float _Delta);

	void AttackEvent(float _Delta);

private:
	void DamienDirCheck();
	void InsideLockMap();
	float4 DamienBossScale = float4::ZERO;
	float MoveSpeed = 70.0f;
	float SlideSpeed = 200.0f;
	long long Hp = 18688692000;
	int Defense = 300;
	float LeftCheck = 100.0f;
	float RightCheck = 1700.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> HitEffect;

	std::shared_ptr<GameEngineCollision> DamienAttackRangeCol;
	std::shared_ptr<GameEngineCollision> SlideAttackCol;
	void CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup);
	std::shared_ptr<GameEngineCollision> HewAttackCol;

	float AttackCool = 6.0f;
	float StartAttack = 0.0f;
	bool IsAttack = false;
	bool SlideAttack = false;
};

