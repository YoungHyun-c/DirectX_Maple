#include "PreCompile.h"
#include "SkillBInd.h"
#include "Player.h"
#include "SkillManager.h"

#include "JinHillaBoss.h"

SkillBInd::SkillBInd()
{

}

SkillBInd::~SkillBInd()
{

}


void SkillBInd::Start()
{
	SkillFunction::Start();
	{
		SkillRender1->CreateAnimation("Scoll_Effect", "Scoll_Effect", 0.1f);

		SkillRender1->SetFrameEvent("Scoll_Effect", 1, std::bind(&SkillBInd::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Scoll_Effect", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);

	}

	SkillCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	SkillCollision->SetCollisionType(ColType::AABBBOX2D);
	SkillCollision->Transform.SetLocalScale({ 600.0f, 400.0f });


	{
		AttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		AttackCol->SetCollisionType(ColType::AABBBOX2D);
		AttackCol->Transform.SetLocalScale({ 600.0f, 400.0f });
	}
	ScollHitCount = 12;
}

void SkillBInd::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;
	On();

	SkillRender1->Transform.SetWorldPosition({ 0.0f, -200.0f });
	SkillCollision->Transform.SetWorldPosition({ 0.0f, -200.0f });
	AttackCol->Transform.SetWorldPosition({ 0.0f, -200.0f });
	SkillRender1->On();


	SkillRender1->ChangeAnimation("Scoll_Effect", true, 0);

	AttackEvent();
}

void SkillBInd::EndSkill()
{
	SkillFunction::EndSkill();
	Off();
	SkillRender1->Off();
}

void SkillBInd::Update(float _Delta)
{
	SkillFunction::Update(_Delta);
	SkillRender1->Transform.SetWorldPosition({ PlayerPos.X, PlayerPos.Y + 250.0f });
	SkillCollision->Transform.SetWorldPosition({ PlayerPos.X, PlayerPos.Y });
	AttackCol->Transform.SetWorldPosition({ PlayerPos.X, PlayerPos.Y });

	if (true == UseFirst)
	{
		SkillCollision->Collision(ContentsCollisionType::Monster, std::bind(&SkillBInd::CollisionEvent, this, std::placeholders::_1));
	}

	AttackEvent();
}

void SkillBInd::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;
}


void SkillBInd::CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	for (int i = 0; i < _CollisionGroup.size(); i++)
	{
		GameEngineCollision* _Other = _CollisionGroup[i];
		//SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Scoll_Mob", 1);
		if (_Other->GetName() == "Boss")
		{
			JinHillaBoss::GetMainBoss()->BossBind();
		}
	}
}

void SkillBInd::AttackEvent()
{
	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, ScollHitCount, 1000, 100);
		};
	AttackCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
	AttackCol->CollisionEvent(ContentsCollisionType::Craving, HitEvent);
}

void SkillBInd::Release()
{
	if (nullptr != SkillCollision)
	{
		SkillCollision = nullptr;
	}

	if (nullptr != AttackCol)
	{
		AttackCol = nullptr;
	}

	if (nullptr != NewDR)
	{
		NewDR = nullptr;
	}
}

void SkillBInd::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}
