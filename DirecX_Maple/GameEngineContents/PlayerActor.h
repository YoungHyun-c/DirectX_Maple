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
		//DebugMap = GameEngineTexture::Find(_DebugMapName);
		DebugMapName = _DebugMapName;
	}

	void GravityReset()
	{
		GravityForce = 0.0f;
	}

	void CameraFocus(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };
	std::string DebugMapName;

	float CameraSpeed = 2.0f;

};

