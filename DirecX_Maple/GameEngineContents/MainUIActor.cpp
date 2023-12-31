#include "PreCompile.h"
#include "MainUIActor.h"

#include "AtereSword.h"

MainUIActor::MainUIActor()
{

}

MainUIActor::~MainUIActor()
{

}

MainUIActor* MainUIActor::PlayerUiActor = nullptr;

void MainUIActor::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainLv = PlayerValue::GetValue()->GetLevel();
	PlayerLvUiRenderer();

	MainHpBar->SetImageScale({ (CurHpScale / static_cast<float>(PlayerValue::GetValue()->GetMaxHp())) * 172.0f, 12.0f });
	MainMpBar->SetImageScale({ (CurMpScale / static_cast<float>(PlayerValue::GetValue()->GetMaxMp())) * 172.0f, 12.0f });
	AtereBar->SetImageScale({ CurGauge / 100.0f * 97.0f, 27.0f });
	SkillValue::GetValue()->SetOrderCount(0);
}

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

		GameEngineSprite::CreateSingle("Lv_0.Png");
		GameEngineSprite::CreateSingle("Lv_1.Png");
		GameEngineSprite::CreateSingle("Lv_2.Png");
		GameEngineSprite::CreateSingle("Lv_3.Png");
		GameEngineSprite::CreateSingle("Lv_4.Png");
		GameEngineSprite::CreateSingle("Lv_5.Png");
		GameEngineSprite::CreateSingle("Lv_6.Png");
		GameEngineSprite::CreateSingle("Lv_7.Png");
		GameEngineSprite::CreateSingle("Lv_8.Png");
		GameEngineSprite::CreateSingle("Lv_9.Png");
		GameEngineSprite::CreateSingle("Lv.Png");

	}

	if (nullptr == GameEngineSprite::Find("LevelUpMsgback"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("UITexture");
		Dir.MoveChild("LevelUpMsgback");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	// 레벨업
	{
		LevelUpMsgBack = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		LevelUpMsgBack->CreateAnimation("LevelUpMsgback", "LevelUpMsgback", 0.1f, -1, -1, true);
		LevelUpMsgBack->ChangeAnimation("LevelUpMsgback");
		LevelUpMsgBack->Transform.SetLocalPosition({ 0.0f, 250.0f });
		LevelUpMsgBack->AutoSpriteSizeOn();
		LevelUpMsgBack->Off();
		LevelUpMsgBack->SetEndEvent("LevelUpMsgback", [&](GameEngineSpriteRenderer*)
			{
				LevelUpMsgBack->Off();
				LevelUpFontRender->Off();
				LevelUpCongratuFont->Off();
			});
		LevelText = "레벨 " + std::to_string(PlayerValue::GetValue()->GetLevel());
		LevelUpFontRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		LevelUpFontRender->SetText("메이플스토리", LevelText, 50.0f, float4::WHITE);
		LevelUpFontRender->Transform.SetLocalPosition({ -100.0f, 300.0f });
		LevelUpFontRender->Off();

		LevelUpCongratuFont = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		LevelUpCongratuFont->SetText("메이플스토리", "레벨이 올랐습니다!", 25.0f, float4{1.0f, 1.0f, 0.0f, 1.0f});
		LevelUpCongratuFont->Transform.SetLocalPosition({ -110.0f, 235.0f });
		LevelUpCongratuFont->Off();
	}

	{
		AtereAnime = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereAnime->CreateAnimation("AtereAnime_Back", "AtereAnime", 0.3f, -1, -1, true);
		AtereAnime->ChangeAnimation("AtereAnime_Back");
		AtereAnime->AutoSpriteSizeOn();
		AtereAnime->Transform.SetLocalPosition({ 602.0f, 141.0f });
	}

	if (Sword1 == nullptr)
	{
		Sword1 = GetLevel()->CreateActor<AtereSword>(ContentsObjectType::UI);
		Sword1->Transform.SetLocalPosition({ 560.0f, 155.0f });
		Sword2 = GetLevel()->CreateActor<AtereSword>(ContentsObjectType::UI);
		Sword2->Transform.SetLocalPosition({ 603.0f, 165.0f });
		Sword3 = GetLevel()->CreateActor<AtereSword>(ContentsObjectType::UI);
		Sword3->Transform.SetLocalPosition({ 645.0f, 155.0f });
	}

	{
		AtereGaugeBack = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
		AtereGaugeBack->SetSprite("LWGaugeUI_background.png");
		AtereGaugeBack->AutoSpriteSizeOn();
		//AtereGaugeBack->Transform.SetLocalPosition({ 600.0f, 75.0f });
	}

	{
		AtereBar = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
		AtereBar->SetSprite("LWGaugeBar.Png");
		AtereBar->SetImageScale({ 97.0f, 27.0f });
		//AtereBar->Transform.SetLocalPosition({ 600.0f, -900.0f });
		AtereBar->SetPivotType(PivotType::Left);
		AtereBar->RenderBaseInfoValue.Target2 = 1;
		AtereBar->GetColorData().MulColor.A = 0.01f;
	}

	{
		AtereGauge = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
		AtereGauge->SetSprite("LWGaugeUI.gauge.png");
		AtereGauge->SetImageScale({ 97.0f, 27.0f });
		//AtereGauge->AutoSpriteSizeOn();
		//AtereGauge->Transform.SetLocalPosition({ 600.0f, -900.0f });
		AtereGauge->SetPivotType(PivotType::Left);
		AtereGauge->RenderBaseInfoValue.Target1 = 1;
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
		//MainHpBar->SetImageScale({ 172.0f,12.0f });
		CurHpScale = static_cast<float>(PlayerValue::GetValue()->GetHp());
		MainHpBar->SetImageScale({ (PlayerValue::GetValue()->GetHp() / (PlayerValue::GetValue()->GetMaxHp())) * 172.0f * (CurHpScale * 0.01f), 12.0f });
		MainHpBar->Transform.SetLocalPosition({ -77.0f, -GlobalValue::WinScale.hY() + 50.0f });

		MainMpBar = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		MainMpBar->SetSprite("MpBar.png");
		MainMpBar->SetPivotType(PivotType::Left);
		CurMpScale = static_cast<float>(PlayerValue::GetValue()->GetMp());
		MainMpBar->SetImageScale({ (PlayerValue::GetValue()->GetMp() / (PlayerValue::GetValue()->GetMaxMp())) * 172.0f * (CurMpScale * 0.01f), 12.0f });
		MainMpBar->Transform.SetLocalPosition({ -77.0f, -GlobalValue::WinScale.hY() + 34.0f });
	}

	////// Lv
	{
		//MainLv = PlayerValue::GetValue()->GetLevel();
		MainLvRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		MainLvRender->SetSprite("Lv.Png");
		MainLvRender->SetImageScale(FontImageScale);
		MainLvRender->Transform.SetLocalPosition({ -77.0f, -GlobalValue::WinScale.hY() + 71.0f });

		PlayerLvNumberRender1 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerLvNumberRender1->SetSprite("Lv_2.Png");
		PlayerLvNumberRender1->AutoSpriteSizeOn();
		PlayerLvNumberRender1->Transform.SetLocalPosition({ -62.0f, -GlobalValue::WinScale.hY() + 71.0f });

		PlayerLvNumberRender2 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerLvNumberRender2->SetSprite("Lv_5.Png");
		PlayerLvNumberRender2->AutoSpriteSizeOn();
		PlayerLvNumberRender2->Transform.SetLocalPosition({ -52.0f, -GlobalValue::WinScale.hY() + 71.0f });

		PlayerLvNumberRender3 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		PlayerLvNumberRender3->SetSprite("Lv_9.Png");
		PlayerLvNumberRender3->AutoSpriteSizeOn();
		PlayerLvNumberRender3->Transform.SetLocalPosition({ -42.0f, -GlobalValue::WinScale.hY() + 71.0f });
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


	// 퀵슬롯 + 스킬 아이콘
	if (nullptr == GameEngineSprite::Find("QuickSlotTest.Png"))
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

		GameEngineSprite::CreateSingle("QuickBack.Png");

		GameEngineSprite::CreateSingle("Divide5SkillIcon.Png");
		GameEngineSprite::CreateSingle("Divide6Skill.Png");
		GameEngineSprite::CreateSingle("Divide6Special.Png");
		GameEngineSprite::CreateSingle("MaestroIcon.Png");

		GameEngineSprite::CreateSingle("OrderNum0.Png");
		GameEngineSprite::CreateSingle("OrderNum1.Png");
		GameEngineSprite::CreateSingle("OrderNum2.Png");
		GameEngineSprite::CreateSingle("OrderNum3.Png");
		GameEngineSprite::CreateSingle("OrderNum4.Png");
		GameEngineSprite::CreateSingle("OrderNum5.Png");
		GameEngineSprite::CreateSingle("OrderNum6.Png");
		GameEngineSprite::CreateSingle("OrderNum7.Png");
		GameEngineSprite::CreateSingle("OrderNum8.Png");
	}

	// 스킬 퀵슬롯
	QuickSlotImage();

	CurHpScale = static_cast<float>(PlayerValue::GetValue()->GetHp());
	CurMpScale = static_cast<float>(PlayerValue::GetValue()->GetMp());
	GameEngineInput::AddInputObject(this);
}

void MainUIActor::QuickSlotImage()
{

	{
	
		DivideIcon = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		DivideIcon->SetSprite("Divide5SkillIcon.Png");
		DivideIcon->AutoSpriteSizeOn();
		DivideIcon->Transform.SetLocalPosition({ 138.0f, -GlobalValue::WinScale.hY() + 66.0f });
	
		MaestroIcon = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		MaestroIcon->SetSprite("MaestroIcon.Png");
		MaestroIcon->AutoSpriteSizeOn();
		MaestroIcon->Transform.SetLocalPosition({ 418.0f, -GlobalValue::WinScale.hY() + 32.0f });
		MaestroIcon->Off();


		QuickSlotCover = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		QuickSlotCover->SetSprite("QuickBack.Png");
		QuickSlotCover->AutoSpriteSizeOn();
		QuickSlotCover->Transform.SetLocalPosition({ 400.0f, -GlobalValue::WinScale.hY() + 50.0f });

		OrderCountIcon = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		OrderCountIcon->SetSprite("OrderNum0.Png");
		OrderCountIcon->AutoSpriteSizeOn();
		OrderCountIcon->Transform.SetLocalPosition({ 282.0f, -GlobalValue::WinScale.hY() + 27.0f });
	}
}

void MainUIActor::Update(float _Delta)
{
	float ExpRatio = (1366.0f / static_cast<float>(PlayerValue::GetValue()->GetMaxExp()));
	ExpBarMin->SetImageScale({ static_cast<float>(PlayerValue::GetValue()->GetExp()) * ExpRatio , 7.0f});

	if (GameEngineInput::IsDown('P', this))
	{
		PlayerValue::GetValue()->SetMaxAtere();
	}


	AtereUpdate(_Delta);
	QuickSlotUpdate();

	if (GameEngineInput::IsDown('=', this))
	{
		PlayerValue::GetValue()->AddExp(50);
		PlayerValue::GetValue()->AddHp(10);
		PlayerValue::GetValue()->AddMp(10);
	}
	if (GameEngineInput::IsDown('-', this))
	{
		PlayerValue::GetValue()->SubHp(10);
		PlayerValue::GetValue()->SubMp(10);
	}

	HpUpdate(_Delta);
	MpUpdate(_Delta);


	/// Lv Ui
	if (MainLv != PlayerValue::GetValue()->GetLevel())
	{
		PlayerLvUiRenderer();
		LevelUpMsgBack->On();
		LevelUpFontRender->On();
		LevelUpCongratuFont->On();
		LevelText = "레벨 " + std::to_string(PlayerValue::GetValue()->GetLevel());
		LevelUpFontRender->SetText("메이플스토리", LevelText, 50.0f, float4::WHITE);
	}
	/// Hp 퍼센트 Ui
	if (CurHpCal != PlayerValue::GetValue()->GetHp())
	{
		PlayerHpPerUiRenderer();
	}
	/// Mp 퍼센트 Ui
	if (CurMpCal != PlayerValue::GetValue()->GetMp())
	{
		PlayerMpPerUiRenderer();
	}
}

void MainUIActor::QuickSlotUpdate()
{
	if (PlayerValue::GetValue()->GetClass() == "Maestro")
	{
		MaestroIcon->On();
		DivideIcon->SetSprite("Divide6Skill.Png");

		if (PlayerValue::GetValue()->GetDivide6Use() == false)
		{
			DivideIcon->SetSprite("Divide6Special.Png");
		}
	}

	int OrderCount = SkillValue::GetValue()->GetCurOrderCount();
	if (CurOrderCount != OrderCount)
	{
		if (CurOrderCount <= 0)
		{
			CurOrderCount = 0;
		}
		CurOrderCount = OrderCount;
		OrderNum = std::to_string(CurOrderCount);
		OrderCountIcon->SetSprite("OrderNum" + OrderNum + ".Png");
	}
}

void MainUIActor::AtereUpdate(float _Delta)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();
	AtereGaugeBack->Transform.SetLocalPosition({ CameraPos.X + 600.0f, CameraPos.Y + 75.0f });
	AtereBar->Transform.SetLocalPosition({ CameraPos.X + 552.0f, CameraPos.Y + 90.0f });
	AtereGauge->Transform.SetLocalPosition({ CameraPos.X + 552.0f, CameraPos.Y + 90.0f });


	float Atere = static_cast<float>(PlayerValue::GetValue()->GetAtere());
	if (Atere >= 400.0f)
	{
		Sword1->ChangeState(AtereSwordActor::Appear);
		Sword2->ChangeState(AtereSwordActor::Appear);
		Sword3->ChangeState(AtereSwordActor::Appear);

		AtereBar->SetImageScale({ 97.0f  , 27.0f });
	}
	if (Atere < 400.0f && Atere >= 300.0f)
	{
		Sword1->ChangeState(AtereSwordActor::Appear);
		Sword2->ChangeState(AtereSwordActor::Appear);
		Sword3->ChangeState(AtereSwordActor::Appear);
		AtereBar->SetImageScale({ CurGauge - 300 / 100.0f * 97.0f  , 27.0f });
	}
	if (Atere < 300.0f && Atere >= 200.0f)
	{
		Sword1->ChangeState(AtereSwordActor::Appear);
		Sword2->ChangeState(AtereSwordActor::Appear);
		Sword3->ChangeState(AtereSwordActor::End);

		AtereBar->SetImageScale({ CurGauge - 200/ 100.0f * 97.0f  , 27.0f });
	}
	if (Atere < 200.0f && Atere >= 100.0f)
	{
		Sword1->ChangeState(AtereSwordActor::Appear);
		Sword2->ChangeState(AtereSwordActor::End);
		Sword3->ChangeState(AtereSwordActor::End);

		AtereBar->SetImageScale({ CurGauge - 100 / 100.0f * 97.0f  , 27.0f });
	}
	if (Atere < 100.0f)
	{
		Sword1->ChangeState(AtereSwordActor::End);
		Sword2->ChangeState(AtereSwordActor::End);
		Sword3->ChangeState(AtereSwordActor::End);
		AtereBar->SetImageScale({ CurGauge / 100.0f * 97.0f  , 27.0f });
	}
	if (Atere == CurGauge)
	{
		return;
	}
	if (Atere < CurGauge)
	{
		CurGauge -= ScaleSpeed * _Delta;
		if (Atere > CurGauge)
		{
			CurGauge = Atere;
		}
	}
	else if (Atere > CurGauge)
	{
		CurGauge += ScaleSpeed * _Delta;

		if (Atere < CurGauge)
		{
			CurGauge = Atere;
		}
	}
}

