#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class OrderState
{
	Start,
	Attack,
	Hit,
	Loop,
	TelePort,
	Geddering,
	Blossom,
	Death,
	Max,
};

// 설명 :
class SkillOrderSummonActor : public GameEngineActor
{
public:
	// constructer destructer
	SkillOrderSummonActor();
	~SkillOrderSummonActor();

	// delete Function
	SkillOrderSummonActor(const SkillOrderSummonActor& _Other) = delete;
	SkillOrderSummonActor(SkillOrderSummonActor&& _Other) noexcept = delete;
	SkillOrderSummonActor& operator = (const SkillOrderSummonActor& _Other) = delete;
	SkillOrderSummonActor& operator = (SkillOrderSummonActor&& _Other) noexcept = delete;

	void ChangeState(OrderState _State);
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
	void LoopStart();
	void TelePortStart();
	void GedderingStart();
	void BlossomStart();
	void DeathStart();

	void ReadyUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void LoopUpdate(float _Delta);
	void TelePortUpdate(float _Delta);
	void GedderingUpdate(float _Delta);
	void BlossomUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	std::shared_ptr<class GameEngineSpriteRenderer> Order = nullptr;
	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<GameEngineCollision> HitCollision;
	std::shared_ptr<GameEngineCollision> GedderingHitCollision;
	std::shared_ptr<GameEngineCollision> BlossomHitCollision;

	std::string OrderName = "";
	//float AppearTime = 0.0f;
	float AttackTime = 0.1f;
	float HitTime = 0.0f;
	float LiveTime = 40.0f;
	float DirAngle = 0.0f;
	float Speed = 1000.0f;
	float RotationSpeed = 0.0f;
	size_t OrderHitCount = 2;
	size_t GedderingHitCount = 4;
	size_t BlossomHitCount = 8;

	OrderState State = OrderState::Start;
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

	// 오더 게더링
	float4 GedderingDir = float4::ZERO;

	// 게더링 블로섬 어택
	void AttackEvent();
	EventParameter GedderingHitEvent;
	EventParameter BlossomHitEvent;
	bool BlossomHit = false;

private:
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;

	GameEngineSoundPlayer GedderingPlay;
	GameEngineSoundPlayer BlossomPlay;
};

