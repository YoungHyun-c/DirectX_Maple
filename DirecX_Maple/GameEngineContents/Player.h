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

enum class PlayerClothes
{
	Battle,
	Normal,
	Max,
};


#include "PlayerActor.h"
#include "AdeleSkill.h"
#include "DamageRenderer.h"

class Player : public PlayerActor
{
	friend class AdeleSkill;
	friend class DamageRenderer;
public:
	static Player* MainPlayer;
public:
	inline float4 GetPlayerScale() const
	{
		return PlayerScale;
	}

	inline ActorDir GetDir()
	{
		return Dir;
	}

	float4 GetPlayerTransform()
	{
		return Pos;
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

	// 엑터로 이동
	//void SetDebugMap(std::string_view _DebugMapName)
	//{
	//	//DebugMap = GameEngineTexture::Find(_DebugMapName);
	//	DebugMapName = _DebugMapName;
	//}

	//void GravityReset()
	//{
	//	GravityForce = 0.0f;
	//}

	void AddPos(float4 _Pos)
	{
		Pos += _Pos;
	}

protected:
	void StateUpdate(float _Delta);

	void StandStart();
	void StandUpdate(float _Delta);
	void StandEnd();

	void WalkStart();
	void WalkUpdate(float _Delta);
	void WalkEnd();

	void AlertStart();
	void AlertUpdate(float _Delta);
	//void AlertEnd();

	void ProneStart();
	void ProneUpdate(float _Delta);
	//void ProneEnd();

	void AttackStart();
	void AttackUpdate(float _Delta);
	void AttackEnd();

	void ProneAttackStart();
	void ProneAttackUpdate(float _Delta);
	//void ProneAttackEnd();

	void JumpStart();
	void JumpUpdate(float _Delta);
	void JumpEnd();

	void DoubleJumpStart();
	void DoubleJumpUpdate(float _Delta);
	//void DoubleJumpEnd();

	void FlyStart();
	void FlyUpdate(float _Delta);
	//void FlyEnd();

	void DeadStart();
	void DeadUpdate(float _Delta);
	//void DeadEnd();

	// 스킬관련
	//void BoltJump();
	bool IsAttack = false;
	std::shared_ptr<class GameEngineCollision> RangeCheck = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCol;
	int a = 0;

	void ChangeState(PlayerState _State);
	void ChangeAnimationState(const std::string& _StateName);

	ActorDir Dir = ActorDir::Max;
	PlayerState State = PlayerState::Max;
	PlayerClothes Clothes = PlayerClothes::Max;
	std::string CurState = "";
	std::string AnimationName = "";

	void DirCheck();
	
private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer;
	std::shared_ptr<class GameEngineComponenet> TestCollision;

	// 엑터로 이동
	//std::shared_ptr<GameEngineTexture> DebugMap;
	/*std::string DebugMapName;
	float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };*/

	std::shared_ptr<GameEngineCollision> Col;

	float4 Pos = float4::ZERO;
	float4 GroundCheck = { 0.0f, -10.0f };
	float4 PlayerScale = float4::ZERO;

	float WalkSpeed = 300.0f;
	bool GroundJump = false;
	bool DoubleJump = false;
	float JumpAirSpeed = 30.0f;
	float AirSpeed = 200.0f;

	static Player* CurPlayer;

};

