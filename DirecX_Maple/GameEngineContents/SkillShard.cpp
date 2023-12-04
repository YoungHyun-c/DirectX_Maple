#include "PreCompile.h"
#include "SkillShard.h"

#include "BaseSummonActor.h"
#include "SkillWonderActor.h"

#include "Player.h"

SkillShard::SkillShard()
{

}

SkillShard::~SkillShard()
{

}

void SkillShard::Start()
{
	SkillFunction::Start();
	{
		// "Maestro"
		{
			SkillRender1->CreateAnimation("Shard6Effect", "Shard6_Effect", 0.07f);

			SkillRender1->SetFrameEvent("Shard6Effect", 1, std::bind(&SkillShard::RenderEvent, this, std::placeholders::_1));
			SkillRender1->Transform.SetLocalPosition({ 0.0f, 75.0f });
			SkillRender1->SetEndEvent("Shard6Effect", [&](GameEngineRenderer* _Renderer)
				{
					SkillRender1->Off();
					EndSkill();
				});

			AllShardActor.reserve(5);
			for (int i = 0; i < 5; i++)
				SkillRender1->SetFrameEvent("Shard6Effect", i, [&](GameEngineSpriteRenderer* _Renderer)
					{
						CreateShard();
					});

			SkillRender1->SetFrameEvent("Shard6Effect", 5, [&](GameEngineSpriteRenderer* _Renderer)
				{
					ShardPosCal();
				});

		}

		{
			SkillRender1->CreateAnimation("ShardEffect", "Shard_Effect", 0.07f);

			SkillRender1->SetFrameEvent("ShardEffect", 1, std::bind(&SkillShard::RenderEvent, this, std::placeholders::_1));
			SkillRender1->Transform.SetLocalPosition({ 0.0f, 75.0f });
			SkillRender1->SetEndEvent("ShardEffect", [&](GameEngineRenderer* _Renderer)
				{
					SkillRender1->Off();
					EndSkill();
				}
			);
		}
		AllShardActor.reserve(5);
		for (int i = 0; i < 5; i++)
			SkillRender1->SetFrameEvent("ShardEffect", i, [&](GameEngineSpriteRenderer* _Renderer)
				{
					CreateShard();
				});

		SkillRender1->SetFrameEvent("ShardEffect", 5, [&](GameEngineSpriteRenderer* _Renderer)
			{
				ShardPosCal();
			});

	}
}

void SkillShard::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;
	On();

	ActorDir Dir = Player::GetMainPlayer()->GetDir();
	if (Dir == ActorDir::Right)
	{
		SkillRender1->LeftFlip();
	}
	if (Dir == ActorDir::Left)
	{
		SkillRender1->RightFlip();
	}

	SkillRender1->On();
	SkillRender1->ChangeAnimation("ShardEffect", true, 0);


	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
}
void SkillShard::EndSkill()
{
	SkillFunction::EndSkill();
	Off();
	SkillRender1->Off();
}
void SkillShard::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}
void SkillShard::Update(float _Delta)
{
	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	Transform.SetWorldPosition(CurPlayerPos);
}

void SkillShard::ShardPosCal()
{
	int j = 0;
	for (size_t i = ShardCount; i < AllShardActor.size(); i++)
	{
		j = ShardCount % 5;
		if ((i % 5) >= 3)
		{
			j = 4 - (i % 5);
		}

		AllShardActor[i]->Transform.SetWorldPosition({ CurPlayerPos.X + (-100 + (i % 5) * 50.0f),
			CurPlayerPos.Y + (100 + (j * 15.0f)) });
		AllShardActor[i]->Transform.SetLocalRotation({ 0.0f, 0.0f,  (30.0f) - ((i % 5) * 15.0f) });
		AllShardActor[i]->On();
		ShardCount++;
	}
}

void SkillShard::CreateShard()
{
	std::shared_ptr<SkillWonderActor> _ShardActor = GetLevel()->CreateActor<SkillWonderActor>(ContentsObjectType::FrontSkill);
	AllShardActor.push_back(_ShardActor);
}

void SkillShard::Release()
{
	SkillFunction::Release();
}
void SkillShard::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;
}