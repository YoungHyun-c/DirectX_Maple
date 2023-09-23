#pragma once


enum class PlayerState
{
	Stand,
	Walk,
	Alert,
	Prone,
	Attack,
	ProneAttack,
	Jump,
	DoubleJump,
	Fly,
	Dead,
	Max,
};

enum class PlayerDir
{
	Right,
	Left,
	Max,
};

#include "PlayerActor.h"

class Player : public PlayerActor
{
public:
	static Player* MainPlayer;

public:
	static Player* GetMainPlyer()
	{
		return MainPlayer;
	}

	// constructer destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator = (const Player& _Other) = delete;
	Player& operator = (Player&& _Other) noexcept = delete;

	void TestEvent(GameEngineRenderer* _Renderer);

	//void SetDebugMap(std::string_view _DebugMapName)
	//{
	//	//DebugMap = GameEngineTexture::Find(_DebugMapName);
	//	DebugMapName = _DebugMapName;
	//}

	void AddPos(float4 _Pos)
	{
		Pos += _Pos;
	}

protected:
	void StateUpdate(float _Delta);

	void StandStart();
	void StandUpdate(float _Delta);

	void WalkStart();
	void WalkUpdate(float _Delta);

	void AlertStart();
	void AlertUpdate(float _Delta);

	void ProneStart();
	void ProneUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void ProneAttackStart();
	void ProneAttackUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void DoubleJumpStart();
	void DoubleJumpUpdate(float _Delta);

	void FlyStart();
	void FlyUpdate(float _Delta);

	void DeadStart();
	void DeadUpdate(float _Delta);

	void ChangeState(PlayerState _State);

	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Max;
	std::string CurState = "";
	std::string AnimationName = "";

	void DirCheck();

	void ChangeAnimationState(const std::string& _StateName);
	
private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<class GameEngineComponenet> TestCollision;

	std::shared_ptr<GameEngineTexture> DebugMap;
	//std::string DebugMapName;
	//float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };

	std::shared_ptr<GameEngineCollision> Col;

	float4 Pos;
	float4 GroundCheck = { 0.0f, -10.0f };

	float WalkSpeed = 400.0f;

};

