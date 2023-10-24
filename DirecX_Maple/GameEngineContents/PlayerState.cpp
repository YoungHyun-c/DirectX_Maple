#include "PreCompile.h"
#include "Player.h"
#include "BackGroundMap.h"
#include "Monster.h"

//#include "AdeleSkill.h"
#include "SkillManager.h"
#include "SkillDivide.h"


#define JumpDistance 200.0f
#define JumpHeight 300.0f
#define DoubleJumpDistance 450.0f
#define NoKeyDistance 225.0f
#define DoubleJumpHeight 100.0f
#define DoubleJumpUP 500.0f


void Player::StandStart()
{
	ChangeAnimationState("Stand");
}
void Player::StandUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_LEFT, this)
		|| true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if (GameEngineInput::IsDown('X', this) || GameEngineInput::IsPress('X', this))
	{
		ChangeState(PlayerState::Jump);
	}

	if (GameEngineInput::IsDown(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack);
	}

	if (GameEngineInput::IsPress(VK_DOWN, this))
	{
		ChangeState(PlayerState::Prone);
	}
}

void Player::StandEnd()
{
	
}

void Player::WalkStart()
{
	ChangeAnimationState("Walk");
}
void Player::WalkUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = float4::RIGHT;
		break;
	case ActorDir::Left:
		MoveDir = float4::LEFT;
		break;
	default:
		break;
	}

	if (GameEngineInput::IsPress(VK_LEFT, this))
	{
		MovePos += MoveDir * WalkSpeed * _Delta;
	}
	if (GameEngineInput::IsPress(VK_RIGHT, this) && Dir == ActorDir::Right)
	{
		MovePos += MoveDir * WalkSpeed * _Delta;
	}

	//CheckColor = CheckGroundColor(MovePos);
	//if (DefaultGroundColor != CheckColor)
	//{

	//}

	Transform.AddLocalPosition(MovePos);

	if (GameEngineInput::IsDown('X', this) || GameEngineInput::IsPress('X', this))
	{
		ChangeState(PlayerState::Jump);
	}

	if (GameEngineInput::IsFree(VK_LEFT, this) && GameEngineInput::IsFree(VK_RIGHT, this))
	{
		ChangeState(PlayerState::Stand);
		return;
	}

	if (GameEngineInput::IsDown(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack);
	}
}

void Player::WalkEnd()
{

}

