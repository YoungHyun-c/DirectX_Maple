#pragma once
//#include <GameEngineCore/GameEngineActor.h>
#include "MonsterFunction.h"

// ���� :
class Monster : public MonsterFunction //GameEngineActor
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

	bool MonsterAppearValue()
	{
		return MonsterAppear;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	//void CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other);

private:
	EventParameter MonsterEvent;
	int MonsterHp = INT_MAX;
	bool MonsterAppear = false;
	float4 MonsterScale = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Col = nullptr;
	

	bool RenderOn = false;
};

