#include "PreCompile.h"
#include "Player.h"
#include "BackGroundMap.h"
#include "SkillManager.h"
#include "SkillDivide.h"
#include "BasicFunction.h"

#define JumpDistance 50.0f
#define JumpHeight 500.0f

#define DoubleJumpDistance 250.0f

#define DoubleJumpHeight 100.0f
#define FlyingDoubleJumpUp 900.0f
#define DoubleJumpUP 500.0f
#define NoKeyDoubleJumpDistance 700.0f

#define RopeJumpHeight 200.0f

#define Alert_Time 5.0f

void Player::StandStart()
{
	MainSpriteRenderer->ChangeAnimation("Normal_Stand");
}
void Player::StandUpdate(float _Delta)
{
	if (State == PlayerState::Stand && 0.0f < AlertTime)
	{
		ChangeState(PlayerState::Alert);
		return;
	}

	if (GameEngineInput::IsPress(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (GameEngineInput::IsDown('3', this))
	{
		SkillManager::PlayerSkillManager->UseSkill("Ruin");
		ChangeState(PlayerState::Alert);
		return;
	}

	if (GameEngineInput::IsDown(VK_HOME, this))
	{
		ChangeState(PlayerState::SwingB);
		return;
	}

	if (PlayerValue::GetValue()->GetClass() == "Maestro")
	{
		if (GameEngineInput::IsDown('R', this))
		{
			ChangeState(PlayerState::Maestro);
			return;
		}
	}

	if (GameEngineInput::IsDown('Y', this))
	{
		ChangeState(PlayerState::SwingY);
		return;
	}

	if (GameEngineInput::IsDown('A', this) && PlayerValue::GetValue()->GetAtere() >= 100)
	{
		SkillManager::PlayerSkillManager->UseSkill("Order");
		AlertTime = Alert_Time;
		return;
	}

	if (true == GameEngineInput::IsPress(VK_LEFT, this)
		|| true == GameEngineInput::IsPress(VK_RIGHT, this))
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if (GameEngineInput::IsDown('X', this) || GameEngineInput::IsPress('X', this))
	{
		ChangeState(PlayerState::Jump);
		return;
	}


	if (GameEngineInput::IsPress(VK_DOWN, this))
	{
		if (false == IsRope)
		{
			ChangeState(PlayerState::Prone);
			return;
		}
		if (true == IsRope && (GameEngineInput::IsPress(VK_UP, this) || GameEngineInput::IsPress(VK_DOWN, this)))
		{
			ChangeState(PlayerState::Rope);
			return;
		}
	}
}

void Player::AlertStart()
{
	MainSpriteRenderer->ChangeAnimation("Normal_Alert");
}
void Player::AlertUpdate(float _Delta)
{
	AlertTime -= _Delta;
	if (0.0f >= AlertTime)
	{
		ChangeState(PlayerState::Stand);
	}
	StandUpdate(_Delta);
}

void Player::WalkStart()
{
	MainSpriteRenderer->ChangeAnimation("Normal_Walk");
}

void Player::WalkUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (GameEngineInput::IsDown('3', this))
	{
		SkillManager::PlayerSkillManager->UseSkill("Ruin");
		ChangeState(PlayerState::Alert);
		return;
	}

	if (GameEngineInput::IsDown(VK_HOME, this))
	{
		ChangeState(PlayerState::SwingB);
		return;
	}

	if (PlayerValue::GetValue()->GetClass() == "Maestro")
	{
		if (GameEngineInput::IsDown('R', this))
		{
			ChangeState(PlayerState::Maestro);
			return;
		}
	}

	if (GameEngineInput::IsDown('Y', this))
	{
		ChangeState(PlayerState::SwingY);
		return;
	}

	if (GameEngineInput::IsDown('A', this) && PlayerValue::GetValue()->GetAtere() >= 100)
	{
		SkillManager::PlayerSkillManager->UseSkill("Order");
		AlertTime = Alert_Time;
		return;
	}

	float MovePos = 0.0f;
	float MoveDir = 0.0f;

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = 1.0f;
		break;
	case ActorDir::Left:
		MoveDir = -1.0f;
		break;
	default:
		break;
	}

	if (GameEngineInput::IsPress(VK_LEFT, this))
	{
		MovePos += MoveDir * WalkSpeed;
	}
	if (GameEngineInput::IsPress(VK_RIGHT, this) && Dir == ActorDir::Right)
	{
		MovePos += MoveDir * WalkSpeed;
	}

	SetMoveVectorXForce(MovePos);

	if (GameEngineInput::IsDown('X', this) || GameEngineInput::IsPress('X', this))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (GameEngineInput::IsFree(VK_LEFT, this) && GameEngineInput::IsFree(VK_RIGHT, this))
	{
		ChangeToStand();
		return;
	}


	if (true == IsRope && (GameEngineInput::IsPress(VK_UP, this) || GameEngineInput::IsPress(VK_DOWN, this)))
	{
		ChangeState(PlayerState::Rope);
		return;
	}
}

