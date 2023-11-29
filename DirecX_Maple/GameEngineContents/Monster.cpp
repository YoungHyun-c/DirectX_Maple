#include "PreCompile.h"

#include "Player.h"
#include "Monster.h"

#include "BossBindEffect.h"
#include "MonsterFunction.h"

Monster* Monster::Monsters = nullptr;

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
		Renderer->CreateAnimation("Mugong_Appear", "Mugong_Appear", 0.1f, -1, -1, false);
		Renderer->CreateAnimation("Mugong_Disappear", "Mugong_Disappear", 0.1f, -1, -1, false);
		Renderer->CreateAnimation("Mugong_Idle", "Mugong_Idle");
		Renderer->ChangeAnimation("Mugong_Idle");

		Renderer->AutoSpriteSizeOn();
		Renderer->Off();


		{
			MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
			MonsterCollision->Transform.SetLocalPosition({ -30.0f, 0.0f });
			MonsterCollision->Transform.SetLocalScale({ 300.0f, 330.0f });
			MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
			MonsterCollision->SetName(std::string("Mugong"));
			MonsterCollision->Off();
		}

	}

	SkillBindEffect = GetLevel()->CreateActor<BossBindEffect>(ContentsObjectType::FrontSkill);
	SkillBindEffect->Off();
	GameEngineInput::AddInputObject(this);
}

void Monster::Update(float _Delta)
{
	
	if (Binding >= BindTIme)
	{
		SkillBindEffect->GetEndBindEffect();
		Binding = 0.0f;
		Bind = false;
	}

	if (Bind == true)
	{
		Binding += _Delta;
	}
	if (GameEngineInput::IsDown(VK_HOME, this))
	{
		SkillBindEffect->Transform.SetLocalPosition(Renderer->Transform.GetWorldPosition()-30.0f);
		SkillBindEffect->GetStartBindEffect();
		SkillBindEffect->On();
		Bind = true;
	}

	if (RenderOn == true && MonsterAppear == false)
	{
		Renderer->ChangeAnimation("Mugong_Appear");
		Renderer->On();
		MonsterCollision->On();
		MonsterAppear = true;
	}
	else if (RenderOn == false && MonsterAppear == true)
	{
		Renderer->ChangeAnimation("Mugong_Disappear");
		MonsterCollision->Off();
		if (true == Renderer->IsCurAnimationEnd())
		{
			MonsterAppear = false;
			Renderer->Off();
		}
	}
	
	//MonsterCollision->CollisionEvent(ContentsCollisionType::Skill, MonsterEvent);
}

void Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	//Monsters = this;
	MonsterHp = 100000000000;
	//{
	//	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	//	Renderer->CreateAnimation("Mugong_Appear", "Mugong_Appear", 0.1f, -1, -1, false);
	//	Renderer->CreateAnimation("Mugong_Disappear", "Mugong_Disappear", 0.1f, -1, -1, false);
	//	Renderer->CreateAnimation("Mugong_Idle", "Mugong_Idle");
	//	Renderer->ChangeAnimation("Mugong_Idle");

	//	Renderer->AutoSpriteSizeOn();
	//	Renderer->Off();


	//	{
	//		MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
	//		MonsterCollision->Transform.SetLocalPosition({ -30.0f, 0.0f });
	//		MonsterCollision->Transform.SetLocalScale({300.0f, 330.0f});
	//		MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
	//		MonsterCollision->SetName(std::string("Mugong"));
	//		MonsterCollision->Off();
	//	}

	//}
}

void Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Monster::Hit(long long _Damage, bool _Attack)
{
	return;
}