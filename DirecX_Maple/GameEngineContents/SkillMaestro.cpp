#include "PreCompile.h"
#include "SkillMaestro.h"
#include "SkillManager.h"

#include "Player.h"

#include "JinHillaBoss.h"

SkillMaestro::SkillMaestro()
{

}

SkillMaestro::~SkillMaestro()
{

}

void SkillMaestro::Start()
{
	SkillFunction::Start();
	{
		SkillRender1->CreateAnimation("Maestro", "Job6_Start", 0.062f);
		SkillRender1->CreateAnimation("MaestroHit", "Job6_Hit", 0.023f);

		SkillRender1->SetFrameEvent("Maestro", 1, std::bind(&SkillMaestro::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Maestro", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);
		//SkillRender1->SetStartEvent("Maestro", [&](GameEngineRenderer* _Renderer)
		//	{
		//		MaestroHitCount = 10;
		//		LimitTime = 0.372f;
		//	}
		//);

		SkillRender1->SetFrameEvent("Maestro", 36, [&](GameEngineRenderer* _Renderer)
			{
				LimitTime = 6.0f;
			}
		);

		SkillRender1->SetFrameEvent("Maestro", 99, [&](GameEngineRenderer* _Renderer)
			{
				MaestroHitCount = 14;
				LimitTime = 0.124f;
				GameEngineSound::SoundPlay("MaestorEnd.mp3");
			}
		);


	}
	
	SkillCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	SkillCollision->SetCollisionType(ColType::AABBBOX2D);
	SkillCollision->Transform.SetLocalScale({ 1600.0f, 1600.0f });


	{
		AttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		AttackCol->SetCollisionType(ColType::AABBBOX2D);
		AttackCol->Transform.SetLocalScale({ 1600.0f, 1600.0f });
	}
}

void SkillMaestro::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;

	SkillRender1->ChangeAnimation("Maestro");
	SkillRender1->On();
	AttackCol->On();
	SkillCollision->On();

	MaestroHitCount = 10;
	LimitTime = 0.372f;

	AttackEvent();
	GameEngineSound::SoundPlay("MaeStroStart.mp3");
}

void SkillMaestro::EndSkill()
{
	SkillFunction::EndSkill();
	SkillRender1->Off();
	AttackCol->Off();
	SkillCollision->Off();
}

void SkillMaestro::Update(float _Delta)
{
	Transform.SetWorldPosition(GetLevel()->GetMainCamera()->Transform.GetLocalPosition());

	// 시간에 따라 데미지
	CurTime += _Delta;
	if (CurTime >= LimitTime)
	{
		SkillCollision->Collision(ContentsCollisionType::Monster, std::bind(&SkillMaestro::CollisionEvent, this, std::placeholders::_1));
		AttackEvent();
		CurTime = 0.0f;
	}
}

void SkillMaestro::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;
}

void SkillMaestro::CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	for (int i = 0; i < _CollisionGroup.size(); i++)
	{
		GameEngineCollision* _Other = _CollisionGroup[i];
		SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Job6_Hit", MaestroHitCount);

		if (_Other->GetName() == "Boss")
		{
			JinHillaBoss::GetMainBoss()->BossFormerBind();
		}
	}
}
void SkillMaestro::AttackEvent()
{
	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, MaestroHitCount, SkillValue::GetValue()->GetMaestroSkillDam(), SkillValue::GetValue()->GetMaestroFinalDam());
		};
	HitEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, MaestroHitCount, SkillValue::GetValue()->GetMaestroSkillDam(), SkillValue::GetValue()->GetMaestroFinalDam());
		};
	AttackCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
	AttackCol->CollisionEvent(ContentsCollisionType::Craving, HitEvent);
}

void SkillMaestro::Release()
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


void SkillMaestro::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}