#include "PreCompile.h"
#include "BackGroundMap.h"
#include "TestLevel.h"


#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "MainUIActor.h"
#include "Mouse.h"
#include "SummonUi.h"

#include "ContentsTimer.h"
#include "JinHillaSickleCut.h"
#include "JinHillaBoss.h"
#include "BossLevelUi.h"
#include "PlayerDeathCountUI.h"
#include "CandleUi.h"
#include "AltarUi.h"
#include "HandAttack.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}


void TestLevel::Start()
{
	GameEngineInput::AddInputObject(this);
}

void TestLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	if (PlayerValue::GetValue()->GetRedDeathValue() >= 1 && Fire1 == false)
	{
		CandleTest1->FrameChangeAni("CandleFireAppear");
		CandleTest1->On();
		Fire1 = true;
	}

	if (PlayerValue::GetValue()->GetRedDeathValue() >= 2 && Fire2 == false)
	{
		CandleTest2->FrameChangeAni("CandleFireAppear");
		CandleTest2->On();
		Fire2 = true;
	}

	if (PlayerValue::GetValue()->GetRedDeathValue() >= 3 && Fire3 == false)
	{
		CandleTest3->FrameChangeAni("CandleFireAppear");
		CandleTest3->On();
		Fire3 = true;
	}

	if (Fire3 == true && AltarAppear == false && GlobalValue::GetNeedGlobalValue()->GetAltarValue() == false)
	{
		AltarTest = CreateActor<AltarUi>(ContentsObjectType::BackSkill);
		AltarAppear = true;
	}


	if (GlobalValue::GetNeedGlobalValue()->GetAltarValue() == true)
	{
		CandleTest1->FrameChangeAni("CandleFireBreak");
		CandleTest2->FrameChangeAni("CandleFireBreak");
		CandleTest3->FrameChangeAni("CandleFireBreak");
		Fire1 = false;
		Fire2 = false;
		Fire3 = false;
		AltarAppear = false;
	}

	if (GlobalValue::GetNeedGlobalValue()->GetSickleCutValue() == true)
	{
		if (Fire1 == true)
		{
			CandleTest1->CandleChangeAni("CandleStickBreak");
			CandleTest1->FrameChangeAni("CandleFireBreak");
		}

		if (Fire2 == true)
		{
			CandleTest2->CandleChangeAni("CandleStickBreak");
			CandleTest2->FrameChangeAni("CandleFireBreak");
		}

		if (Fire3 == true)
		{
			CandleTest3->CandleChangeAni("CandleStickBreak");
			CandleTest3->FrameChangeAni("CandleFireBreak");
		}
	}

}

void TestLevel::LevelStart(GameEngineLevel* _PrevLevel)
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
	//if (nullptr == GameEngineSprite::Find("Skill"))
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentsResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("FolderTexture");
	//	Dir.MoveChild("Skill");
	//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	//	for (size_t i = 0; i < Directorys.size(); i++)
	//	{
	//		GameEngineDirectory& Dir = Directorys[i];
	//		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	//	}
	//}

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

	if (Map == nullptr)
	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("BossMap.png", "BossDebugMap.png");
	}

	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		PlayerObject->SetDebugMap("BossDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 900.0f, -500.0f });
	}

	//if (nullptr == PlayerSkill)
	//{
	//	PlayerSkill = CreateActor<AdeleSkill>();
	//}
	//if (nullptr == Skill)
	//{
	//	Skill = CreateActor<SkillManager>();
	//}
	if (nullptr == UIObject)
	{
		UIObject = CreateActor<MainUIActor>(ContentsObjectType::UI);
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
	/*{
		std::shared_ptr<class BossLevelUi> BossUi = CreateActor<BossLevelUi>(ContentsObjectType::UI);
	}*/
	//if (nullptr == GameEngineSprite::Find("BossJin"))
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentsResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("FolderTexture");
	//	Dir.MoveChild("Monster");
	//	Dir.MoveChild("BossJin");
	//	Dir.MoveChild("BossJinHilla");
	//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	//	for (size_t i = 0; i < Directorys.size(); i++)
	//	{
	//		GameEngineDirectory& Dir = Directorys[i];
	//		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	//	}
	//}

	//if (nullptr == BossJin)
	//{
	//	BossJin = CreateActor<JinHillaBoss>(ContentsObjectType::Monster);
	//	BossJin->Transform.SetWorldPosition({ 900.0f, -700.0f, static_cast<float>(DeepBufferType::Monster) });
	//	BossJin->SetDebugMap("BossDebugMap.Png");
	//	BossJin->CallRegen();
	//}

	

	//if (nullptr == GameEngineSprite::Find("GhostDamienMob"))
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentsResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("FolderTexture");
	//	Dir.MoveChild("Monster");
	//	Dir.MoveChild("GhostDamienMob");
	//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	//	for (size_t i = 0; i < Directorys.size(); i++)
	//	{
	//		GameEngineDirectory& Dir = Directorys[i];
	//		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	//	}
	//}

	std::shared_ptr<ContentsTimer> Test = CreateActor<ContentsTimer>(ContentsObjectType::UI);
	Test->SetTimeValue(1785.0f);
	std::shared_ptr<JinHillaSickleCut> SickleAni = CreateActor<JinHillaSickleCut>(ContentsObjectType::JinHillaAnime);
	std::shared_ptr<PlayerDeathCountUI> DeathUI = CreateActor<PlayerDeathCountUI>(ContentsObjectType::UI);

	CandleTest1 = CreateActor<CandleUi>(ContentsObjectType::BackSkill);
	CandleTest1->Transform.SetWorldPosition({ 810.0f, -410.0f });

	CandleTest2 = CreateActor<CandleUi>(ContentsObjectType::BackSkill);
	CandleTest2->Transform.SetWorldPosition({ 900.0f, -437.0f });

	CandleTest3 = CreateActor<CandleUi>(ContentsObjectType::BackSkill);
	CandleTest3->Transform.SetWorldPosition({ 980.0f, -415.0f });

	std::shared_ptr<HandAttack> HandTest = CreateActor<HandAttack>(ContentsObjectType::MonsterSkill);
	HandTest->Transform.SetLocalPosition({ 900.0f, -200.0f });

	//AltarTest = CreateActor<AltarUi>(ContentsObjectType::BackSkill);


	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition(HScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void TestLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("BossMap.png"))
	{
		GameEngineSprite::Release("BossMap.png");
		GameEngineSprite::Release("BossDebugMap.png");
	}

	if (nullptr != Map)
	{
		Map->Death();
		Map = nullptr;
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
	if (nullptr != MouseObject)
	{
		MouseObject->Death();
		MouseObject = nullptr;
	}
}