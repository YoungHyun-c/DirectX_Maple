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
		Renderer->SetSprite("Mugong_stand.png");
		Renderer->AutoSpriteSizeOn();
		Renderer->Off();

		{	
			std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Mugong_stand.Png");
			MonsterScale = Sprite->GetSpriteData(0).GetScale();
			Sprite = nullptr;
		}

		{
			Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
			//Col->Transform.SetLocalScale({ 300.0f, 300.0f, 1.0f });
			Col->Transform.SetLocalScale(MonsterScale);
			Col->SetCollisionType(ColType::AABBBOX2D);
			Col->Off();
			Col->SetName("Mugong");
		}

	}
}

void Monster::Update(float _Delta)
{
	//GameEngineDebug::DrawBox2D(Renderer->GetImageTransform(), float4::BLUE);

	//float4 Dir = Player::MainPlayer->Transform.GetWorldPosition() - Renderer->Transform.GetWorldPosition();
	//Dir.Normalize();
	//Renderer->Transform.AddLocalPosition(Dir * _Delta * 100.0f);

	// 일단 띄워놓기 용 테스트에 용이
	//float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	////if (RenderOn == true && MonsterAppear == false)
	//{
	//	//Renderer->Transform.SetLocalPosition({ PlayerPos.X, PlayerPos.Y + 100.0f});
	//	Renderer->On();
	//	//Col->Transform.SetLocalPosition({PlayerPos.X, PlayerPos.Y + 100.0f});
	//	Col->On();
	//	MonsterAppear = true;
	//}
	////else if (RenderOn == false && MonsterAppear == true)
	////{
	////	Renderer->Off();
	////	Col->Off();
	////	MonsterAppear = false;
	////}

	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	if (RenderOn == true && MonsterAppear == false)
	{
		//Renderer->Transform.SetLocalPosition({ PlayerPos.X, PlayerPos.Y + 100.0f});
		Renderer->On();
		//Col->Transform.SetLocalPosition({PlayerPos.X, PlayerPos.Y + 100.0f});
		Col->On();
		MonsterAppear = true;
	}
	else if (RenderOn == false && MonsterAppear == true)
	{
		Renderer->Off();
		Col->Off();
		MonsterAppear = false;
	}
	
	//GlobalValue::CurMonsterPos = Renderer->Transform.GetWorldPosition();
	Col->CollisionEvent(ContentsCollisionType::Skill, MonsterEvent);
}

void Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	//Monsters = this;
	MonsterHp = 100000000000;
}

void Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	//Death();
}

void Monster::Hit(long long _Damage, bool _Attack)
{

}