void Player::AlertStart()
{
	ChangeAnimationState("Alert");
}
void Player::AlertUpdate(float _Delta)
{

}
void Player::ProneStart()
{
	ChangeAnimationState("Prone");
}
void Player::ProneUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_LEFT, this)
		|| true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		ChangeState(PlayerState::Walk);
		return;
	}
}
void Player::AttackStart()
{
	if (IsAttack == true)
	{
		return;
	}
	IsAttack = true;
	
	ChangeAnimationState("Attack");
	SkillManager::PlayerSkillManager->UseSkill("Divide1");

	//AttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	//AttackCol->SetCollisionType(ColType::AABBBOX2D);
	//if (Dir == ActorDir::Right)
	//{
	//	AttackCol->Transform.SetLocalPosition({ 207.5f, 0.0f });
	//	AttackCol->Transform.SetLocalScale({ 485.0f, 335.0f });
	//}
	//else if (Dir == ActorDir::Left)
	//{
	//	AttackCol->Transform.SetLocalPosition({ -207.5f, 0.0f });
	//	AttackCol->Transform.SetLocalScale({ 485.0f, 335.0f });
	//}
	////AttackCol->On();
	//// Ãæµ¹
	////std::vector<std::shared_ptr<GameEngineCollision>> HitMonsterVector;
	////std::vector<std::shared_ptr<GameEngineCollision>> HitObjectVector;
	////std::shared_ptr<GameEngineCollision> HitObject;
	//EventParameter HitEvent;

	//HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
	//	{
	//		//Monster::Monsters->GetMonsterHp(-1);
	//		std::shared_ptr<DamageRenderer> NewDR = GetLevel()->CreateActor<DamageRenderer>();
	//		NewDR->PushDamage(_Other, 6, 480, 220);
	//		//SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Divide1_Hit", 6, 500, 220);
	//		//SkillManager::PlayerSkillManager->HitPrint("Normal_Impale", 1, _Other->GetParentObject(), false);
	//		//NewDR->Transform.SetWorldPosition(Transform.GetWorldPosition() + float4{ 150.0f, 50.0f });
	//		//NewDR->Transform.SetWorldPosition({ GlobalValue::CurMonsterPos.X + 150.0f, GlobalValue::CurMonsterPos.Y + 50.0f });
	//	};
	//HitEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* _Other)
	//	{
	//		int a = 0;
	//	};
	//AttackCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
	//AttackCol->Collision(ContentsCollisionType::Monster, std::bind(&Player::CollisionEvent2, this, std::placeholders::_1));


	//RangeCheck->CollisionEvent(ContentsCollisionType::Monster, HitEvent);


	/*ChangeAnimationState("Attack");
	SkillManager::PlayerSkillManager->UseSkill("Divide1");*/
	//GameEngineRandom NewRandom;
	//int AttackValue = NewRandom.RandomInt(1, 3);
	//std::shared_ptr<AdeleSkill> Divide = GetLevel()->CreateActor<AdeleSkill>();
	//switch(AttackValue)
	//{
	//case(1):
	//	Divide->SetSkillActor("Divide1");
	//	break;
	//case(2):
	//	Divide->SetSkillActor("Divide2");
	//	break;
	//case(3):
	//	Divide->SetSkillActor("Divide3");
	//	break;
	//default:
	//	break;
	//}
}
void Player::AttackUpdate(float _Delta)
{
	//if (DoubleJump = false)
	//{
	//	{
	//		std::shared_ptr<AdeleSkill> BoltJumpActor = GetLevel()->CreateActor<AdeleSkill>();
	//		std::shared_ptr<AdeleSkill> DoubleJumpActor = GetLevel()->CreateActor<AdeleSkill>();
	//		if (GameEngineInput::IsPress(VK_UP))
	//		{
	//			BoltJumpActor->SetSkillActor("BoltJump");
	//			AddMoveVectorForce(float4(0, DoubleJumpUP));
	//		}
	//		else if (true == GameEngineInput::IsPress(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	//		{
	//			DoubleJumpActor->SetSkillActor("DoubleJump");
	//			AddMoveVectorForce(float4(-DoubleJumpDistance * 0.5, DoubleJumpHeight));
	//		}
	//		else if (true == GameEngineInput::IsPress(VK_RIGHT) && true == GameEngineInput::IsFree(VK_LEFT))
	//		{
	//			DoubleJumpActor->SetSkillActor("DoubleJump");
	//			AddMoveVectorForce(float4(DoubleJumpDistance * 0.5, DoubleJumpHeight));
	//		}
	//		else
	//		{
	//			switch (Dir)
	//			{
	//			case ActorDir::Right:
	//				if (true == GameEngineInput::IsFree(VK_RIGHT) && true == GameEngineInput::IsFree(VK_LEFT))
	//				{
	//					DoubleJumpActor->SetSkillActor("DoubleJump");
	//					AddMoveVectorForce(float4(NoKeyDistance, DoubleJumpHeight));
	//					break;
	//				}
	//				DoubleJumpActor->SetSkillActor("DoubleJump");
	//				AddMoveVectorForce(float4(DoubleJumpDistance * 0.5, DoubleJumpHeight));
	//				break;
	//			case ActorDir::Left:
	//				if (true == GameEngineInput::IsFree(VK_RIGHT) && true == GameEngineInput::IsFree(VK_LEFT))
	//				{
	//					DoubleJumpActor->SetSkillActor("DoubleJump");
	//					AddMoveVectorForce(float4(-NoKeyDistance, DoubleJumpHeight));
	//					break;
	//				}
	//				DoubleJumpActor->SetSkillActor("DoubleJump");
	//				AddMoveVectorForce(float4(-DoubleJumpDistance * 0.5, DoubleJumpHeight));
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//}


	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Walk);
		return;
	}
}

void Player::AttackEnd()
{
	IsAttack = false;
	//AttackCol->Off();
}

