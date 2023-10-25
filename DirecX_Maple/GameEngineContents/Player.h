#pragma once
#include <GameEngineCore/GameEngineState.h>


// 게임내에서 등장하는 모든 
// 선생님한테 스킬을 만들라고 하면 고려하는 것들.
// class SkillDataManager {
//		std::map<std::string, GameEngineState> GameAllSkillMap;
// }

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

struct KnockBackInfo
{
	float4 Dir;
	float Distance;
	float Speed;
	float MinTime;
	float Time = 0.0f;
};

#include "PlayerActor.h"
#include "AdeleSkill.h"
#include "DamageRenderer.h"

class Player : public PlayerActor
{
	friend class AdeleSkill;
	friend class DamageRenderer;
	friend class PlayerValue;
private:
	static Player* MainPlayer;
public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

	inline float4 GetPlayerScale() const
	{
		return PlayerScale;
	}

	inline float4 GetPlayerPos() const
	{
		return PlayerPos;
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

	void PlayerEnterBind()
	{
		Bind = true;
	}

	void PlayerEnterBindEnd()
	{
		Bind = false;
	}

	// 스킬을 맞았을때의 기능
	void PlayerBind(float _Time = 1.0f);
	void KnockBack(float4 _Dir, float _Distance, float _Speed, float _MinTime);

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

	// SkillUpdate();

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

	std::shared_ptr<GameEngineCollision> PlayerCol;

	float4 Pos = float4::ZERO;
	float4 GroundCheck = { 0.0f, -10.0f };
	float4 UpCheck = { 0.0f, 50.0f };
	float4 PlayerScale = float4::ZERO;
	float4 PlayerPos = float4::ZERO;
	float4 LeftCheck = { -20.0f, 0.0f };
	float4 RightCheck = { 20.0f, 0.0f };
	GameEngineColor CheckColor = DefaultGroundColor;
	float4 CurMapScale = float4::ZERO;
	void InsideLockMap();

	float WalkSpeed = 300.0f;
	bool GroundJump = false;
	bool DoubleJump = false;
	float JumpAirSpeed = 30.0f;
	float AirSpeed = 200.0f;

	static Player* CurPlayer;


	bool Bind = false;
	float BindTime = 0.0f;
	float BindLimitTime = 1.5f;
	float CurTime = 0.0f;

	std::shared_ptr<KnockBackInfo> MyKnockBackInfo = nullptr;
	void KnockBackUpdate(float _Delta);
	bool isKnockBack = false;

	float PrevTime = 0.0f;
	float TimeCount = 0.0f;

	// 여기안에 넣어놓은
	// 스킬중 그 어떤거라도 사용하면 무조건 스킬로 상태가 체인지 되면 된다.
	// 누르는 키

	//class Skill 
	//{
	//public:
	//	bool IsControll;
	//    float MaxCoolTime;
	//    float CurCoolTime;
	//	float4 SkillUsePos;
	//	int TargetCollisionOrder;
	//	GameEngineState State;

	//	// void CoolUpdate();

	//	void Update(float _Delta) 
	//	{
	//		State.Update(_Delta);
	//	}
	//};

	//bool SkillUseCheck();
	//Skill* CurSkill = nullptr;
	//std::map<int, Skill > SkillState;
};