#include "PreCompile.h"
#include "SkillDivide.h"
#include "Player.h"
#include "SkillManager.h"
#include "MonsterFunction.h"

SkillDivide::SkillDivide()
{

}

SkillDivide::~SkillDivide()
{

}


void SkillDivide::Start()
{
	SkillFunction::Start();
	{



		SkillRender1->CreateAnimation("Divide1", "Divide_1", 0.05f);
		SkillRender1->CreateAnimation("Divide1Hit", "Divide1_Hit", 0.05f);

		SkillRender1->SetFrameEvent("Divide1", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Divide1", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);
	
		SkillRender1->CreateAnimation("Divide2", "Divide_2", 0.05f, -1, -1, false);
		SkillRender1->CreateAnimation("Divide2Hit", "Divide2_Hit", 0.05f);

		SkillRender1->SetFrameEvent("Divide2", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Divide2", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);

		SkillRender1->CreateAnimation("Divide3", "Divide_3", 0.05f, -1, -1, false);
		SkillRender1->CreateAnimation("Divide3Hit", "Divide3_Hit", 0.05f);

		SkillRender1->SetFrameEvent("Divide3", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Divide3", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);

		// 6차
		SkillRender1->CreateAnimation("Divide4", "Divide_4", 0.05f, -1, -1, false);
		SkillRender1->CreateAnimation("Divide4Hit", "Divide4_Hit", 0.05f);

		SkillRender1->SetFrameEvent("Divide4", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Divide4", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);
		SkillRender1->CreateAnimation("Divide5", "Divide_5", 0.05f, -1, -1, false);
		SkillRender1->CreateAnimation("Divide5Hit", "Divide5_Hit", 0.05f);

		SkillRender1->SetFrameEvent("Divide5", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Divide5", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);
		SkillRender1->CreateAnimation("Divide6", "Divide_6", 0.05f, -1, -1, false);
		SkillRender1->CreateAnimation("Divide6Hit", "Divide6_Hit", 0.05f);

		SkillRender1->SetFrameEvent("Divide6", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Divide6", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);
		SkillRender1->CreateAnimation("Divide7", "Divide_7", 0.05f, -1, -1, false);
		SkillRender1->CreateAnimation("Divide7Hit", "Divide7_Hit", 0.05f);

		SkillRender1->SetFrameEvent("Divide7", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetEndEvent("Divide7", [&](GameEngineRenderer* _Renderer)
			{
				SkillRender1->Off();
				EndSkill();
			}
		);

	}

	SkillCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	SkillCollision->SetCollisionType(ColType::AABBBOX2D);
	SkillCollision->Transform.SetLocalScale({ 485.0f, 335.0f });


	{
		AttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		AttackCol->SetCollisionType(ColType::AABBBOX2D);
		AttackCol->Transform.SetLocalScale({ 485.0f, 335.0f });
		//AttackCol->Off();
	}
}


void SkillDivide::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;
	On();

	SkillName = "Divide";
	SkillHitName = "Divide";
	if (PlayerValue::GetValue()->GetClass() == "HighAtere")
	{
		DivideHitCount = 6;
		SkillNum = RandomSKillNum.RandomInt(1, 3);
		switch (SkillNum)
		{
		case 1:
			SkillName += std::to_string(1);
			SkillHitName += std::to_string(1) + "_Hit";
			break;
		case 2:
			SkillName += std::to_string(2);
			SkillHitName += std::to_string(2) + "_Hit";
			break;
		case 3:
			SkillName += std::to_string(3);
			SkillHitName += std::to_string(3) + "_Hit";
			break;
		}
	}

	if (PlayerValue::GetValue()->GetClass() == "Maestro")
	{
		DivideHitCount = 7;
		if (PlayerValue::GetValue()->GetDivide6Use() == false)
		{
			PlayerValue::GetValue()->SetDivideUse(true);
			SkillNum = 7;
			SkillName += std::to_string(7);
			SkillHitName += std::to_string(7) + "_Hit";
		}
		else
		{
			SkillNum = RandomSKillNum.RandomInt(4, 6);
			switch (SkillNum)
			{
			case 4:
				SkillName += std::to_string(4);
				SkillHitName += std::to_string(4) + "_Hit";
				break;
			case 5:
				SkillName += std::to_string(5);
				SkillHitName += std::to_string(5) + "_Hit";
				break;
			case 6:
				SkillName += std::to_string(6);
				SkillHitName += std::to_string(6) + "_Hit";
				break;
			}
		}
	}

	SkillRender1->On();

	ActorDir Dir = Player::GetMainPlayer()->GetDir();
	if (Dir == ActorDir::Right)
	{
		SkillRender1->Transform.SetWorldPosition({ 207.5f, -25.0f});
		SkillRender1->LeftFlip();
		SkillCollision->Transform.SetWorldPosition({ 207.5f, -25.0f });
		AttackCol->Transform.SetWorldPosition({ +207.5f, -25.0f });
	}
	else if (Dir == ActorDir::Left)
	{
		SkillRender1->Transform.SetWorldPosition({ - 207.5f, -25.0f });
		SkillRender1->RightFlip();
		SkillCollision->Transform.SetWorldPosition({ -207.5f, -25.0f });
		AttackCol->Transform.SetWorldPosition({ -207.5f, -25.0f });
	}

	SkillRender1->ChangeAnimation(SkillName, true, 0);

	AttackEvent();
}

void SkillDivide::EndSkill()
{
	SkillFunction::EndSkill();
	Off();
	SkillRender1->Off();
}

void SkillDivide::Update(float _Delta)
{
	//SkillFunction::Update(_Delta);

	Transform.SetLocalPosition(PlayerPos);
	if (true == UseFirst)
	{
		SkillCollision->Collision(ContentsCollisionType::Monster, std::bind(&SkillDivide::CollisionEvent, this, std::placeholders::_1));
		//AttackCol->Collision(ContentsCollisionType::Monster, std::bind(&SkillDivide::AttackEvent, this));
	}
	
	// 시간에 따라 데미지
	//CurTime += _Delta;
	//if (CurTime >= LimitTime)
	//{
	//	AttackEvent();
	//	CurTime = 0.0f;
	//}

	AttackEvent();
}

void SkillDivide::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;
}

void SkillDivide::CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	for (int i = 0; i < _CollisionGroup.size(); i++)
	{
		GameEngineCollision* _Other = _CollisionGroup[i];
		SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), SkillHitName, DivideHitCount);
	}
}


void SkillDivide::AttackEvent()
{
	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, DivideHitCount, SkillValue::GetValue()->GetDivideSkillDam(), SkillValue::GetValue()->GetDivideFinalDam());
		};
	HitEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			int a = 0;
		};
	AttackCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
	AttackCol->CollisionEvent(ContentsCollisionType::Craving, HitEvent);
}

void SkillDivide::Release()
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


void SkillDivide::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}