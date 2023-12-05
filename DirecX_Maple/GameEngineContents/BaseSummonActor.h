#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class WonderState
{
	Start,
	Attack,
	Hit,
	Death,
	Max,
};


// Ό³Έν :
class BaseSummonActor : public GameEngineActor
{
public:
	// constructer destructer
	BaseSummonActor();
	~BaseSummonActor();

	// delete Function
	BaseSummonActor(const BaseSummonActor& _Other) = delete;
	BaseSummonActor(BaseSummonActor&& _Other) noexcept = delete;
	BaseSummonActor& operator = (const BaseSummonActor& _Other) = delete;
	BaseSummonActor& operator = (BaseSummonActor&& _Other) noexcept = delete;

	//static void CreateWonder();

	void ChangeState(WonderState _State);
	void StateUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	//void Init(std::string_view _WonderName);

	virtual void ReadyStart();
	virtual void AttackStart();
	virtual void HitStart();
	virtual void DeathStart();

	void ReadyUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void HitUpdate(float _Delta);
	virtual void DeathUpdate(float _Delta);


	std::shared_ptr<class GameEngineSpriteRenderer> Wonder = nullptr;
	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<GameEngineCollision> HitCollision;

	std::string WonderName = "";
	float AppearTime = 0.0f;
	float AttackTime = 0.5f;
	float LiveTime = 6.0f;
	float DirAngle = 0.0f;
	float Speed = 800.0f;
	float RotationSpeed = 0.0f;
	size_t WonderHitCount = 3;


	WonderState State = WonderState::Start;
	float4 MoveVector = float4::ZERO;
	float4 CurPlayerPos = float4::ZERO;
private:
	std::shared_ptr<class DamageRenderer> NewDR = nullptr;

};

