#pragma once
#include "MonsterFunction.h"

// 설명 :
class JinHillaBoss : public MonsterFunction
{
public:
	// constructer destructer
	JinHillaBoss();
	~JinHillaBoss();

	// delete Function
	JinHillaBoss(const JinHillaBoss& _Other) = delete;
	JinHillaBoss(JinHillaBoss&& _Other) noexcept = delete;
	JinHillaBoss& operator = (const JinHillaBoss& _Other) = delete;
	JinHillaBoss& operator = (JinHillaBoss&& _Other) noexcept = delete;

	void Hit(long long _Damage, bool _Attack) override;

protected:
	void Start();
	void Update(float _Delta) override;

	void StandStart() override;

	void AttackStart() override;
	void AttackUpdate(float _Delta) override;

	void AttackEvent(float _Delta);

private:
	ActorDir Dir = ActorDir::Max;

	float MoveSpeed = 50.0f;
	long long JinHillaHp = 176000000000000; // 하드 176조
	int Defense = 300;
	float LeftCheck = 100.0f;
	float RightCheck = 1750.0f;

	float AppearCool = 1.5f;
	float StartAttack = 0.0f;
	float AttackCool = 6.0f;

	std::shared_ptr<GameEngineCollision> JinHillaAttackRangeCol;


	bool IsAttack = false;

};

