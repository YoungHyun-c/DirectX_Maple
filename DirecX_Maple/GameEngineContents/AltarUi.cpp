#include "PreCompile.h"
#include "AltarUi.h"
#include "BackGroundMap.h"

AltarUi::AltarUi()
{

}

AltarUi::~AltarUi()
{

}

void AltarUi::Start()
{
	
	GameEngineInput::AddInputObject(this);
}

void AltarUi::Update(float _Delta)
{
	if (GameEngineInput::IsDown('4', this))
	{
		Altar->ChangeAnimation("AltarAppear");
	}
	if (GameEngineInput::IsDown('5', this))
	{
		Altar->ChangeAnimation("AltarFail");
	}
	if (GameEngineInput::IsDown('6', this))
	{
		Altar->ChangeAnimation("AltarSuccess");
	}
	if (GameEngineInput::IsDown('7', this))
	{
		Altar->ChangeAnimation("AltarStand0");
	}
	if (GameEngineInput::IsDown('8', this))
	{
		Altar->ChangeAnimation("AltarStand1");
	}
	if (GameEngineInput::IsDown('9', this))
	{
		Altar->ChangeAnimation("AltarStand2");
	}
	if (GameEngineInput::IsDown('0', this))
	{
		Altar->ChangeAnimation("AltarStand3");
	}

	//GroundCheck(_Delta);
}

void AltarUi::LevelStart(GameEngineLevel* _PreveLevel)
{
	if (nullptr == GameEngineSprite::Find("Altar"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaUI");
		Dir.MoveChild("Altar");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	Altar = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	Altar->CreateAnimation("AltarAppear", "AltarAppear", 0.1f, -1, -1, false);
	Altar->CreateAnimation("AltarFail", "AltarFail", 0.1f, -1, -1, false);
	Altar->CreateAnimation("AltarSuccess", "AltarSuccess", 0.1f, -1, -1, false);
	Altar->CreateAnimation("AltarStand0", "AltarStand0", 0.1f, -1, -1, false);
	Altar->CreateAnimation("AltarStand1", "AltarStand1", 0.1f, -1, -1, false);
	Altar->CreateAnimation("AltarStand2", "AltarStand2", 0.1f, -1, -1, false);
	Altar->CreateAnimation("AltarStand3", "AltarStand3", 0.1f, -1, -1, false);

	Altar->Transform.SetWorldPosition({ 980.0f, -610.0f });
	Altar->AutoSpriteSizeOn();
	Altar->ChangeAnimation("AltarAppear");

	float4 AltarPos = Altar->Transform.GetWorldPosition();

	AltarCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Altar);
	AltarCol->SetCollisionType(ColType::AABBBOX2D);
	AltarCol->Transform.SetLocalPosition({ AltarPos.X - 15.0f , AltarPos.Y - 50.0f});
	AltarCol->Transform.SetLocalScale({ 300.0f, 150.0f });

	ColMap = BackGroundMap::MainMap->GetColMap();
}

void AltarUi::GroundCheck(float _Delta)
{
	float4 NextPos;
	float4 CurPos = Transform.GetLocalPosition();


	float4 MapSize = ColMap->GetScale();

	float4 ColorPos;
	ColorPos.X = NextPos.X;
	ColorPos.Y = -NextPos.Y + 50.0f;

	GameEngineColor Color = { 255, 0, 0, 255 };
	GameEngineColor MapColor = ColMap->GetColor(ColorPos, DefaultGroundColor);

	if (Color == MapColor)
	{
		NextPos.X = CurPos.X;
		NextPos.Y += 1.0f;
	}
	else
	{
		NextPos.Y -= 1.0f * _Delta;
	}

	ColorPos.X = +NextPos.X;
	ColorPos.Y = -NextPos.Y;
	MapColor = ColMap->GetColor(ColorPos, DefaultGroundColor);

	//if (Color == MapColor)
	//{
	//	while (Color == MapColor)
	//	{
	//		NextPos.Y++;
	//		ColorPos.Y--;

	//		MapColor = ColMap->GetColor(ColorPos, DefaultGroundColor);
	//	}

	//	int ConvertYtoInt = static_cast<int>(NextPos.Y);

	//	Transform.SetLocalPosition({ NextPos.X, NextPos.Y + 20.0f });
	//	return;
	//}

	Transform.SetLocalPosition(NextPos);
}