void MainUIActor::HpUpdate(float _Delta)
{
	float PlayerHp = static_cast<float>(PlayerValue::GetValue()->GetHp());
	if (PlayerHp == CurHpScale)
	{
		return;
	}

	if (PlayerHp < CurHpScale)
	{
		CurHpScale -= ScaleSpeed * _Delta;
		if (PlayerHp > CurHpScale)
		{
			CurHpScale = PlayerHp;
		}
	}
	else if (PlayerHp > CurHpScale)
	{
		CurHpScale += ScaleSpeed * _Delta;

		if (PlayerHp < CurHpScale)
		{
			CurHpScale = PlayerHp;
		}
	}

	MainHpBar->SetImageScale({ (CurHpScale / static_cast<float>(PlayerValue::GetValue()->GetMaxHp())) * 172.0f, 12.0f });
}

void MainUIActor::MpUpdate(float _Delta)
{
	float PlayerMp = static_cast<float>(PlayerValue::GetValue()->GetMp());
	if (PlayerMp == CurMpScale)
	{
		return;
	}

	if (PlayerMp < CurMpScale)
	{
		CurMpScale -= ScaleSpeed * _Delta;
		if (PlayerMp > CurMpScale)
		{
			CurMpScale = PlayerMp;
		}
	}
	else if (PlayerMp > CurMpScale)
	{
		CurMpScale += ScaleSpeed * _Delta;

		if (PlayerMp < CurMpScale)
		{
			CurMpScale = PlayerMp;
		}
	}

	MainMpBar->SetImageScale({ (CurMpScale / static_cast<float>(PlayerValue::GetValue()->GetMaxMp())) * 172.0f, 12.0f });
}

