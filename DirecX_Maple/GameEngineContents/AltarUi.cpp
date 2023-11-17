#include "PreCompile.h"
#include "AltarUi.h"

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
}