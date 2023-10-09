#pragma once
#include "BasicFunction.h"

enum class MonsterState
{
	Regen,
	Stand,
	Move,
	Attack,
	Skill1,
	Skill2,
	Die,
	Dieing,
	Hit,
	Awake,
	Death,
	Max,
};


class MonsterFunction : public BasicFunction
{
public:
	static MonsterFunction* MonsterFunc;
public:
	// constructer destructer
	MonsterFunction();
	~MonsterFunction();

	// delete Function
	MonsterFunction(const MonsterFunction& _Other) = delete;
	MonsterFunction(MonsterFunction&& _Other) noexcept = delete;
	MonsterFunction& operator = (const MonsterFunction& _Other) = delete;
	MonsterFunction& operator = (MonsterFunction&& _Other) noexcept = delete;

	void SetDebugMap(std::string_view _DebugMapName)
	{
		DebugMap = GameEngineTexture::Find(_DebugMapName);
		DebugMapName = _DebugMapName;
	}

	void SetMoveSpeed(float _MoveSpeed)
	{
		MoveSpeed = _MoveSpeed;
	}

	bool GetGround()
	{
		return IsGround;
	}

	//virtual void Hit(int _Damge, bool _RealAttack) = 0;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	float4 LeftCheck = { -100.0f, 0.0f };
	float4 RightCheck = { 100.0f, 0.0f };
	GameEngineColor CheckColor;
	float4 MonsterMovePos = float4::ZERO;
	float4 CurMapScale = float4::ZERO;
	float4 NextPos = float4::ZERO;
	GameEngineColor CheckSideColor(float4 CheckPos = float4::ZERO);

	std::shared_ptr<class GameEngineSpriteRenderer> MonsterRenderer;
	std::shared_ptr<class GameEngineCollision> MonsterCollision;

	int MonsterName = 0;
	ActorDir Dir = ActorDir::Left;
	MonsterState State = MonsterState::Stand;
	std::string CurState = "Stand";
	std::string AnimationName = "";

	bool IsGround = false;
	bool IsFight = false;
	bool IsDeath = false;
	bool IsAnimationEnd = false;


	void StateUpdate(float _Delta);

	virtual void RegenStart();
	virtual void RegenUpdate(float _Delta);

	virtual void StandStart();
	virtual void StandUpdate(float _Delta);
	
	virtual void MoveStart();
	virtual void MoveUpdate(float _Delta);

	virtual void AttackStart();
	virtual void AttackUpdate(float _Delta);

	virtual void DieStart();
	virtual void DieUpdate(float _Delta);

	virtual void DieingStart();
	virtual void DieingUpdate(float _Delta);

	virtual void AwakeStart();
	virtual void AwakeUpdate(float _Delta);

	virtual void DeathStart();
	virtual void DeathUpdate(float _Delta);

	virtual void Skill_1Start();
	virtual void Skill_1Update(float _Delta);

	virtual void Skill_2Start();
	virtual void Skill_2Update(float _Delta);

	void StateCheck();
	void ChangeState(MonsterState _State);
	void ChangeAnimationState(const std::string& _StateName);
	
	
	void TimeCounting();

	int Att = 0;

	float MoveSpeed = 0.0f;
	float MoveDistance = 0.0f;
	float MoveLimitDistance = 700.0f;
	float M_FStopTime = 0.0f;
	float M_FStopLimiTime = 2.0f;

	int CurStateNumber = rand() % 2;

private:
	std::string DebugMapName;
	std::shared_ptr<GameEngineTexture> DebugMap;


};

