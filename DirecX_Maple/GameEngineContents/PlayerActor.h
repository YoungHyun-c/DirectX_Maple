#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BasicFunction.h"

// Ό³Έν :
class PlayerActor : public BasicFunction
{
public:
	// constructer destructer
	PlayerActor();
	~PlayerActor();

	// delete Function
	PlayerActor(const PlayerActor& _Other) = delete;
	PlayerActor(PlayerActor&& _Other) noexcept = delete;
	PlayerActor& operator = (const PlayerActor& _Other) = delete;
	PlayerActor& operator = (PlayerActor&& _Other) noexcept = delete;

	void SetDebugMap(std::string_view _DebugMapName)
	{
		DebugMap = GameEngineTexture::Find(_DebugMapName);
		DebugMapName = _DebugMapName;
	}

	void GravityReset()
	{
		GravityForce = 0.0f;
	}

	void GravityOn()
	{
		IsGravity = true;
	}

	void GravityOff()
	{
		IsGravity = false;
	}

	inline void MoveVectorForceReset()
	{
		MoveVectorForce = float4::ZERO;
	}

	void AddMoveVectorForce(const float4& _Force)
	{
		MoveVectorForce += _Force;
	}

	void SetMoveVectorXForce(float _Force)
	{
		MoveVectorForce.X = _Force;
	}

	void SetMoveVectorYForce(float _Force)
	{
		MoveVectorForce.Y = _Force;
	}

	const float4 GetMoveVectorForce()
	{
		return MoveVectorForce;
	}


	void Gravity(float _Delta);
	void CameraFocus(float _Delta);

	GameEngineColor CheckGroundColor(float4 _CheckPos = float4{ 0.0f, -35.0f,1.0f});
	//virtual bool CheckGround(float4 _CheckPos = float4{0.0f, 35.0f, 1.0f});
	bool CheckGround(float4 _CheckPos = float4{ 0.0f, -35.0f, 1.0f });
	float4 MoveVectorForce = float4::ZERO;

	void CalCulateMove(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	bool IsGround = true;
	bool WallCheck = true;
	bool IsWall = false;
	bool IsGroundVectorReset = true;
	bool CameraFocusValue = false;
	std::shared_ptr<class GameEngineCamera> IsCameraFocus = nullptr;
private:
	bool IsGravity = true;

	float GravityForce = 0.0f;
	float GravityPower = 14000.0f;
	float MaxGravity = 1400.0f;
	float MaxGravitySpeed = 5.0f;
	std::string DebugMapName;
	std::shared_ptr<GameEngineTexture> DebugMap;

	float CameraSpeed = 2.0f;
};

