#include "PreCompile.h"

#include "Player.h"
#include "Monster.h"

#include "MonsterFunction.h"
#include "BossBindEffect.h"
#include "BossFormerEffect.h"

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


		Renderer->ChangeAnimation("Mugong_Appear");
		Renderer->Transform.SetLocalPosition({ 0.0f, 100.0f });
		Renderer->SetPivotType(PivotType::Center);

		Renderer->AutoSpriteSizeOn();
		Renderer->Off();


		{
			MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
			MonsterCollision->Transform.SetLocalPosition({ -30.0f, 50.0f });
			MonsterCollision->Transform.SetLocalScale({ 200.0f, 230.0f });
			MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
			MonsterCollision->SetName(std::string("Mugong"));
			MonsterCollision->Off();
		}

	}

	SkillBindEffect = GetLevel()->CreateActor<BossBindEffect>(ContentsObjectType::FrontSkill);
	SkillBindEffect->Off();

	FormBindEffect = GetLevel()->CreateActor<BossFormerEffect>(ContentsObjectType::FrontSkill);
	FormBindEffect->Off();

	GameEngineInput::AddInputObject(this);
}

void Monster::Update(float _Delta)
{
	
	if (SkillBinding >= SkillBindTIme)
	{
		SkillBindEffect->GetEndBindEffect();
		SkillBinding = 0.0f;
		SkillBind = false;
	}
	if (SkillBind == true)
	{
		SkillBinding += _Delta;
	}
	if (GameEngineInput::IsDown(VK_HOME, this) && MonsterAppear == true)
	{
		SkillBindEffect->Transform.SetLocalPosition(Renderer->Transform.GetWorldPosition()-30.0f);
		SkillBindEffect->GetStartBindEffect();
		SkillBindEffect->On();
		SkillBind = true;
	}

	if (FormerBinding >= FormerBindTIme)
	{
		FormBindEffect->GetEndFormerBindEffect();
		FormerBinding = 0.0f;
		FormerBind = false;
	}

	if (FormerBind == true)
	{
		FormerBinding += _Delta;
	}
	if (GameEngineInput::IsDown('R', this) && MonsterAppear == true)
	{
		FormBindEffect->Transform.SetLocalPosition(Renderer->Transform.GetWorldPosition() - 30.0f);
		FormBindEffect->GetStartFormerBindEffect();
		FormBindEffect->On();
		FormerBind = true;
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
}

void Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	//Monsters = this;
	//MonsterHp = 100000000000;
}

void Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Monster::Hit(long long _Damage, bool _Attack)
{
	return;
}