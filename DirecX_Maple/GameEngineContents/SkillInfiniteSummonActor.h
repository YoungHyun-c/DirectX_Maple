#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class InfiOrderState
{
	Start,
	Attack,
	Hit,
	Loop,
	TelePort,
	Death,
	Max,
};

// 설명 :
class SkillInfiniteSummonActor : public GameEngineActor
{
public:
	// constructer destructer
	SkillInfiniteSummonActor();
	~SkillInfiniteSummonActor();

	// delete Function
	SkillInfiniteSummonActor(const SkillInfiniteSummonActor& _Other) = delete;
	SkillInfiniteSummonActor(SkillInfiniteSummonActor&& _Other) noexcept = delete;
	SkillInfiniteSummonActor& operator = (const SkillInfiniteSummonActor& _Other) = delete;
	SkillInfiniteSummonActor& operator = (SkillInfiniteSummonActor&& _Other) noexcept = delete;

	void ChangeState(InfiOrderState _State);
	void StateUpdate(float _Delta);

	float4 GetMoveVector()
	{
		return MoveVector;
	}

protected:

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void ReadyStart();
	void AttackStart();
	void HitStart();
	void TelePortStart();
	void DeathStart();

	void ReadyUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void TelePortUpdate(float _Delta);
	virtual void DeathUpdate(float _Delta);

	std::shared_ptr<class GameEngineSpriteRenderer> InfiOrder = nullptr;
	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<GameEngineCollision> HitCollision;

	std::string OrderName = "";
	float AttackTime = 0.1f;
	float HitTime = 0.0f;
	float LiveTime = 30.0f;
	float DirAngle = 0.0f;
	float Speed = 1000.0f;
	float RotationSpeed = 0.0f;

	int InfiOrderHitCount = 2;

	InfiOrderState State = InfiOrderState::Start;
	float4 MoveVector = float4::ZERO;
	float4 CurPlayerPos = float4::ZERO;
	float4 GedderingPos = float4::ZERO;

	// 오더 텔레포트
	float TelePortTime = 0.0f;
	float TelePortLimitTime = 2.0f;
	GameEngineRandom Random_XRange;
	GameEngineRandom Random_YRange;
	float TelePort_X = 0.0f;
	float TelePort_Y = 0.0f;

private:
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;
};

