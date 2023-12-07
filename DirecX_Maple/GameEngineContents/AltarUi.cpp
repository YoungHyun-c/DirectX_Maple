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

	Altar->SetEndEvent("AltarAppear", [&](GameEngineSpriteRenderer*)
		{
			Altar->ChangeAnimation("AltarStand0");
			AltarCol->On();
			GameEngineSound::SoundPlay("AltarAppear.mp3");
		});

	Altar->SetStartEvent("AltarSuccess", [&](GameEngineSpriteRenderer*)
		{
			AltarCol->Off();
			GameEngineSound::SoundPlay("AltarSucceess.mp3");
		});

	Altar->SetFrameEvent("AltarSuccess", 5, [&](GameEngineSpriteRenderer*)
		{
			PlayerValue::GetValue()->RedToGreen();
		});

	Altar->SetEndEvent("AltarSuccess", [&](GameEngineSpriteRenderer*)
		{
			Altar->Off();
			AltarAppear = false;
			GlobalValue::GetNeedGlobalValue()->SetAltarValue(false);
		});

	Altar->SetStartEvent("AltarFail", [&](GameEngineSpriteRenderer*)
		{
			AltarCol->Off();
		});
	Altar->SetEndEvent("AltarFail", [&](GameEngineSpriteRenderer*)
		{
			Altar->Off();
		});

	/*SpwanX = XRandom.RandomFloat(300.0f, 1600.0f);
	Altar->Transform.SetWorldPosition({ SpwanX, -610.0f });*/

	Altar->AutoSpriteSizeOn();
	Altar->ChangeAnimation("AltarAppear");
	Altar->Off();

	AltarPos = Altar->Transform.GetWorldPosition();

	AltarCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Altar);
	AltarCol->SetCollisionType(ColType::AABBBOX2D);
	//AltarCol->Transform.SetLocalPosition({ AltarPos.X - 15.0f , AltarPos.Y - 50.0f });
	AltarCol->Transform.SetLocalScale({ 300.0f, 150.0f });
	AltarCol->Off();
	GameEngineInput::AddInputObject(this);
}

void AltarUi::Update(float _Delta)
{
	if (GlobalValue::GetNeedGlobalValue()->GetSickleCutValue() == true)
	{
		Altar->ChangeAnimation("AltarFail");
		AltarAppear = false;
	}

	if (PlayerValue::GetValue()->GetRedDeathValue() >= PlayerValue::GetValue()->GetGreenDeathValue() && AltarAppear == false
		&& GlobalValue::GetNeedGlobalValue()->GetSickleCutValue() == false)
	{
		SpwanX = XRandom.RandomFloat(300.0f, 1600.0f);
		Altar->Transform.SetWorldPosition({ SpwanX, -610.0f });
		AltarCol->Transform.SetLocalPosition({ Altar->Transform.GetWorldPosition().X - 15.0f , Altar->Transform.GetWorldPosition().Y - 50.0f });
		Altar->ChangeAnimation("AltarAppear");
		Altar->On();
		AltarAppear = true;
	}

	AltarColEvent();
}

void AltarUi::AltarColEvent()
{
	AltarEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			if (GameEngineInput::IsDown(VK_SPACE, this))
			{
				StandState += 1;
			}
			if (StandState == 2)
			{
				Altar->ChangeAnimation("AltarStand1");
				return;
			}
			if (StandState == 5)
			{
				Altar->ChangeAnimation("AltarStand2");
				return;
			}
			if (StandState == 8)
			{
				Altar->ChangeAnimation("AltarStand3");
				return;
			}
			if (StandState == 11)
			{
				GlobalValue::GetNeedGlobalValue()->SetAltarValue(true);
				Altar->ChangeAnimation("AltarSuccess");
				StandState = 0;
				//PlayerValue::GetValue()->RedToGreen();
				return;
			}
		};
	AltarCol->CollisionEvent(ContentsCollisionType::Player, AltarEvent);
}

void AltarUi::LevelStart(GameEngineLevel* _PreveLevel)
{
	//if (nullptr == GameEngineSprite::Find("Altar"))
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentsResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("FolderTexture");
	//	Dir.MoveChild("Monster");
	//	Dir.MoveChild("BossJin");
	//	Dir.MoveChild("JinHillaUI");
	//	Dir.MoveChild("Altar");
	//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	//	for (size_t i = 0; i < Directorys.size(); i++)
	//	{
	//		GameEngineDirectory& Dir = Directorys[i];
	//		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	//	}
	//}

	//Altar = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//Altar->CreateAnimation("AltarAppear", "AltarAppear", 0.1f, -1, -1, false);
	//Altar->CreateAnimation("AltarFail", "AltarFail", 0.1f, -1, -1, false);
	//Altar->CreateAnimation("AltarSuccess", "AltarSuccess", 0.1f, -1, -1, false);
	//Altar->CreateAnimation("AltarStand0", "AltarStand0", 0.1f, -1, -1, false);
	//Altar->CreateAnimation("AltarStand1", "AltarStand1", 0.1f, -1, -1, false);
	//Altar->CreateAnimation("AltarStand2", "AltarStand2", 0.1f, -1, -1, false);
	//Altar->CreateAnimation("AltarStand3", "AltarStand3", 0.1f, -1, -1, false);

	//Altar->SetEndEvent("AltarAppear", [&](GameEngineSpriteRenderer*)
	//	{
	//		Altar->ChangeAnimation("AltarStand0");
	//		AltarCol->On();
	//	});

	//Altar->SetStartEvent("AltarSuccess", [&](GameEngineSpriteRenderer*)
	//	{
	//		Altar->Off();
	//		AltarCol->Off();
	//	});

	////float SpwanX = XRandom.RandomFloat(300.0f, 1600.0f);
	////Altar->Transform.SetWorldPosition({ SpwanX, -610.0f });
	//
	//Altar->Transform.SetWorldPosition({ 980.0f, -610.0f });
	//Altar->AutoSpriteSizeOn();
	//Altar->ChangeAnimation("AltarAppear");
	//Altar->On();

	//float4 AltarPos = Altar->Transform.GetWorldPosition();

	//AltarCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Altar);
	//AltarCol->SetCollisionType(ColType::AABBBOX2D);
	//AltarCol->Transform.SetLocalPosition({ AltarPos.X - 15.0f , AltarPos.Y - 50.0f});
	//AltarCol->Transform.SetLocalScale({ 300.0f, 150.0f });
	//AltarCol->Off();
}

void AltarUi::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}