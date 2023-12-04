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
	SwingB,
	SwingY,
	Maestro,
	ProneAttack,
	Jump,
	Rope,
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

	void PlayerCollisionOff()
	{
		PlayerCol->Off();
	}

	void PlayerCollisionOn()
	{
		PlayerCol->On();
	}

	bool GetBindValue()
	{
		return Bind;
	}

	void PlayerHit(float _Damage, bool _Attack);


	// 스킬을 맞았을때의 기능
	void PlayerBind(float _Time = 1.0f);
	void KnockBack(float4 _Dir, float _Distance, float _Speed, float _MinTime);

	void GetItem();

	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _StateName);
protected:
	void ChangeToStand();

	void StandStart();
	void StandEnd();
	void StandUpdate(float _Delta);

	void WalkStart();
	void WalkEnd();
	void WalkUpdate(float _Delta);

	void AlertStart();
	void AlertEnd();
	void AlertUpdate(float _Delta);

	void ProneStart();
	void ProneEnd();
	void ProneUpdate(float _Delta);

	void AttackStart();
	void AttackEnd();
	void AttackUpdate(float _Delta);

	void ProneAttackStart();
	void ProneAttackEnd();
	void ProneAttackUpdate(float _Delta);

	void JumpStart();
	void JumpEnd();
	void JumpUpdate(float _Delta);

	void RopeStart();
	void RopeEnd();
	void RopeUpdate(float _Delta);


	void FlyStart();
	void FlyEnd();
	void FlyUpdate(float _Delta);
	void FlyCheckUpdate();

	void DeadStart();
	void DeadEnd();
	void DeadUpdate(float _Delta);

	// SkillUpdate();

	void SwingBStart();
	void SwingBUpdate(float _Delta);
	void SwingBEnd();

	void SwingYStart();
	void SwingYUpdate(float _Delta);
	void SwingYEnd();
	
	void MaestroStart();
	void MaestroUpdate(float _Delta);
	void MaestroEnd();

	// 스킬관련
	//void BoltJump();
	bool IsAttack = false;
	std::shared_ptr<class GameEngineCollision> RangeCheck = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCol;

	ActorDir Dir = ActorDir::Max;
	PlayerClothes Clothes = PlayerClothes::Max;
	PlayerState State = PlayerState::Max;
	std::string AnimationName = "";

	void DirCheck();
	void RopeCheck();
	bool IsRope = false;

	//bool CheckGround(float4 _CheckPos = float4::ZERO) override;
	
	void InsideLockMap();
private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;

	std::shared_ptr<GameEngineCollision> PlayerCol;
	std::shared_ptr<GameEngineCollision> PlayerDropCol;

	float4 Pos = float4::ZERO;
	float4 PlayerPos = float4::ZERO;
	float4 GroundCheck = { 0.0f, -35.0f };
	float4 UpCheck = { 0.0f, 50.0f };
	float4 PlayerScale = float4::ZERO;
	float4 LeftCheck = { -20.0f, 0.0f };
	float4 RightCheck = { 20.0f, 0.0f };
	GameEngineColor CheckColor = DefaultGroundColor;
	float SkipGround = 0.0f;
	std::set<float> NotGround;
	bool IsGroundCheck = true;
	float4 CurMapScale = float4::ZERO;

	float WalkSpeed = 300.0f;
	bool GroundJump = false;
	bool DoubleJump = false;
	float JumpAirSpeed = 30.0f;
	float AirSpeed = 200.0f;
	float AlertTime = 0.0f;
	float RopePivot = 0.0f;

	//// 레비테이션 공중체공 확인
	float FlyTime = 0.0f;
	float FlyLimitTime = 3.0f;
	bool Flying = false;

	bool UpClick = false;
	bool UpDoubleClick = false;
	float UpClickCount = 0.0f;
	float UpDoubleClickCount = 0.0f;
	///////////////////////////////

	bool Bind = false;
	float BindTime = 0.0f;
	float BindLimitTime = 1.5f;
	float CurTime = 0.0f;

	std::shared_ptr<KnockBackInfo> MyKnockBackInfo = nullptr;
	void KnockBackUpdate(float _Delta);
	bool isKnockBack = false;

	float PrevTime = 0.0f;
	//float KnockTimeCount = 0.0f;


	float HitDamaged = 0.0f;
	float HitDamCool = 1.3f;
	bool IsDamaged = false;

	void PotionCheck(float _Delta);
	bool AltarSuccess = false;
	float PotionLimitTime = 5.0f;


	bool Invicibility = false;
	std::shared_ptr<class InvinCibilityEffect> Invicible = nullptr;
	void InvicibleCheck();

	void Level_Up();
	std::shared_ptr<GameEngineSpriteRenderer> LevelUp = nullptr;
	std::shared_ptr<GameEngineCollision> LevelUpCol = nullptr;


	// 스킬 관련
	void SkillUseCheck(float Delta);
	float DivideTime = 0.0f;
	float DivideCool = 6.0f;

	float WonderTime = 0.0f;
	float WonderCool = 6.0f;

	float MaestroTime = 0.0f;
	float MaestroEndTime = 9.0f;
	bool MaestroUse = false;
};