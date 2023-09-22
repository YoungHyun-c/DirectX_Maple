#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	Idle,
	Run,
	Jump,
	DoubleJump,
	Prone,
	ProneAttack,
	Attack,
	Max,
};

enum class PlayerDir
{
	Right,
	Left,
	Max,
};

// Ό³Έν :
class Player : public GameEngineActor
{
public:
	// constructer destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator = (const Player& _Other) = delete;
	Player& operator = (Player&& _Other) noexcept = delete;

	void TestEvent(GameEngineRenderer* _Renderer);

	void SetDebugMap(std::string_view _DebugMapName)
	{
		//DebugMap = GameEngineTexture::Find(_DebugMapName);
		DebugMapName = _DebugMapName;
	}

	void AddPos(float4 _Pos)
	{
		Pos += _Pos;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<class GameEngineComponenet> TestCollision;

	std::shared_ptr<GameEngineTexture> DebugMap;
	std::string DebugMapName;
	float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };

	std::shared_ptr<GameEngineCollision> Col;

	float4 Pos;
};

