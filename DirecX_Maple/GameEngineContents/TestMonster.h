#pragma once
#include "MonsterFunction.h"

// Ό³Έν :
class TestMonster : public MonsterFunction
{
public:
	// constructer destructer
	TestMonster();
	~TestMonster();

	// delete Function
	TestMonster(const TestMonster& _Other) = delete;
	TestMonster(TestMonster&& _Other) noexcept = delete;
	TestMonster& operator = (const TestMonster& _Other) = delete;
	TestMonster& operator = (TestMonster&& _Other) noexcept = delete;

	void Hit(long long _Damage, bool _Attack) override;

protected:

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void Start();
	void Update(float _Delta) override;

private:
	float MoveSpeed = 100.0f;

};

