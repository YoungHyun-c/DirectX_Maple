#include "PreCompile.h"
#include "MainUIActor.h"

MainUIActor::MainUIActor()
{

}

MainUIActor::~MainUIActor()
{

}

MainUIActor* MainUIActor::PlayerUiActor = nullptr;

void MainUIActor::Start()
{
	PlayerUiActor = this;
	WindowHalfPos = GlobalValue::WinScale.Half();

	if (nullptr == GameEngineSprite::Find("ExpBar.Png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("UITexture");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("LWGaugeUI_background.Png");
		GameEngineSprite::CreateSingle("LWGaugeUI.gauge.png");
		GameEngineSprite::CreateSingle("ExpBar.Png");
		GameEngineSprite::CreateSingle("ExpMax.Png");
		GameEngineSprite::CreateSingle("ErdaGauge.Png");
		GameEngineSprite::CreateSingle("SolErdagauge.Png");
		GameEngineSprite::CreateSingle("SolErdagaugeMax.Png");
		GameEngineSprite::CreateSingle("MainBarStatus.Png");
		GameEngineSprite::CreateSingle("HpBar.Png");
		GameEngineSprite::CreateSingle("MpBar.Png");

		GameEngineSprite::CreateSingle("Number_0.Png");
		GameEngineSprite::CreateSingle("Number_1.Png");
		GameEngineSprite::CreateSingle("Number_2.Png");
		GameEngineSprite::CreateSingle("Number_3.Png");
		GameEngineSprite::CreateSingle("Number_4.Png");
		GameEngineSprite::CreateSingle("Number_5.Png");
		GameEngineSprite::CreateSingle("Number_6.Png");
		GameEngineSprite::CreateSingle("Number_7.Png");
		GameEngineSprite::CreateSingle("Number_8.Png");
		GameEngineSprite::CreateSingle("Number_9.Png");
		GameEngineSprite::CreateSingle("Percent.Png");
	}

	{
		AtereAnime = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereAnime->CreateAnimation("AtereAnime_Back", "AtereAnime", 0.3f, -1, -1, true);
		AtereAnime->ChangeAnimation("AtereAnime_Back");
		AtereAnime->AutoSpriteSizeOn();
		AtereAnime->Transform.SetLocalPosition({ 602.0f, 141.0f });
	}

	{
		AtereGaugeBack = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereGaugeBack->SetSprite("LWGaugeUI_background.png");
		AtereGaugeBack->AutoSpriteSizeOn();
		AtereGaugeBack->Transform.SetLocalPosition({ 600.0f, 75.0f });
	}

	{
		AtereGauge = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereGauge->SetSprite("LWGaugeUI.gauge.png");
		AtereGauge->AutoSpriteSizeOn();
		AtereGauge->Transform.SetLocalPosition({ 600.0f, 90.0f });
	}


	{
		ExpBarUi = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		ExpBarUi->SetSprite("ExpBar.png");
		ExpBarUi->SetPivotType(PivotType::Left);
		ExpBarUi->AutoSpriteSizeOn();
		ExpBarUi->Transform.SetLocalPosition({ -GlobalValue::WinScale.hX(), -GlobalValue::WinScale.hY() + 10.0f});

		ExpBarMin = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		ExpBarMin->SetSprite("ExpMax.png");
		ExpBarMin->SetPivotType(PivotType::Left);
		ExpBarMin->Transform.SetLocalPosition({ -GlobalValue::WinScale.hX() + 15, -GlobalValue::WinScale.hY() + 10.0f });

		MainBarStatus = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		MainBarStatus->SetSprite("MainBarStatus.png");
		MainBarStatus->SetPivotType(PivotType::Center);
		MainBarStatus->AutoSpriteSizeOn();
		MainBarStatus->Transform.SetLocalPosition({ 0.0f, -GlobalValue::WinScale.hY() + 50.0f });

		MainHpBar = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		MainHpBar->SetSprite("HpBar.png");
		MainHpBar->SetPivotType(PivotType::Left);
		MainHpBar->SetImageScale({ 172.0f,12.0f });
		MainHpBar->Transform.SetLocalPosition({ -77.0f, -GlobalValue::WinScale.hY() + 50.0f });

		MainMpBar = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		MainMpBar->SetSprite("MpBar.png");
		MainMpBar->SetPivotType(PivotType::Left);
		MainMpBar->SetImageScale({ 172.0f,12.0f });
		MainMpBar->Transform.SetLocalPosition({ -77.0f, -GlobalValue::WinScale.hY() + 34.0f });
	}

	////// Hp, Mp 퍼센트
	{
		//// Hp
		PlayerHpNumberRender1 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerHpNumberRender1->SetSprite("Number_1.Png");
		PlayerHpNumberRender1->SetImageScale(FontImageScale);
		PlayerHpNumberRender1->Transform.SetLocalPosition({ -10.0f, -GlobalValue::WinScale.hY() + 50.0f });

		PlayerHpNumberRender2 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerHpNumberRender2->SetSprite("Number_0.Png");
		PlayerHpNumberRender2->SetImageScale(FontImageScale);
		PlayerHpNumberRender2->Transform.SetLocalPosition({ 0.0f, -GlobalValue::WinScale.hY() + 50.0f });

		PlayerHpNumberRender3 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerHpNumberRender3->SetSprite("Number_0.Png");
		PlayerHpNumberRender3->SetImageScale(FontImageScale);
		PlayerHpNumberRender3->Transform.SetLocalPosition({ 10.0f, -GlobalValue::WinScale.hY() + 50.0f });

		PlayerHpNumberRender4 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerHpNumberRender4->SetSprite("Percent.Png");
		PlayerHpNumberRender4->SetImageScale(FontImageScale);
		PlayerHpNumberRender4->Transform.SetLocalPosition({ 20.0f, -GlobalValue::WinScale.hY() + 50.0f });


		//// Mp
		PlayerMpNumberRender1 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerMpNumberRender1->SetSprite("Number_1.Png");
		PlayerMpNumberRender1->SetImageScale(FontImageScale);
		PlayerMpNumberRender1->Transform.SetLocalPosition({ -10.0f,  -GlobalValue::WinScale.hY() + 34.0f });

		PlayerMpNumberRender2 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerMpNumberRender2->SetSprite("Number_0.Png");
		PlayerMpNumberRender2->SetImageScale(FontImageScale);
		PlayerMpNumberRender2->Transform.SetLocalPosition({ 0.0f, -GlobalValue::WinScale.hY() + 34.0f });

		PlayerMpNumberRender3 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerMpNumberRender3->SetSprite("Number_0.Png");
		PlayerMpNumberRender3->SetImageScale(FontImageScale);
		PlayerMpNumberRender3->Transform.SetLocalPosition({ 10.0f, -GlobalValue::WinScale.hY() + 34.0f });

		PlayerMpNumberRender4 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerMpNumberRender4->SetSprite("Percent.Png");
		PlayerMpNumberRender4->SetImageScale(FontImageScale);
		PlayerMpNumberRender4->Transform.SetLocalPosition({ 20.0f, -GlobalValue::WinScale.hY() + 34.0f });
	}

	GameEngineInput::AddInputObject(this);

}

void MainUIActor::Update(float _Delta)
{
	float ExpRatio = (1366.0f / static_cast<float>(PlayerValue::GetValue()->GetMaxExp()));
	ExpBarMin->SetImageScale({ static_cast<float>(PlayerValue::GetValue()->GetExp()) * ExpRatio , 7.0f});

	float HpRatio = (172.0f / static_cast<float>(PlayerValue::GetValue()->GetMaxHp()));
	MainHpBar->SetImageScale({ static_cast<float>(PlayerValue::GetValue()->GetHp()) * HpRatio, 12.0f });

	float MpRatio = (172.0f / static_cast<float>(PlayerValue::GetValue()->GetMaxMp()));
	MainMpBar->SetImageScale({ static_cast<float>(PlayerValue::GetValue()->GetMp()) * MpRatio, 12.0f });

	if (GameEngineInput::IsDown('=', this))
	{
		PlayerValue::GetValue()->AddExp(50);
		PlayerValue::GetValue()->AddHp(10);
		PlayerValue::GetValue()->AddMp(10);
	}
	if (GameEngineInput::IsDown('-', this))
	{
		PlayerValue::GetValue()->AddExp(10);
		GlobalValue::GetNeedGlobalValue()->AddDropItemCount(10);
		PlayerValue::GetValue()->SubHp(10);
		PlayerValue::GetValue()->SubMp(10);
	}
	if (GameEngineInput::IsDown('0', this))
	{
		PlayerValue::GetValue()->AddExp(1);
		PlayerValue::GetValue()->SubHp(1);
		PlayerValue::GetValue()->SubMp(1);
	}

	/// Hp 퍼센트 Ui
	PlayerHpPerUiRenderer();
	/// Mp 퍼센트 Ui
	PlayerMpPerUiRenderer();
}

void MainUIActor::PlayerHpPerUiRenderer()
{
	CurHpCal = (PlayerValue::GetValue()->GetHp());
	MainHpCal =(PlayerValue::GetValue()->GetMaxHp());
	PercentFrontHp = (CurHpCal * 100 / MainHpCal);

	int NumArr[3] = { 0, };
	NumArr[0] = PercentFrontHp / 10;
	NumArr[1] = PercentFrontHp % 10;

	// Hp
	std::string TextureName1 = "Number_" + std::to_string(NumArr[0]) + ".Png";
	std::string TextureName2 = "Number_" + std::to_string(NumArr[1]) + ".Png";

	// Hp
	{
		if (PercentFrontHp >= 100)
		{
			PlayerHpNumberRender1->SetSprite("Number_1.Png");
			PlayerHpNumberRender1->SetImageScale(FontImageScale);
			PlayerHpNumberRender1->On();
			PlayerHpNumberRender2->SetSprite("Number_0.Png");
			PlayerHpNumberRender2->SetImageScale(FontImageScale);
			PlayerHpNumberRender2->On();
			PlayerHpNumberRender3->SetSprite("Number_0.Png");
			PlayerHpNumberRender3->SetImageScale(FontImageScale);
			PlayerHpNumberRender3->On();
			return;
		}

		if (PercentFrontHp < 10)
		{
			PlayerHpNumberRender1->Off();
			PlayerHpNumberRender2->Off();
			PlayerHpNumberRender3->SetSprite(TextureName2);
			PlayerHpNumberRender3->SetImageScale(FontImageScale);
			PlayerHpNumberRender3->On();
			return;
		}

		if (CurHpCal <= 0)
		{
			PlayerHpNumberRender1->SetSprite("Number_0.Png");
			PlayerHpNumberRender1->Off();
			PlayerHpNumberRender2->SetSprite("Number_0.Png");
			PlayerHpNumberRender2->Off();
			PlayerHpNumberRender3->SetSprite("Number_0.Png");
			PlayerHpNumberRender3->SetImageScale(FontImageScale);
			return;
		}

		PlayerHpNumberRender1->Off();
		PlayerHpNumberRender2->SetSprite(TextureName1);
		PlayerHpNumberRender2->SetImageScale(FontImageScale);
		PlayerHpNumberRender2->On();
		PlayerHpNumberRender3->SetSprite(TextureName2);
		PlayerHpNumberRender3->SetImageScale(FontImageScale);
		PlayerHpNumberRender3->On();
	}
}

void MainUIActor::PlayerMpPerUiRenderer()
{
	CurMpCal = (PlayerValue::GetValue()->GetMp());
	MainMpCal = (PlayerValue::GetValue()->GetMaxMp());
	PercentFrontMp = (CurMpCal * 100 / MainMpCal);

	int MpNumArr[3] = { 0, };
	MpNumArr[0] = PercentFrontMp / 10;
	MpNumArr[1] = PercentFrontMp % 10;

	// Hp
	std::string MpTextureName1 = "Number_" + std::to_string(MpNumArr[0]) + ".Png";
	std::string MpTextureName2 = "Number_" + std::to_string(MpNumArr[1]) + ".Png";

	// Mp
	{
		if (PercentFrontMp >= 100)
		{
			PlayerMpNumberRender1->SetSprite("Number_1.Png");
			PlayerMpNumberRender1->SetImageScale(FontImageScale);
			PlayerMpNumberRender1->On();
			PlayerMpNumberRender2->SetSprite("Number_0.Png");
			PlayerMpNumberRender2->SetImageScale(FontImageScale);
			PlayerMpNumberRender2->On();
			PlayerMpNumberRender3->SetSprite("Number_0.Png");
			PlayerMpNumberRender3->SetImageScale(FontImageScale);
			PlayerMpNumberRender3->On();
			return;
		}

		if (PercentFrontMp < 10)
		{
			PlayerMpNumberRender1->Off();
			PlayerMpNumberRender2->Off();
			PlayerMpNumberRender3->SetSprite(MpTextureName2);
			PlayerMpNumberRender3->SetImageScale(FontImageScale);
			PlayerMpNumberRender3->On();
			return;
		}

		if (CurMpCal <= 0)
		{
			PlayerMpNumberRender1->SetSprite("Number_0.Png");
			PlayerMpNumberRender1->Off();
			PlayerMpNumberRender2->SetSprite("Number_0.Png");
			PlayerMpNumberRender2->Off();
			PlayerMpNumberRender3->SetSprite("Number_0.Png");
			PlayerMpNumberRender3->SetImageScale(FontImageScale);
			return;
		}

		PlayerMpNumberRender1->Off();
		PlayerMpNumberRender2->SetSprite(MpTextureName1);
		PlayerMpNumberRender2->SetImageScale(FontImageScale);
		PlayerMpNumberRender2->On();
		PlayerMpNumberRender3->SetSprite(MpTextureName2);
		PlayerMpNumberRender3->SetImageScale(FontImageScale);
		PlayerMpNumberRender3->On();
	}
}