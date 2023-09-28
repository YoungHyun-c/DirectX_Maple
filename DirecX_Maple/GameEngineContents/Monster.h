#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Monster : public GameEngineActor
{
public:
	// constructer destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator = (const Monster& _Other) = delete;
	Monster& operator = (Monster&& _Other) noexcept = delete;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	float4 PlayerScale = float4::ZERO;
	float4 PlayerPos = float4::ZERO;
private:

};

