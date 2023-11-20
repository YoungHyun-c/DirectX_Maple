#include "PreCompile.h"
#include "BackGroundMap.h"
#include "BossLevel.h"
#include "BossEntranceLevel.h"

#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

//#include "JinHillaAnime.h"
#include "JinHillaEnterAnime.h"
#include "ContentsTimer.h"
#include "JinHillaSickleCut.h"
#include "JinHillaBoss.h"
#include "BossLevelUi.h"
#include "PlayerDeathCountUI.h"
#include "CandleUi.h"
#include "AltarUi.h"
#include "HandAttack.h"

#include "MainUIActor.h"
#include "Mouse.h"

#include "JinHillaBoss.h"
#include "BossSkillManager.h"

#include "CravingMonster.h"
#include "GhostSwoo.h"
#include "GhostDamien.h"
#include "MonsterFunction.h"


BossLevel::BossLevel()
{

}

BossLevel::~BossLevel()
{

}

void BossLevel::Start()
{
	// 진힐라 낫베기
	//{
	//	JinHillaAttackAni = CreateActor<JinHillaAnime>(ContentsObjectType::BackGround);
	//}


	// 입장 컷신
	/*{
		EnterAni = CreateActor<JinHillaEnterAnime>(ContentsObjectType::UI);
	}*/


	//{
	//	CravingMob = CreateActor<CravingMonster>(ContentsObjectType::Monster);
	//	CravingMob->Transform.SetWorldPosition({ 900.0f, -800.0f });
	//	CravingMob->SetDebugMap("BOssDebugMap.Png");
	//}

	// 사령 스우, 스우 구체
	{
		//GhostSwooMob = CreateActor<GhostSwoo>(ContentsObjectType::Monster);
		//GhostSwooMob->Transform.SetWorldPosition({ 900.0f, -800.0f });
		//GhostSwooMob->SetDebugMap("BossDebugMap.Png");


	}

	//// 사령 데미안, 이펙트
	//{
		/*GhostDamienMob = CreateActor<GhostDamien>(ContentsObjectType::Monster);
		GhostDamienMob->Transform.SetWorldPosition({ 500.0f, -650.0f, static_cast<float>(DeepBufferType::Monster) });
		GhostDamienMob->SetDebugMap("BossDebugMap.Png");*/

	//}

	GameEngineInput::AddInputObject(this);
}

void BossLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	/////////// 패턴 관련 /////////////
	if (PlayerValue::GetValue()->GetRedDeathValue() >= 1 && Fire1 == false)
	{
		Candle1->FrameChangeAni("CandleFireAppear");
		Candle1->On();
		Fire1 = true;
	}

	if (PlayerValue::GetValue()->GetRedDeathValue() >= 2 && Fire2 == false && CandleCut2 == false)
	{
		Candle2->FrameChangeAni("CandleFireAppear");
		Candle2->On();
		Fire2 = true;
	}

	if (PlayerValue::GetValue()->GetRedDeathValue() >= 3 && Fire3 == false && CandleCut1 == false)
	{
		Candle3->FrameChangeAni("CandleFireAppear");
		Candle3->On();
		Fire3 = true;
	}


	if (GlobalValue::GetNeedGlobalValue()->GetAltarValue() == true)
	{
		Candle1->FrameChangeAni("CandleFireBreak");
		Candle2->FrameChangeAni("CandleFireBreak");
		Candle3->FrameChangeAni("CandleFireBreak");
		Fire1 = false;
		Fire2 = false;
		Fire3 = false;
	}

	if (GlobalValue::GetNeedGlobalValue()->GetSickleCutValue() == true)
	{
		if (PlayerValue::GetValue()->GetGreenDeathValue() <= 4 && CandleCut1 == false
			|| PlayerValue::GetValue()->GetGreenDeathValue() >= 3 && CandleCut1 == false)
		{
			Candle3->CandleChangeAni("CandleStickBreak");
			Candle3->FrameChangeAni("CandleFireBreak");
			CandleCut1 = true;
			Candle1->FrameChangeAni("CandleFireBreak");
			Candle2->FrameChangeAni("CandleFireBreak");
			Fire1 = false;
			Fire2 = false;
			Fire3 = false;
			return;
		}
		if (PlayerValue::GetValue()->GetGreenDeathValue() == 2 && CandleCut2 == false)
		{
			Candle2->CandleChangeAni("CandleStickBreak");
			Candle2->FrameChangeAni("CandleFireBreak");
			CandleCut2 = true;
			Candle1->FrameChangeAni("CandleFireBreak");
			Candle2->FrameChangeAni("CandleFireBreak");
			Candle3->FrameChangeAni("CandleFireBreak");
			Fire1 = false;
			Fire2 = false;
			Fire3 = false;
			return;
		}

		if (PlayerValue::GetValue()->GetGreenDeathValue() == 1 && CandleCut3 == false)
		{
			Candle1->CandleChangeAni("CandleStickBreak");
			Candle1->FrameChangeAni("CandleFireBreak");
			CandleCut3 = true;
			Candle1->FrameChangeAni("CandleFireBreak");
			Candle2->FrameChangeAni("CandleFireBreak");
			Candle3->FrameChangeAni("CandleFireBreak");
			Fire1 = false;
			Fire2 = false;
			Fire3 = false;
			return;
		}
	}

	if (HandApeear1 == false)
	{
		EventTime1 += _Delta;
	}
	if (HandApeear2 == false)
	{
		EventTime2 += _Delta;
	}
	if (HandApeear3 == false)
	{
		EventTime3 += _Delta;
	}

	if (EventTime1 >= EventCoolTime1)
	{
		Hand1->On();
		EventTime1 = 0.0f;
		HandApeear1 = true;
		Hand4->On();
		Hand7->On();
	}
	if (EventTime2 >= EventCoolTime2)
	{
		Hand2->On();
		EventTime2 = 0.0f;
		HandApeear2 = true;
		Hand5->On();
	}
	if (EventTime3 >= EventCoolTime3)
	{
		Hand3->On();
		EventTime3 = 0.0f;
		HandApeear3 = true;
		Hand6->On();
	}


}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("BossMap.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("BackGround");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("BossMap.png");
		GameEngineSprite::CreateSingle("BossDebugMap.png");
	}

	if (nullptr == Map)
	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("BossMap.png", "BossDebugMap.png");
	}

	if (nullptr == GameEngineSprite::Find("Adele_Character"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Adele_Character");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("Adele_Battle_Character"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Adele_Battle_Character");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		BossEntranceLevel* Level = dynamic_cast<BossEntranceLevel*>(_PrevLevel);
		PlayerObject->SetDebugMap("BossDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 900.0f, -500.0f });
	}
	if (nullptr == GameEngineSprite::Find("Skill"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Skill");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == PlayerSkill)
	{
		PlayerSkill = CreateActor<AdeleSkill>();
	}
	if (nullptr == Skill)
	{
		Skill = CreateActor<SkillManager>();
	}

	if (nullptr == GameEngineSprite::Find("Craving"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("Craving");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("GhostDamienMob"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("GhostDamienMob");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("BossJin"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("BossJinHilla");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("JinHillaUI"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaUI");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}
	
	// 보스
	if (nullptr == BossJin)
	{
		BossJin = CreateActor<JinHillaBoss>(ContentsObjectType::Monster);
		BossJin->Transform.SetWorldPosition({ 900.0f, -700.0f, static_cast<float>(DeepBufferType::Monster) });
		BossJin->SetDebugMap("BossDebugMap.Png");
		BossJin->CallRegen();
	}
	if (nullptr ==  BossJinSkill)
	{
		BossJinSkill = CreateActor<BossSkillManager>();
	}
	// 보스레벨 Ui
	if (nullptr == BossUi)
	{
		BossUi = CreateActor<BossLevelUi>(ContentsObjectType::UI);
	}

	if (nullptr == GameEngineSprite::Find("UITexture"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("UITexture");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("LWGaugeUI_background.Png"))
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
	}

	if (nullptr == UIObject)
	{
		UIObject = CreateActor<MainUIActor>(ContentsObjectType::UI);
		BossEntranceLevel* Level = dynamic_cast<BossEntranceLevel*>(_PrevLevel);
	}
	if (nullptr == MouseObject)
	{
		MouseObject = CreateActor<Mouse>(ContentsObjectType::UI);
	}


	/////////////// 패턴관련 ///////////////
	if (nullptr == BossTimer)
	{
		BossTimer = CreateActor<ContentsTimer>(ContentsObjectType::UI);
		BossTimer->SetTimeValue(1784.0f);
	}
	if (nullptr == SickleAni)
	{
		SickleAni = CreateActor<JinHillaSickleCut>(ContentsObjectType::JinHillaAnime);
	}
	if (nullptr == DeathUI)
	{
		DeathUI = CreateActor<PlayerDeathCountUI>(ContentsObjectType::UI);
	}
	if (nullptr == Altar)
	{
		Altar = CreateActor<AltarUi>(ContentsObjectType::BackSkill);
	}

	if (Candle1 == nullptr)
	{
		Candle1 = CreateActor<CandleUi>(ContentsObjectType::MonsterSkill);
		Candle1->Transform.SetWorldPosition({ 810.0f, -410.0f });

		Candle2 = CreateActor<CandleUi>(ContentsObjectType::MonsterSkill);
		Candle2->Transform.SetWorldPosition({ 900.0f, -437.0f });

		Candle3 = CreateActor<CandleUi>(ContentsObjectType::MonsterSkill);
		Candle3->Transform.SetWorldPosition({ 980.0f, -415.0f });
	}

	if (Hand1 == nullptr)
	{
		Hand1 = CreateActor<HandAttack>(ContentsObjectType::MonsterSkill);
		Hand1->Transform.SetLocalPosition({ 70.0f, -200.0f }); 
		Hand1->Off();
		Hand2 = CreateActor<HandAttack>(ContentsObjectType::MonsterSkill);
		Hand2->Transform.SetLocalPosition({ 360.0f, -200.0f });
		Hand2->Off();
		Hand3 = CreateActor<HandAttack>(ContentsObjectType::MonsterSkill); 
		Hand3->Transform.SetLocalPosition({ 650.0f, -200.0f });
		Hand3->Off();
		Hand4 = CreateActor<HandAttack>(ContentsObjectType::MonsterSkill);
		Hand4->Transform.SetLocalPosition({ 950.0f, -200.0f });
		Hand4->Off();
		Hand5 = CreateActor<HandAttack>(ContentsObjectType::MonsterSkill);
		Hand5->Transform.SetLocalPosition({ 1250.0f, -200.0f });
		Hand5->Off();
		Hand6 = CreateActor<HandAttack>(ContentsObjectType::MonsterSkill);
		Hand6->Transform.SetLocalPosition({ 1475.0f, -200.0f });
		Hand6->Off();
		Hand7 = CreateActor<HandAttack>(ContentsObjectType::MonsterSkill);
		Hand7->Transform.SetLocalPosition({ 1750.0f, -200.0f });
		Hand7->Off();
	}


	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition(HScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("BossMap.png"))
	{
		GameEngineSprite::Release("BossMap.png");
		GameEngineSprite::Release("BossDebugMap.png");
	}
	if (nullptr != GameEngineSprite::Find("BossJin"))
	{
		GameEngineSprite::Release("BossJin");
		GameEngineSprite::Release("JinHillaUI");
		GameEngineSprite::Release("Craving");
		GameEngineSprite::Release("GhostDamienMob");
	}
	if (nullptr != GameEngineSprite::Find("JinHillaAnime"))
	{
		GameEngineSprite::Release("JinHillaAnime");
	}

	if (nullptr != Map)
	{
		Map->Death();
		Map = nullptr;
	}

	if (nullptr != BossJin)
	{
		BossJin->Death();
		BossJin = nullptr;

		BossJinSkill->Death();
		BossJinSkill = nullptr;

	}

	if (nullptr != PlayerSkill)
	{
		PlayerSkill->Death();
		PlayerSkill = nullptr;
	}
	if (nullptr != Skill)
	{
		Skill->Death();
		Skill = nullptr;
	}
	if (nullptr != PlayerObject)
	{
		PlayerObject->Death();
		PlayerObject = nullptr;
	}
	if (nullptr != UIObject)
	{
		UIObject->Death();
		UIObject = nullptr;
	}
	if (nullptr != BossUi)
	{
		BossUi->Death();
		BossUi = nullptr;
	}
	if (nullptr != MouseObject)
	{
		MouseObject->Death();
		MouseObject = nullptr;
	}

	if (nullptr != BossTimer)
	{
		BossTimer->Death();
		BossTimer = nullptr;
	}
	if (nullptr != SickleAni)
	{
		SickleAni->Death();
		SickleAni = nullptr;
	}
	if (nullptr != DeathUI)
	{
		DeathUI->Death();
		DeathUI = nullptr;
	}
	if (nullptr != Altar)
	{
		Altar->Death();
		Altar = nullptr;
	}

	if (Candle1 != nullptr)
	{
		Candle1->Death();
		Candle1 = nullptr;

		Candle2->Death();
		Candle2 = nullptr;

		Candle3->Death();
		Candle3 = nullptr;
	}

	if (Hand1 != nullptr)
	{
		Hand1->Death();
		Hand1 = nullptr;
		Hand2->Death();
		Hand2 = nullptr;
		Hand3->Death();
		Hand3 = nullptr;
		Hand4->Death();
		Hand4 = nullptr;
		Hand5->Death();
		Hand5 = nullptr;
		Hand6->Death();
		Hand6 = nullptr;
		Hand7->Death();
		Hand7 = nullptr;
	}

}