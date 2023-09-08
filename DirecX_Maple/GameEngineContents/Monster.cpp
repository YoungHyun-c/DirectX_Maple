#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{

}

Monster::~Monster()
{

}

void Monster::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(30);

		GameEngineRandom NewRandom;

		NewRandom.SetSeed(reinterpret_cast<long long>(this));

		Renderer->SetSprite("JinHilla.png");
		//Renderer->Transform.SetLocalPosition({ 1300.0f, -500.0f, 0 });
		Renderer->Transform.SetLocalScale({ 300.0f, 300.0f, 0.0f });
		
		//Renderer->Transform.SetLocalScale(NewRandom.RandomVectorBox2D(100, 100, 100, 100));
		//float4 Scale = NewRandom.RandomVectorBox2D(100, 100, 100, 100);
		std::shared_ptr<GameEngineCollision> Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		//Col->Transform.SetLocalScale({ 300.0f, 300.0f, 0.0f });
		//Col->Transform.SetLocalScale(Scale);
	}

}