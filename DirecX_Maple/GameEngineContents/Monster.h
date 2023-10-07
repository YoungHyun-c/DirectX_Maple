#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Monster : public GameEngineActor
{
public:
	static Monster* Monsters;
public:
	// constructer destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator = (const Monster& _Other) = delete;
	Monster& operator = (Monster&& _Other) noexcept = delete;

	int GetMonsterHp(int _Value)
	{
		return MonsterHp += _Value;
	}
	int GetMonsterHp()
	{
		return MonsterHp;
	}

	void RendererOn()
	{
		RenderOn = true;
	}

	void RendererOff()
	{
		RenderOn = false;
	}

	bool MonsterAppear = false;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	float4 PlayerScale = float4::ZERO;
	float4 PlayerPos = float4::ZERO;

	int MonsterHp = 10;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<GameEngineCollision> Col;

	bool RenderOn = false;
};