void Player::JumpStart()
{
	MainSpriteRenderer->ChangeAnimation("Normal_Jump");

	if (true == IsGround)
	{
		if (ActorDir::Left == Dir && GameEngineInput::IsPress(VK_LEFT, this))
		{
			AddMoveVectorForce(float4(-JumpDistance, JumpHeight));
		}
		else if (ActorDir::Right == Dir && GameEngineInput::IsPress(VK_RIGHT, this))
		{
			AddMoveVectorForce(float4(JumpDistance, JumpHeight));
		}
		else
		{
			AddMoveVectorForce(float4(0, JumpHeight));
		}
		GroundJump = true;
	}
	else if (PlayerState::Rope == State)
	{
		if (GameEngineInput::IsPress(VK_LEFT, this))
		{
			AddMoveVectorForce(float4(-RopeJumpHeight, RopeJumpHeight));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT, this))
		{
			AddMoveVectorForce(float4(RopeJumpHeight, RopeJumpHeight));
		}
	}
}
void Player::JumpUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SHIFT, this) || GameEngineInput::IsPress(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (GameEngineInput::IsDown(VK_HOME, this))
	{
		ChangeState(PlayerState::SwingB);
		return;
	}

	if (PlayerValue::GetValue()->GetClass() == "Maestro")
	{
		if (GameEngineInput::IsDown('R', this))
		{
			ChangeState(PlayerState::Maestro);
			return;
		}
	}

	if (GameEngineInput::IsDown('A', this) && PlayerValue::GetValue()->GetAtere() >= 100)
	{
		SkillManager::PlayerSkillManager->UseSkill("Order");
		AlertTime = Alert_Time;
		return;
	}


	if (true == IsGround && 0 >= GetMoveVectorForce().Y)
	{
		ChangeToStand();
		return;
	}

	if (true == IsRope && GameEngineInput::IsPress(VK_UP, this))
	{
		ChangeState(PlayerState::Rope);
		GravityReset();
		MoveVectorForceReset();
		GroundJump = false;
		DoubleJump = false;
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
		case ActorDir::Max:
		default:
			break;
		}

		switch (GroundJump)
		{
		case true:
			MoveVectorForce += MoveDir * _Delta * JumpAirSpeed;
			break;
		case false:
			MoveVectorForce += MoveDir * _Delta * AirSpeed;
			break;
		}
	}


	if (true == DoubleJump)
	{
		return;
	}

	if (GameEngineInput::IsDown('X', this))
	{
		GravityReset();
		std::shared_ptr<AdeleSkill> BoltJumpActor = GetLevel()->CreateActor<AdeleSkill>();
		std::shared_ptr<AdeleSkill> DoubleJumpActor = GetLevel()->CreateActor<AdeleSkill>();
		DoubleJump = true;
		if (Flying == true && GameEngineInput::IsPress(VK_UP, this))
		{
			BoltJumpActor->SetSkillActor("BoltJump");
			AddMoveVectorForce(float4(0, FlyingDoubleJumpUp));
		}
		else if (GameEngineInput::IsPress(VK_UP, this))
		{
			BoltJumpActor->SetSkillActor("BoltJump");
			AddMoveVectorForce(float4(0, DoubleJumpUP));
		}
		else if (GameEngineInput::IsPress(VK_LEFT, this))
		{
			DoubleJumpActor->SetSkillActor("DoubleJump");
			AddMoveVectorForce(float4(-DoubleJumpDistance, DoubleJumpHeight));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT, this))
		{
			DoubleJumpActor->SetSkillActor("DoubleJump");
			AddMoveVectorForce(float4(DoubleJumpDistance, DoubleJumpHeight));
		}

		if (false == GameEngineInput::IsPress(VK_UP, this) && abs(NoKeyDoubleJumpDistance) > abs(MoveVectorForce.X))
		{
			switch (Dir)
			{
			case ActorDir::Right:
				DoubleJumpActor->SetSkillActor("DoubleJump");
				MoveVectorForce.X = NoKeyDoubleJumpDistance;
				break;
			case ActorDir::Left:
				DoubleJumpActor->SetSkillActor("DoubleJump");
				MoveVectorForce.X = -NoKeyDoubleJumpDistance;
				break;
			case ActorDir::Max:
			default:
				break;
			}
		}
	}
}

