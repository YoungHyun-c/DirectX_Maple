#include "PreCompile.h"
#include "PlayerActor.h"
#include "BackGroundMap.h"

#include "GlobalValue.h"
#include "ContentsCore.h"

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
	GameEngineColor Color = BackGroundMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED, DebugMapName);
	if (GameEngineColor::RED != Color)
	{
		GravityForce.Y -= _Delta * 900.0f;
		Transform.AddLocalPosition(GravityForce * _Delta);
	}
	else
	{
		//if (Color != GameEngineColor::White)
		//{
		//	Transform.AddLocalPosition(float4::UP);
		//}
		GravityReset();
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