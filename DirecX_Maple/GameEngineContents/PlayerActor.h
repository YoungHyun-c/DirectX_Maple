#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerActor : public GameEngineActor
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

	inline void MoveVectorForceReset()
	{
		MoveVectorForce = float4::ZERO;
	}

	void AddMoveVectorForce(float4 _Force)
	{
		MoveVectorForce += _Force;
	}

	const float4 GetMoveVectorForce()
	{
		return MoveVectorForce;
	}


	void Gravity(float _Delta);
	void CameraFocus(float _Delta);

	GameEngineColor CheckGroundColor(float4 _CheckPos = float4::ZERO);
	bool CheckGround(float4 _CheckPos = float4::ZERO);

protected:
	void Start() override;
	void Update(float _Delta) override;

	bool IsGround = true;
	bool CameraFocusValue = false;
	std::shared_ptr<class GameEngineCamera> IsCameraFocus = nullptr;
private:
	bool IsGravity = true;
	//float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };
	float GravityForce = 0.0f;
	float GravityPower = 2300.0f;
	float MaxGravity = 2000.0f;
	std::string DebugMapName;
	std::shared_ptr<GameEngineTexture> DebugMap;

	float CameraSpeed = 2.0f;
	float4 MoveVectorForce = float4::ZERO;
};