//void Player::DownStart()
//{
//	MainSpriteRenderer->ChangeAnimation("Down");
//	HitCollision->Transform.SetLocalScale({ 32, 40 });
//	HitCollision->Transform.SetLocalPosition({ 0, 20 });
//}

void Player::RopeStart()
{
	float4 CurPos = Transform.GetWorldPosition();
	Transform.SetLocalPosition(float4(CurPos.X + RopePivot, CurPos.Y, CurPos.Z));
	MainSpriteRenderer->ChangeAnimation("Normal_Rope");
	GravityOff();
}

void Player::RopeUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	if (GameEngineInput::IsPress(VK_UP, this))
	{
		MovePos += float4::UP * _Delta * 200.0f;
		MainSpriteRenderer->AnimationPauseOff();
	}
	else if (GameEngineInput::IsPress(VK_DOWN, this))
	{
		MovePos += float4::DOWN * _Delta * 200.0f;
		MainSpriteRenderer->AnimationPauseOff();
	}
	else if (GameEngineInput::IsPress(VK_RIGHT, this) || GameEngineInput::IsPress(VK_LEFT, this))
	{
		MainSpriteRenderer->AnimationPauseOn();
		if (GameEngineInput::IsDown('X', this))
		{
			DirCheck();
			ChangeState(PlayerState::Jump);
			return;
		}
	}
	else
	{
		MainSpriteRenderer->AnimationPauseOn();
	}

	Transform.AddLocalPosition(MovePos);
	RopeCheck();
	if (false == IsRope)
	{
		MoveVectorForceReset();
		ChangeToStand();
		return;
	}
}
void Player::AttackStart()
{
	IsAttack = true;
	MainSpriteRenderer->ChangeAnimation("Normal_Attack");
	SkillManager::PlayerSkillManager->UseSkill("Divide1");
	AlertTime = Alert_Time;
}

void Player::AttackUpdate(float _Delta)
{
	if (GameEngineInput::IsDown('A', this) && PlayerValue::GetValue()->GetAtere() >= 100)
	{
		SkillManager::PlayerSkillManager->UseSkill("Order");
		AlertTime = Alert_Time;
		return;
	}

	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		if (true == IsGround)
		{
			ChangeToStand();
		}
		else
		{
			ChangeState(PlayerState::Jump);
			return;
		}
	}
}

void Player::AttackEnd()
{
	IsAttack = false;
}

void Player::StandEnd()
{

}

void Player::AlertEnd()
{
	Player::StandEnd();
}

void Player::WalkEnd()
{

}

void Player::JumpEnd()
{
}


