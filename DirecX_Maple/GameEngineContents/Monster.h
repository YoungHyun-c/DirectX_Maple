#pragma once
//#include <GameEngineCore/GameEngineActor.h>
#include "MonsterFunction.h"

// Ό³Έν :
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

	long long GetMonsterHp(long long _Value)
	{
		return MonsterHp += _Value;
	}
	long long GetMonsterHp()
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

	void Hit(long long _Damage, bool _Attack) override;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	//void CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other);

private:
	long long MonsterHp = 0;
	bool MonsterAppear = false;
	float4 MonsterScale = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;	

	bool RenderOn = false;

	std::shared_ptr<class BossBindEffect> SkillBindEffect = nullptr;

	bool Bind = false;
	float Binding = 0.0f;
	float BindTIme = 10.0f;
};

