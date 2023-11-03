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
	
		//SkillRender2->CreateAnimation("Divide2", "Divide_2", 0.05f, -1, -1, false);
		//SkillRender1->CreateAnimation("Divide2Hit", "Divide2_Hit", 0.05f);
		//SkillRender2->SetFrameEvent("Divide2", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		//SkillRender2->SetEndEvent("Divide2", [&](GameEngineRenderer* _Renderer)
		//	{
		//		SkillRender2->Off();
		//		EndSkill();
		//	}
		//);

		//SkillRender3->CreateAnimation("Divide3", "Divide_3", 0.05f, -1, -1, false);
		//SkillRender1->CreateAnimation("Divide3Hit", "Divide3_Hit", 0.05f);
		//SkillRender3->SetFrameEvent("Divide3", 1, std::bind(&SkillDivide::RenderEvent, this, std::placeholders::_1));
		//SkillRender3->SetEndEvent("Divide3", [&](GameEngineRenderer* _Renderer)
		//	{
		//		SkillRender3->Off();
		//		EndSkill();
		//	}
		//);
	}

	SkillCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	SkillCollision->SetCollisionType(ColType::AABBBOX2D);
	SkillCollision->Transform.SetLocalScale({ 485.0f, 335.0f });


	{
		/*Divide1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Divide1->AutoSpriteSizeOn();
		Divide1->CreateAnimation("Divide1", "Divide_1", 0.05f, -1, -1, false);
		Divide1->ChangeAnimation("Divide1");
		Divide1->Off();*/

		//Divide2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		//Divide2->AutoSpriteSizeOn();
		//Divide2->CreateAnimation("Divide2", "Divide_2", 0.05f, -1, -1, false);
		//Divide2->ChangeAnimation("Divide2");
		//Divide2->Off();

		//Divide3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		//Divide3->AutoSpriteSizeOn();
		//Divide3->CreateAnimation("Divide3", "Divide_3", 0.05f, -1, -1, false);
		//Divide3->ChangeAnimation("Divide3");
		//Divide3->Off();

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

	//GameEngineRandom NewRandom;
	//int AttackValue = NewRandom.RandomInt(1, 3);
	//switch (AttackValue)
	//{
	//case(1):
	//	{
	//		ActorDir Dir = Player::GetMainPlayer()->GetDir();
	//		switch (Dir)
	//		{
	//		case ActorDir::Left:
	//			SkillRender1->Transform.SetWorldPosition({ PlayerPos.X - 207.5f, PlayerPos.Y - 25.0f});
	//			SkillRender1->RightFlip();
	//			SkillRender1->On();
	//			//Creation1->Transform.SetWorldPosition({ PlayerPos.X - 207.5f, PlayerPos.Y - 25.0f, FrontSkillPosZ });
	//			//Creation1->RightFlip();
	//			//Creation1->On();
	//			break;
	//		case ActorDir::Right:
	//			SkillRender1->Transform.SetWorldPosition({ PlayerPos.X + 207.5f, PlayerPos.Y});
	//			SkillRender1->LeftFlip();
	//			SkillRender1->On();
	//			//Creation1->Transform.SetWorldPosition({ PlayerPos.X + 207.5f, PlayerPos.Y, FrontSkillPosZ });
	//			//Creation1->LeftFlip();
	//			//Creation1->On();
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//case(2):
	//	{
	//		ActorDir Dir = Player::GetMainPlayer()->GetDir();
	//		switch (Dir)
	//		{
	//		case ActorDir::Left:
	//			SkillRender2->Transform.SetWorldPosition({ PlayerPos.X - 207.5f, PlayerPos.Y });
	//			SkillRender2->RightFlip();
	//			SkillRender2->On();
	//			//Creation2->Transform.SetWorldPosition({ PlayerPos.X - 207.5f, PlayerPos.Y, FrontSkillPosZ });
	//			//Creation2->RightFlip();
	//			//Creation2->On();
	//			break;
	//		case ActorDir::Right:
	//			SkillRender2->Transform.SetWorldPosition({ PlayerPos.X + 207.5f, PlayerPos.Y });
	//			SkillRender2->LeftFlip();
	//			SkillRender2->On();
	//			//Creation2->Transform.SetWorldPosition({ PlayerPos.X + 207.5f, PlayerPos.Y, FrontSkillPosZ });
	//			//Creation2->LeftFlip();
	//			//Creation2->On();
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//case(3):
	//	{
	//		ActorDir Dir = Player::GetMainPlayer()->GetDir();
	//		switch (Dir)
	//		{
	//		case ActorDir::Left:
	//			SkillRender3->Transform.SetWorldPosition({ PlayerPos.X - 207.5f, PlayerPos.Y });
	//			SkillRender3->RightFlip();
	//			SkillRender3->On();
	//			//Creation3->Transform.SetWorldPosition({ PlayerPos.X - 207.5f, PlayerPos.Y, FrontSkillPosZ });
	//			//Creation3->RightFlip();
	//			//Creation3->On();
	//			break;
	//		case ActorDir::Right:
	//			SkillRender3->Transform.SetWorldPosition({ PlayerPos.X + 207.5f, PlayerPos.Y });
	//			SkillRender3->LeftFlip();
	//			SkillRender3->On();
	//			//Creation3->Transform.SetWorldPosition({ PlayerPos.X + 207.5f, PlayerPos.Y, FrontSkillPosZ });
	//			//Creation3->LeftFlip();
	//			//Creation3->On();
	//			break;
	//		default:
	//			break;
	//		}
	//}

	SkillRender1->On();

	ActorDir Dir = Player::GetMainPlayer()->GetDir();
	if (Dir == ActorDir::Right)
	{
		SkillRender1->Transform.SetWorldPosition({ 207.5f, 0.0f});
		SkillRender1->LeftFlip();
		SkillCollision->Transform.SetWorldPosition({ 207.5f, 0.0f });
		AttackCol->Transform.SetWorldPosition({ +207.5f, 0.0f });
	}
	else if (Dir == ActorDir::Left)
	{
		SkillRender1->Transform.SetWorldPosition({ - 207.5f, -25.0f });
		SkillRender1->RightFlip();
		SkillCollision->Transform.SetWorldPosition({ -207.5f, -25.0f });
		AttackCol->Transform.SetWorldPosition({ -207.5f, -25.0f });
	}

	/*switch (Dir)
	{
	case ActorDir::Left:
		Divide1->Transform.SetWorldPosition({- 207.5f, - 25.0f });
		Divide1->RightFlip();
		Divide1->On();
		AttackCol->Transform.SetWorldPosition({ - 207.5f, - 25.0f });
		AttackCol->On();
		AttackEvent();
		break;
	case ActorDir::Right:
		Divide1->Transform.SetWorldPosition({  + 207.5f, 0.0f });
		Divide1->LeftFlip();
		Divide1->On();
		AttackCol->Transform.SetWorldPosition({ + 207.5f, 0.0f });
		AttackCol->On();
		AttackEvent();
		break;
	default:
		break;
	}

	Divide1->ChangeAnimation("DIvide1");*/
	SkillRender1->ChangeAnimation("Divide1", true, 0);
	DivideHitCount = 7;

	AttackEvent();
}

void SkillDivide::EndSkill()
{
	SkillFunction::EndSkill();
	Off();
	SkillRender1->Off();

	//SkillRender2->Off();
	//SkillRender3->Off();
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
	/*if (true == Divide1->IsCurAnimationEnd())
	{
		Divide1->Off();
		AttackCol->Off();
	}*/
	
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

void SkillDivide::CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
{
	for (int i = 0; i < _CollisionGroup.size(); i++)
	{
		std::shared_ptr<GameEngineCollision> _Other = _CollisionGroup[i];
		SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Divide1_Hit", DivideHitCount);
	}
}


void SkillDivide::AttackEvent()
{
	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, DivideHitCount, 480, 220);
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