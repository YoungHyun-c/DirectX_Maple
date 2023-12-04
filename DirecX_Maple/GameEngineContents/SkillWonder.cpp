#include "PreCompile.h"
#include "SkillWonder.h"

#include "BaseSummonActor.h"
#include "SkillWonderActor.h"

#include "Player.h"


float SkillWonder::WonderCool = 0.0f;

SkillWonder::SkillWonder()
{

}

SkillWonder::~SkillWonder()
{

}

void SkillWonder::Start()
{
	SkillFunction::Start();

	// "Maestro"
	{
		SkillRender3->CreateAnimation("Shard6Effect", "Shard6_Effect", 0.07f);

		SkillRender3->SetFrameEvent("Shard6Effect", 1, std::bind(&SkillWonder::RenderEvent, this, std::placeholders::_1));
		SkillRender3->Transform.SetLocalPosition({ 0.0f, 75.0f });
		SkillRender3->SetEndEvent("Shard6Effect", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender3->Off();
				EndSkill();
			});

		AllWonderActor.reserve(5);
		for (int i = 0; i < 5; i++)
			SkillRender3->SetFrameEvent("Shard6Effect", i, [&](GameEngineSpriteRenderer* _Renderer)
				{
					CreateWonder();
				});

		SkillRender3->SetFrameEvent("Shard6Effect", 5, [&](GameEngineSpriteRenderer* _Renderer)
			{
				WonderPosCal();
			});

	}
	{
		SkillRender3->CreateAnimation("ShardEffect", "Shard_Effect", 0.07f);

		SkillRender3->SetFrameEvent("ShardEffect", 1, std::bind(&SkillWonder::RenderEvent, this, std::placeholders::_1));
		SkillRender3->Transform.SetLocalPosition({ 0.0f, 75.0f });
		SkillRender3->SetEndEvent("ShardEffect", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender3->Off();
				EndSkill();
			}
		);

		AllWonderActor.reserve(5);
		for (int i = 0; i < 5; i++)
			SkillRender3->SetFrameEvent("ShardEffect", i, [&](GameEngineSpriteRenderer* _Renderer)
				{
					CreateWonder();
				});

		SkillRender3->SetFrameEvent("ShardEffect", 5, [&](GameEngineSpriteRenderer* _Renderer)
			{
				WonderPosCal();
			});
	}

}

void SkillWonder::Update(float _Delta)
{
	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	Transform.SetWorldPosition(CurPlayerPos);
}

void SkillWonder::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;
	On();

	ActorDir Dir = Player::GetMainPlayer()->GetDir();
	if (Dir == ActorDir::Right)
	{
		SkillRender3->LeftFlip();
	}
	if (Dir == ActorDir::Left)
	{
		SkillRender3->RightFlip();
	}

	SkillRender3->On();

	if (PlayerValue::GetValue()->GetClass() == "Maestro")
	{
		SkillRender3->ChangeAnimation("Shard6Effect", true, 0);
	}
	else
	{
		SkillRender3->ChangeAnimation("ShardEffect", true, 0);
	}


	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
}


void SkillWonder::CreateWonder()
{
	std::shared_ptr<SkillWonderActor> _WonderActor = GetLevel()->CreateActor<SkillWonderActor>(ContentsObjectType::FrontSkill);
	AllWonderActor.push_back(_WonderActor);
}

void SkillWonder::Release()
{
	SkillFunction::Release();
}


void SkillWonder::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;
}

void SkillWonder::WonderPosCal()
{
	int j = 0;
	for (size_t i = WonderCount; i < AllWonderActor.size(); i++)
	{
		j = WonderCount % 5;
		if ((i % 5) >= 3)
		{
			j = 4 - (i % 5);
		}

		AllWonderActor[i]->Transform.SetWorldPosition({ CurPlayerPos.X + (-100 + (i % 5) * 50.0f),
			CurPlayerPos.Y + (100 + (j * 15.0f)) });
		AllWonderActor[i]->Transform.SetLocalRotation({ 0.0f, 0.0f,  (30.0f) - ((i % 5) * 15.0f) });
		AllWonderActor[i]->On();
		WonderCount++;
	}
}

void SkillWonder::EndSkill()
{
	SkillFunction::EndSkill();
	Off();
	SkillRender3->Off();
}

void SkillWonder::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}