void Player::ProneAttackStart()
{

}
void Player::ProneAttackUpdate(float _Delta)
{

}
void Player::JumpStart()
{
	ChangeAnimationState("Jump");

	if (true == IsGround)
	{
		if (GameEngineInput::IsPress(VK_LEFT, this))
		{
			AddMoveVectorForce(float4(-JumpDistance, JumpHeight));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT, this))
		{
			AddMoveVectorForce(float4(JumpDistance, JumpHeight));
		}
		else
		{
			AddMoveVectorForce(float4(0, JumpHeight));
		}
		GroundJump = true;
	}
}
void Player::JumpUpdate(float _Delta)
{
	if (true == IsGround && 0 >= GetMoveVectorForce().Y)
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if (GameEngineInput::IsPress(VK_LEFT, this) || GameEngineInput::IsPress(VK_RIGHT, this))
	{
		float4 MoveDir = float4::ZERO;

		switch (Dir)
		{
		case ActorDir::Right:
			MoveDir = float4::RIGHT;
			break;
		case ActorDir::Left:
			MoveDir = float4::LEFT;
			break;
		default:
			break;
		}
		
		switch (GroundJump)
		{
		case true:
			Transform.AddLocalPosition(MoveDir * _Delta * JumpAirSpeed);
			break;
		case false:
			Transform.AddLocalPosition(MoveDir * _Delta * AirSpeed);
			break;
		}
	}

	if (GameEngineInput::IsDown(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack);
	}

	if (true == DoubleJump)
	{
		return;
	}

	if (GameEngineInput::IsDown('X', this))
	{
		std::shared_ptr<AdeleSkill> BoltJumpActor = GetLevel()->CreateActor<AdeleSkill>();
		std::shared_ptr<AdeleSkill> DoubleJumpActor = GetLevel()->CreateActor<AdeleSkill>();
		DoubleJump = true;
		if (GameEngineInput::IsPress(VK_UP, this))
		{
			BoltJumpActor->SetSkillActor("BoltJump");
			AddMoveVectorForce(float4(0, DoubleJumpUP));
		}
		else if (true == GameEngineInput::IsPress(VK_LEFT, this) && true == GameEngineInput::IsFree(VK_RIGHT, this))
		{
			DoubleJumpActor->SetSkillActor("DoubleJump");
			AddMoveVectorForce(float4(-DoubleJumpDistance * 0.5, DoubleJumpHeight));
		}
		else if (true == GameEngineInput::IsPress(VK_RIGHT, this) && true == GameEngineInput::IsFree(VK_LEFT, this))
		{
			DoubleJumpActor->SetSkillActor("DoubleJump");
			AddMoveVectorForce(float4(DoubleJumpDistance * 0.5, DoubleJumpHeight));
		}
		else
		{
			switch (Dir)
			{
			case ActorDir::Right:
				if (true == GameEngineInput::IsFree(VK_RIGHT, this) && true == GameEngineInput::IsFree(VK_LEFT, this))
				{
					DoubleJumpActor->SetSkillActor("DoubleJump");
					AddMoveVectorForce(float4(NoKeyDistance, DoubleJumpHeight));
					break;
				}
				else
				{
					DoubleJumpActor->SetSkillActor("DoubleJump");
					AddMoveVectorForce(float4(DoubleJumpDistance * 0.5, DoubleJumpHeight));
					break;
				}
			case ActorDir::Left:
				if (true == GameEngineInput::IsFree(VK_RIGHT, this) && true == GameEngineInput::IsFree(VK_LEFT, this))
				{
					DoubleJumpActor->SetSkillActor("DoubleJump");
					AddMoveVectorForce(float4(-NoKeyDistance, DoubleJumpHeight));
					break;
				}
				DoubleJumpActor->SetSkillActor("DoubleJump");
				AddMoveVectorForce(float4(-DoubleJumpDistance * 0.5, DoubleJumpHeight));
				break;
			default:
				break;
			}
		}

		if (GameEngineInput::IsDown(VK_SHIFT, this))
		{
			ChangeState(PlayerState::Attack);
		}
		//GravityReset();
	}
}

void Player::JumpEnd()
{
	GravityReset();
	MoveVectorForceReset();
	GroundJump = false;
	DoubleJump = false;
}

void Player::DoubleJumpStart()
{

}
void Player::DoubleJumpUpdate(float _Delta)
{

}
void Player::FlyStart()
{

}
void Player::FlyUpdate(float _Delta)
{

}
void Player::DeadStart()
{

}
void Player::DeadUpdate(float _Delta)
{

}