void MainUIActor::PlayerLvUiRenderer()
{
	MainLv = PlayerValue::GetValue()->GetLevel();
	int LvNumArr[4] = { 0, };
	LvNumArr[0] = MainLv / 100;
	LvNumArr[1] = (MainLv / 10) % 10;
	LvNumArr[2] = MainLv % 10;

	// Lv
	std::string LvTextureName1 = "Lv_" + std::to_string(LvNumArr[0]) + ".Png";
	std::string LvTextureName2 = "Lv_" + std::to_string(LvNumArr[1]) + ".Png";
	std::string LvTextureName3 = "Lv_" + std::to_string(LvNumArr[2]) + ".Png";

	PlayerLvNumberRender1->SetSprite(LvTextureName1);
	PlayerLvNumberRender2->SetSprite(LvTextureName2);
	PlayerLvNumberRender3->SetSprite(LvTextureName3);
}

void MainUIActor::PlayerHpPerUiRenderer()
{
	CurHpCal = (PlayerValue::GetValue()->GetHp());
	MainHpCal =(PlayerValue::GetValue()->GetMaxHp());
	PercentFrontHp = (CurHpCal * 100 / MainHpCal);

	int HpNumArr[3] = { 0, };
	HpNumArr[0] = PercentFrontHp / 10;
	HpNumArr[1] = PercentFrontHp % 10;

	// Hp
	std::string HpTextureName1 = "Number_" + std::to_string(HpNumArr[0]) + ".Png";
	std::string HpTextureName2 = "Number_" + std::to_string(HpNumArr[1]) + ".Png";

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
			PlayerHpNumberRender3->SetSprite(HpTextureName2);
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
		PlayerHpNumberRender2->SetSprite(HpTextureName1);
		PlayerHpNumberRender2->SetImageScale(FontImageScale);
		PlayerHpNumberRender2->On();
		PlayerHpNumberRender3->SetSprite(HpTextureName2);
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