#include "PreCompile.h"
#include "SkillRestore.h"
#include "SkillManager.h"

SkillRestore::SkillRestore()
{

}

SkillRestore::~SkillRestore()
{

}

void SkillRestore::Start()
{
	SkillFunction::Start();
	{
		SkillRender2->CreateAnimation("Restore_CharacterTop", "Restore_CharacterTop", 0.03f);
		SkillRender2->SetFrameEvent("Restore_CharacterTop", 0, std::bind(&SkillRestore::RenderEvent, this, std::placeholders::_1));

		SkillRender2->CreateAnimation("Restore_Start", "Restore_Start", 0.03f);
		SkillRender2->CreateAnimation("Restore6_Loop", "Restore6_Loop", 0.1f);

		SkillRender2->CreateAnimation("Restore_Hit", "Restore_Hit", 0.1f);

		SkillRender2->SetEndEvent("Restore_CharacterTop", [&](GameEngineRenderer* _Renderer)
			{
				if (Player::GetMainPlayer()->GetDir() == ActorDir::Right)
				{
					SkillRender2->Transform.SetLocalPosition({ -40.0f, 50.0f });
					SkillRender2->ChangeAnimation("Restore_Start");
				}
				else if (Player::GetMainPlayer()->GetDir() == ActorDir::Left)
				{
					SkillRender2->Transform.SetLocalPosition({ 40.0f, 50.0f });
					SkillRender2->ChangeAnimation("Restore_Start");
				}
			}
		);

		SkillRender2->SetEndEvent("Restore_Start", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender2->Transform.SetLocalPosition({ 0.0f, 0.0f });
				SkillRender2->ChangeAnimation("Restore6_Loop");
				AttackCol->On();
				SkillCollision->On();
			}
		);

		SkillCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		SkillCollision->SetCollisionType(ColType::AABBBOX2D);
		SkillCollision->Transform.SetLocalScale({ 800.0f, 600.0f });
		SkillCollision->Transform.SetLocalPosition({ 50.0f, 0.0f });

		{
			AttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
			AttackCol->SetCollisionType(ColType::AABBBOX2D);
			AttackCol->Transform.SetLocalScale({ 800.0f, 600.0f });
			AttackCol->Transform.SetLocalPosition({ 50.0f, 0.0f });
		}
	}
}


void SkillRestore::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;

	SkillRender2->On();

	SkillRender2->ChangeAnimation("Restore_CharacterTop", true, 0);

	AttackEvent();

	SkillValue::GetValue()->SetOrderLimitCount(8);
	RestoreTime = 30.0f;

	GameEngineSound::SoundPlay("Restore.mp3");
}

void SkillRestore::EndSkill()
{
	SkillFunction::EndSkill();
	SkillRender2->Off();
	SkillValue::GetValue()->SetOrderLimitCount(6);
	RestoreTime = 30.0f;

	if (SkillValue::GetValue()->GetCurOrderCount() >= 7)
	{
		SkillValue::GetValue()->SetOrderCount(6);
	}

	AttackCol->Off();
	SkillCollision->Off();
}

void SkillRestore::Update(float _Delta)
{
	SkillFunction::Update(_Delta);
	ActorDir Dir = Player::GetMainPlayer()->GetDir();
	if (Dir == ActorDir::Right)
	{
		SkillRender2->LeftFlip();
		Transform.SetLocalPosition({ PlayerPos.X - 50.0f, PlayerPos.Y + 35.0f });
	}
	else if (Dir == ActorDir::Left)
	{
		SkillRender2->RightFlip();
		Transform.SetLocalPosition({ PlayerPos.X + 50.0f, PlayerPos.Y + 35.0f });
	}

	RestoreTime -= _Delta;
	if (RestoreTime <= 0)
	{
		EndSkill();
	}

	// 시간에 따라 데미지
	CurTime += _Delta;
	if (CurTime >= LimitTime)
	{
		SkillCollision->Collision(ContentsCollisionType::Monster, std::bind(&SkillRestore::CollisionEvent, this, std::placeholders::_1));
		AttackEvent();
		CurTime = 0.0f;
	}
}

void SkillRestore::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;

	if (Player::GetMainPlayer()->GetDir() == ActorDir::Left)
	{
		SkillRender2->Transform.SetLocalPosition({ -40.0f, 35.0f });
	}
	else if (Player::GetMainPlayer()->GetDir() == ActorDir::Right)
	{
		SkillRender2->Transform.SetLocalPosition({ 40.0f, 35.0f });
	}
}

void SkillRestore::CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	for (int i = 0; i < _CollisionGroup.size(); i++)
	{
		GameEngineCollision* _Other = _CollisionGroup[i];
		SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Restore_Hit", RestoreHitCount);
	}
}

void SkillRestore::AttackEvent()
{
	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, RestoreHitCount, 1980, 100);
		};
	HitEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, RestoreHitCount, 1900, 100);
		};
	AttackCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
	AttackCol->CollisionEvent(ContentsCollisionType::Craving, HitEvent);
}

void SkillRestore::Release()
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