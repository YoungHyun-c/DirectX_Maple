#pragma once
#include "MonsterFunction.h"

// Ό³Έν :
class GhostSwoo : public MonsterFunction
{
public:
	static GhostSwoo* SummonSwoo;
public:
	// constructer destructer
	GhostSwoo();
	~GhostSwoo();

	// delete Function
	GhostSwoo(const GhostSwoo& _Other) = delete;
	GhostSwoo(GhostSwoo&& _Other) noexcept = delete;
	GhostSwoo& operator = (const GhostSwoo& _Other) = delete;
	GhostSwoo& operator = (GhostSwoo&& _Other) noexcept = delete;

	void Hit(long long _Damage, bool _Attack) override;

	void CallRegen() override;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start()override;
	void Update(float _Delta) override;
	
	void StandStart() override;
	void StandUpdate(float _Delta) override;

	void AttackStart() override;
	void AttackUpdate(float _Delta) override;

	void Skill_1Start() override;
	void Skill_1After() override;
	void Skill_1AfterUpdate(float _Delta) override;

	void DeathStart();
	void DeathUpdate(float _Delta);

	void AttackEvent(float _Delta);

private:
	//void InsideLockMap();

	float MoveSpeed = 50.0f;
	long long Hp = 18688692000;
	int Defense = 300;
	float LeftCheck = 100.0f;
	float RightCheck = 1700.0f;

	std::shared_ptr<GameEngineCollision> SwooAttackRangeCol;
	std::shared_ptr<GameEngineCollision> SwooAttackCol;
	void CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup);


	float AttackCool = 6.0f;
	float StartAttack = 0.0f;
	bool IsAttack = false;
	int AttackNum = 1;
};


//std::shared_ptr<class GameEngineSpriteRenderer> BallSprite;