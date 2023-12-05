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

// Ό³Έν :
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

	virtual void ReadyStart();
	virtual void AttackStart();
	virtual void HitStart();
	virtual void LoopStart();
	virtual void TelePortStart();
	virtual void GedderingStart();
	virtual void BlossomStart();
	virtual void DeathStart();

	void ReadyUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void LoopUpdate(float _Delta);
	void TelePortUpdate(float _Delta);
	void GedderingUpdate(float _Delta);
	void BlossomUpdate(float _Delta);
	virtual void DeathUpdate(float _Delta);

	std::shared_ptr<class GameEngineSpriteRenderer> Order = nullptr;
	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<GameEngineCollision> HitCollision;

	std::string OrderName = "";
	float AppearTime = 0.0f;
	float AttackTime = 0.1f;
	float HitTime = 0.0f;
	float LiveTime = 10.0f;
	float DirAngle = 0.0f;
	float Speed = 1000.0f;
	float RotationSpeed = 0.0f;
	size_t OrderHitCount = 2;

	OrderState State = OrderState::Start;
	float4 MoveVector = float4::ZERO;
	float4 CurPlayerPos = float4::ZERO;

private:
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;
};

