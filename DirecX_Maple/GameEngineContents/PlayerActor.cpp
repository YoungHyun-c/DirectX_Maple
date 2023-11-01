#include "PreCompile.h"
#include "PlayerActor.h"
#include "BackGroundMap.h"

#include "GlobalValue.h"
#include "ContentsCore.h"
#include "Player.h"

PlayerActor::PlayerActor()
{

}

PlayerActor::~PlayerActor()
{

}

void PlayerActor::Start()
{

}

void PlayerActor::Update(float _Delta)
{
	Gravity(_Delta);
	IsGround = CheckGround(float4{0.0f, -35.0f});
	
	// 프리카메라 사용 설정
	IsCameraFocus = GetLevel()->GetMainCamera();
	CameraFocusValue = IsCameraFocus->IsFreeCamera();
	if (CameraFocusValue == true)
	{
		return;
	}
	// 카메라 중심맞추기
	CameraFocus(_Delta);
}

void PlayerActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	if (true == IsGround && 0 >= MoveVectorForce.Y)
	{
		return;
	}

	GravityForce += GravityPower * _Delta;
	if (MaxGravity <= GravityForce)
	{
		GravityForce = MaxGravity;
	}

	MoveVectorForce.Y -= GravityForce * _Delta;
	if (0.0f > MoveVectorForce.Y)
	{
		float4 MoveVectorForceDelta = MoveVectorForce * _Delta;
		GameEngineColor GroundColor = CheckGroundColor(float4{ 0.0f, -35.0f });
		float Count = 0.0f;
		for (; Count <= static_cast<int>(-MoveVectorForceDelta.Y); Count += 1.0f)
		{
			if (DefaultGroundColor == GroundColor)
			{
				break;
			}
			 GroundColor = CheckGroundColor(float4{ 0.0f, -35.0f * Count });
		}
		if (0 != Count)
		{
			MoveVectorForceDelta.Y = -1.0f * Count;
		}
		Transform.AddLocalPosition(MoveVectorForceDelta);
	}
	else
	{
		Transform.AddLocalPosition(MoveVectorForce * _Delta);
	}
}

void PlayerActor::CameraFocus(float _Delta)
{
	float4 PlayerPos = Transform.GetWorldPosition();
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	
	float4 MovePos = (PlayerPos - CameraPos) * CameraSpeed * _Delta;
	GetLevel()->GetMainCamera()->Transform.AddLocalPosition(MovePos);
	CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	
	if (GlobalValue::WinScale.hX() >= CameraPos.X)
	{
		CameraPos.X = GlobalValue::WinScale.hX();
	}
	if (GlobalValue::MapScale.X - GlobalValue::WinScale.hX() <= CameraPos.X)
	{
		CameraPos.X = GlobalValue::MapScale.X - GlobalValue::WinScale.hX();
	}


	if (GlobalValue::WinScale.hY() >= -CameraPos.Y)
	{
		CameraPos.Y = -GlobalValue::WinScale.hY();
	}
	if (GlobalValue::MapScale.Y - GlobalValue::WinScale.hY() <= -CameraPos.Y)
	{
		CameraPos.Y = -(GlobalValue::MapScale.Y - GlobalValue::WinScale.hY());
	}
	
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(CameraPos);
}

GameEngineColor PlayerActor::CheckGroundColor(float4 _CheckPos)
{
	GameEngineColor CheckColor = BackGroundMap::MainMap->GetColor(Transform.GetWorldPosition() + _CheckPos, DefaultGroundColor, DebugMapName);
	return CheckColor;
}

bool PlayerActor::CheckGround(float4 _CheckPos)
{
	bool Result = false;
	GameEngineColor CheckColor = BackGroundMap::MainMap->GetColor(Transform.GetWorldPosition() + _CheckPos, DefaultGroundColor, DebugMapName);
	if (DefaultGroundColor == CheckColor)
	{
		Result = true;
	}
	else
	{
		Result = false;
	}

	return Result;
}