void Player::RopeEnd()
{
	GravityReset();
	MoveVectorForceReset();
	GravityOn();
	MainSpriteRenderer->AnimationPauseOff();
	if (true == GameEngineInput::IsPress(VK_UP, this))
	{
		Transform.AddLocalPosition(float4(0, 15.0f));
	}
}

void Player::DeadStart()
{
}
void Player::DeadUpdate(float _Delta)
{

}
void Player::DeadEnd()
{

}
void Player::FlyStart()
{
	MainSpriteRenderer->ChangeAnimation("Normal_Fly");
	Transform.SetLocalPosition(PlayerPos);
	//FlyTime = 0.0f;
	Flying = true;
}
void Player::FlyUpdate(float _Delta)
{
	/// Flying
	{
		FlyTime += _Delta;
		Transform.SetLocalPosition(PlayerPos);
		SetMoveVectorXForce(0.0f);
		SetMoveVectorYForce(0.0f);
		GravityReset();
		if (FlyTime >= FlyLimitTime)
		{
			FlyTime = 0.0f;
			IsAttack = false;
			ChangeToStand();
			return;
		}
	}

	// Fling중 공격
	if (MainSpriteRenderer->IsCurAnimation("Normal_Attack"))
	{
		if (true == MainSpriteRenderer->IsCurAnimationEnd())
		{
			MainSpriteRenderer->ChangeAnimation("Normal_Fly");
			IsAttack = false;
		}
	}
	if (GameEngineInput::IsDown(VK_SHIFT, this) && IsAttack == false)
	{
		SetMoveVectorXForce(0.0f);
		SetMoveVectorYForce(0.0f);
		IsAttack = true;
		MainSpriteRenderer->ChangeAnimation("Normal_Attack");
		SkillManager::PlayerSkillManager->UseSkill("Divide1");
		AlertTime = Alert_Time;
		return;
	}

	if (GameEngineInput::IsDown('A', this) && PlayerValue::GetValue()->GetAtere() >= 100)
	{
		SkillManager::PlayerSkillManager->UseSkill("Order");
		AlertTime = Alert_Time;
		return;
	}


	// 더블 점프 상황
	if (GameEngineInput::IsDown('X', this))
	{
		ChangeState(PlayerState::Jump);
		return;
	}
}
void Player::FlyEnd()
{
	GravityReset();
}
void Player::ProneStart()
{
	MainSpriteRenderer->ChangeAnimation("Normal_Prone");
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
void Player::ProneEnd()
{

}
void Player::ProneAttackStart()
{
}
void Player::ProneAttackUpdate(float _Delta)
{
}
void Player::ProneAttackEnd()
{
}

void Player::SwingBStart()
{
	IsAttack = true;
	AlertTime = Alert_Time;
	MainSpriteRenderer->ChangeAnimation("Normal_SwingB");
	SkillManager::PlayerSkillManager->UseSkill("Scoll");
}
void Player::SwingBUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeToStand();
	}
}
void Player::SwingBEnd()
{
	IsAttack = false;
}

void Player::SwingYStart()
{
	IsAttack = true;
	AlertTime = Alert_Time;
	MainSpriteRenderer->ChangeAnimation("Normal_SwingY");
	SkillManager::PlayerSkillManager->UseSkill("Shard");
}
void Player::SwingYUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeToStand();
	}
}
void Player::SwingYEnd()
{
	IsAttack = false;
}

void Player::MaestroStart()
{
	PlayerCol->Off();
	IsAttack = true;
	SkillManager::PlayerSkillManager->UseSkill("Maestro");
	MaestroUse = true;
}
void Player::MaestroUpdate(float _Delta)
{
	SetMoveVectorXForce(0.0f);
	SetMoveVectorYForce(0.0f);
	GravityReset();

	Transform.SetLocalPosition(PlayerPos);
	if (MaestroTime >= 8.0f)
	{
		if (true == IsGround)
		{
			ChangeToStand();
		}
		else
		{
			ChangeState(PlayerState::Jump);
			return;
		}
	}
}
void Player::MaestroEnd()
{
	IsAttack = false;
	GravityReset();
}