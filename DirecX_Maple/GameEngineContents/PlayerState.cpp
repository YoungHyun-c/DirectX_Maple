#include "PreCompile.h"
#include "Player.h"
#include "BackGroundMap.h"

#define JumpDistance 200.0f
#define JumpHeight 300.0f

void Player::StandStart()
{
	ChangeAnimationState("Stand");
}
void Player::StandUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT))
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if (GameEngineInput::IsDown('X') || GameEngineInput::IsPress('X'))
	{
		ChangeState(PlayerState::Jump);
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

	if (GameEngineInput::IsPress(VK_LEFT))
	{
		MovePos += MoveDir * WalkSpeed * _Delta;
	}
	if (GameEngineInput::IsPress(VK_RIGHT) && Dir == ActorDir::Right)
	{
		MovePos += MoveDir * WalkSpeed * _Delta;
	}

	Transform.AddLocalPosition(MovePos);

	if (GameEngineInput::IsDown('X') || GameEngineInput::IsPress('X'))
	{
		ChangeState(PlayerState::Jump);
	}

	if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::Stand);
		return;
	}

}

void Player::WalkEnd()
{

}

void Player::AlertStart()
{

}
void Player::AlertUpdate(float _Delta)
{

}
void Player::ProneStart()
{

}
void Player::ProneUpdate(float _Delta)
{

}
void Player::AttackStart()
{

}
void Player::AttackUpdate(float _Delta)
{

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
		if (GameEngineInput::IsPress(VK_LEFT))
		{
			AddMoveVectorForce(float4(-JumpDistance, JumpHeight));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT))
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

	if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
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
}

void Player::JumpEnd()
{
	GravityReset();
	MoveVectorForceReset();
	GroundJump = false;
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