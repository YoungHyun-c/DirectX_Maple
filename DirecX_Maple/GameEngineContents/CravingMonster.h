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
	
	//void Hit(int _Damage, bool _IsRealAttack) override;

protected:
	void Start();
	void Update(float _Delta) override;

	void DeathUpdate(float _Delta) override;
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

	//void DirCheck();

private:
	//void Start() override;
	//void Update(float _Delta) override;

	//ActorDir Dir = ActorDir::Max;
	//CravingState State = CravingState::Max;
	//std::string CurState = "";
	//std::string AnimationName = "";

	//float M_FMoveTime = 0.0f;
	//float M_FMoveLinitTime = 6.0f;
	//float M_FStopTime = 0.0f;
	//float M_FStopLimiTime = 2.0f;
	//int idx = rand() % 2;

	float MoveSpeed = 70.0f;
	int Hp = 10000000;
	int Defense = 300;
	float LeftCheck = 100.0f;
	float RightCheck = 1750.0f;
	float4 GroundCheck = { 0.0f, -10.0f };
	float4 UpCheck = { 0.0f, 50.0f };
	//std::shared_ptr<GameEngineSpriteRenderer> CravingMob;

};

