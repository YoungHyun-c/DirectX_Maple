#include "PreCompile.h"

#include "Player.h"
#include "Monster.h"

Monster* Monster::Monsters;

Monster::Monster()
{
	Monsters = this;
	MonsterName = static_cast<int>(MonstersName::Mugong);
}

Monster::~Monster()
{

}

void Monster::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);

		GameEngineRandom NewRandom;

		NewRandom.SetSeed(reinterpret_cast<long long>(this));
		Renderer->SetSprite("Mugong_stand.png");

		//Renderer->Transform.SetLocalPosition({ Player::MainPlayer->Transform.GetWorldPosition() });
		Renderer->AutoSpriteSizeOn();

		//float4 Pos = float4::ZERO;
		//Pos = Transform.GetWorldPosition();
		//Renderer->Transform.SetLocalPosition(Pos);
		Renderer->Off();

		//Renderer->SetImageScale(NewRandom.RandomVectorBox2D(300, 500, 300, 500));
		//float4 Scale = NewRandom.RandomVectorBox2D(100, 100, 100, 100);
		//Col->Transform.SetLocalScale(Scale);
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		//Col->Transform.SetLocalPosition({ 0.0f, 100.0f, 1.0f });
		//Col->Transform.SetLocalPosition({ 0 , 100.0f });
		Col->Transform.SetLocalScale({ 300.0f, 300.0f, 0.0f });
		Col->Off();

	}

}

void Monster::Update(float _Delta)
{
	//GameEngineDebug::DrawBox2D(Renderer->GetImageTransform(), float4::BLUE);

	//float4 Dir = Player::MainPlayer->Transform.GetWorldPosition() - Renderer->Transform.GetWorldPosition();
	//Dir.Normalize();
	//Renderer->Transform.AddLocalPosition(Dir * _Delta * 100.0f);

	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	//if (RenderOn == true && MonsterAppear == false)
	{
		//Renderer->Transform.SetLocalPosition({ PlayerPos.X, PlayerPos.Y + 100.0f});
		Renderer->On();
		//Col->Transform.SetLocalPosition({PlayerPos.X, PlayerPos.Y + 100.0f});
		Col->On();
		MonsterAppear = true;
	}
	//else if (RenderOn == false && MonsterAppear == true)
	//{
	//	Renderer->Off();
	//	Col->Off();
	//	MonsterAppear = false;
	//}
	
	GlobalValue::CurMonsterPos = Renderer->Transform.GetWorldPosition();

}

void Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	//Monsters = this;
}