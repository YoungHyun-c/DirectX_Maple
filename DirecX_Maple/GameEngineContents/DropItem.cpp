#include "PreCompile.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "BackGroundMap.h"

#include "DropItem.h"
#include "Player.h"


DropItem::DropItem()
{
}

DropItem::~DropItem()
{
}

void DropItem::Start()
{
	DropItemRender = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	DropItemRender->Off();
	DropItemCollision = CreateComponent<GameEngineCollision>(ContentsObjectType::UI);
	DropItemCollision->Off();

	ColMap = BackGroundMap::MainMap->GetColMap();

}

void DropItem::Update(float _DeltaTime)
{
	MoveDropItem(_DeltaTime);
}


void DropItem::MoveDropItem(float _DeltaTime)
{

	if (isFuncSet == false || isInfoSet == false)
	{
		return;
	}

	if (isGet == true)
	{
		//�÷��̾�� �ٰ����� ���
		float4 CurPos = Transform.GetLocalPosition();

		if (DropItemCollision->IsUpdate() == false)
		{
			Transform.AddLocalPosition({ 0, 140.0f * _DeltaTime });

			if (abs(CurPos.Y - StartPos.Y) >= 10.0f)
			{
				DropItemCollision->On();
			}
		}
		else
		{
			float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
			float4 GetDir = { PlayerPos.X - CurPos.X , PlayerPos.Y - CurPos.Y + 15.0f };
			GetDir.Normalize();

			Transform.AddLocalPosition(GetDir * -250.0f * _DeltaTime);
		}
	}

	if (isGround == true)
	{
		if (UpMove == true)
		{
			VerticalMoveCount += 5.0f * _DeltaTime;
			Transform.AddLocalPosition({ 0, 5.0f * _DeltaTime });

			if (VerticalMoveCount >= 5.0f)
			{
				VerticalMoveCount = 0.0f;
				UpMove = false;
				DownMove = true;
			}
		}
		else if (DownMove == true)
		{
			VerticalMoveCount -= 5.0f * _DeltaTime;
			Transform.AddLocalPosition({ 0, -5.0f * _DeltaTime });

			if (VerticalMoveCount <= -5.0f)
			{
				VerticalMoveCount = 0.0f;
				UpMove = true;
				DownMove = false;
			}
		}

		return;
	}

	float4 NextPos;
	float4 CurPos = Transform.GetLocalPosition();

	NextPos.X = CurPos.X + 2.0f * XDistance * _DeltaTime;
	NextPos.Y = CurPos.Y;

	float4 MapSize = ColMap->GetScale();

	float4 ColorPos;
	ColorPos.X = + NextPos.X;
	ColorPos.Y = - NextPos.Y;

	GameEngineColor Color = { 255, 0, 0, 255 };
	GameEngineColor MapColor = ColMap->GetColor(ColorPos, DefaultGroundColor);

	if (Color == MapColor)
	{
		NextPos.X = CurPos.X;
		NextPos.Y -= 400.0f * _DeltaTime;
	}
	else
	{
		NextPos.X = CurPos.X + 0.75f * XDistance * _DeltaTime;
		NextPos.Y = Coefficient * (NextPos.X - StartPos.X) * (NextPos.X - Xintercept) + StartPos.Y;
	}

	ColorPos.X = + NextPos.X;
	ColorPos.Y = - NextPos.Y;
	MapColor = ColMap->GetColor(ColorPos, DefaultGroundColor);

	if (Color == MapColor)
	{
		while (Color == MapColor)
		{
			NextPos.Y++;
			ColorPos.Y--;

			MapColor = ColMap->GetColor(ColorPos, DefaultGroundColor);
		}

		int ConvertYtoInt = static_cast<int>(NextPos.Y);

		Transform.SetLocalPosition({ NextPos.X, NextPos.Y + 20.0f});
		DropItemRender->Transform.SetLocalRotation({ 0, 0, 0 });
		isGround = true;
		return;
	}

	Transform.SetLocalPosition(NextPos);
	DropItemRender->Transform.AddLocalRotation({ 0.0f, 0.0f, -Dir * 360.0f * _DeltaTime });
}

void DropItem::SetDropItemInfo(const std::string_view& _ItemName, int _ItemType)
{
	ItemName = _ItemName.data();
	ItemType = _ItemType;

	DropItemRender->SetSprite(ItemName + "Icon.png");

	TransformData RenderData = DropItemRender->Transform.GetConstTransformDataRef();

	DropItemRender->Transform.SetLocalPosition({ 0.0f, RenderData.LocalScale.Y * 0.5f });
	DropItemRender->On();

	DropItemCollision->Transform.SetLocalScale({ 20, 20 });
	DropItemCollision->On();

	isInfoSet = true;
}

void DropItem::GetItem()
{
	isGet = true;
	StartPos = Transform.GetLocalPosition();
	DropItemCollision->Off();
}