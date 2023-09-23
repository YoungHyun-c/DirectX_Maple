#include "PreCompile.h"
#include "Player.h"
#include "BackGroundMap.h"



void Player::StandStart()
{
	ChangeAnimationState("Normal_stand");
}
void Player::StandUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT))
	{
		DirCheck();
		ChangeState(PlayerState::Walk);
		return;
	}
}

void Player::WalkStart()
{
	ChangeAnimationState("Normal_Walk");
}
void Player::WalkUpdate(float _Delta)
{
	DirCheck();

	//GameEngineColor Color = BackGroundMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED, DebugMapName);

	//if (GameEngineColor::RED != Color)
	//{
	//	GravityForce.Y -= _Delta * 900.0f;
	//	Transform.AddLocalPosition(GravityForce * _Delta);
	//}
	//else
	//{
	//	//if (Color != GameEngineColor::White)
	//	//{
	//	//	Transform.AddLocalPosition(float4::UP);
	//	//}
	//	GravityForce = 0.0f;
	//}
	float4 MovePos = float4::ZERO;

	if (GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		MovePos = { -WalkSpeed * _Delta, 0.0f };
		//Transform.AddLocalPosition(float4::LEFT * _Delta * WalkSpeed);
	}
	if (GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		//Transform.AddLocalPosition(float4::RIGHT * _Delta * WalkSpeed);
		MovePos = { WalkSpeed * _Delta, 0.0f };
	}
	if (GameEngineInput::IsPress(VK_UP))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * WalkSpeed);
	}
	if (GameEngineInput::IsPress(VK_DOWN))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * WalkSpeed);
	}
	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}
	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}

	if (GameEngineInput::IsDown('X'))
	{
		ChangeState(PlayerState::Jump);
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Stand);
		return;
	}

	Transform.AddLocalPosition(MovePos);
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
	Transform.AddLocalPosition(float4::UP * 400.0f);
	MainSpriteRenderer->ChangeAnimation("Normal_Jump");
}
void Player::JumpUpdate(float _Delta)
{
	
	DirCheck();
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