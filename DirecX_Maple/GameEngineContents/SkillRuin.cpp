#include "PreCompile.h"
#include "SkillRuin.h"
#include "SkillManager.h"

SkillRuin::SkillRuin()
{

}

SkillRuin::~SkillRuin()
{

}

void SkillRuin::Start()
{
	SkillFunction::Start();
	{
		SkillRender2->CreateAnimation("Ruin", "Ruin_1", 0.142f);
		SkillRender2->CreateAnimation("RuinHit", "Ruin1_Hit", 0.023f);

		SkillRender2->SetFrameEvent("Ruin", 1, std::bind(&SkillRuin::RenderEvent, this, std::placeholders::_1));
		SkillRender2->SetEndEvent("Ruin", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender2->Off();
				EndSkill();
			}
		);

		SkillRender2->SetFrameEvent("Ruin", 8, [&](GameEngineRenderer* _Renderer)
			{
				SkillValue::GetValue()->SetRuinSkillDam(550);
				SkillCollision->On();
				AttackCol->On();
				LimitTime = 0.568f;
			}
		);

		SkillRender2->SetFrameEvent("Ruin", 32, [&](GameEngineRenderer* _Renderer)
			{
				SkillValue::GetValue()->SetRuinSkillDam(990);
				RuinHitCount = 9;
				LimitTime = 0.142f;
			}
		);

		SkillRender2->SetFrameEvent("Ruin", 44, [&](GameEngineRenderer* _Renderer)
			{
				SkillCollision->Off();
				AttackCol->Off();
			}
		);
	}


	SkillCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	SkillCollision->SetCollisionType(ColType::AABBBOX2D);
	SkillCollision->Transform.SetLocalScale({ 1200.0f, 1200.0f });
	SkillCollision->Off();


	{
		AttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		AttackCol->SetCollisionType(ColType::AABBBOX2D);
		AttackCol->Transform.SetLocalScale({ 1200.0f, 1200.0f });
		AttackCol->Off();
	}
}

void SkillRuin::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;

	SkillRender2->On();

	CurTime = 0.0f;
	RuinHitCount = 6;
	SkillRender2->ChangeAnimation("Ruin", true, 0);

	AttackEvent();
	GameEngineSound::SoundPlay("Ruin.mp3");
}

void SkillRuin::EndSkill()
{
	SkillFunction::EndSkill();
	SkillRender2->Off();
}

void SkillRuin::Update(float _Delta)
{
	Transform.SetWorldPosition({ PlayerPos.X, PlayerPos.Y + 275.0f });

	// �ð��� ���� ������
	CurTime += _Delta;
	if (CurTime >= LimitTime)
	{
		SkillCollision->Collision(ContentsCollisionType::Monster, std::bind(&SkillRuin::CollisionEvent, this, std::placeholders::_1));
		AttackEvent();
		CurTime = 0.0f;
	}
}

void SkillRuin::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;
}

void SkillRuin::CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	for (int i = 0; i < _CollisionGroup.size(); i++)
	{
		GameEngineCollision* _Other = _CollisionGroup[i];
		SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Ruin1_Hit", RuinHitCount);
	}
}

void SkillRuin::AttackEvent()
{
	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, RuinHitCount, SkillValue::GetValue()->GetRuinSkillDam(), SkillValue::GetValue()->GetRuinFinalDam());
		};
	HitEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, RuinHitCount, SkillValue::GetValue()->GetRuinSkillDam(), SkillValue::GetValue()->GetRuinFinalDam());
		};
	AttackCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
	AttackCol->CollisionEvent(ContentsCollisionType::Craving, HitEvent);
}

void SkillRuin::Release()
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


void SkillRuin::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}