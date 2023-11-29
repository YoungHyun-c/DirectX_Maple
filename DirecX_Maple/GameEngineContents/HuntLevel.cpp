#include "PreCompile.h"
#include "HuntLevel.h"
#include "BackGroundMap.h"
#include "CrossLoadLevel.h"


#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "MainUIActor.h"
#include "SolErdaGauge.h"
#include "Mouse.h"
#include "QuestIcon.h"
#include "SolErdaGauge.h"

#include "CraneMonster.h"
#include "MonsterSpawnZone.h"

HuntLevel::HuntLevel()
{

}

HuntLevel::~HuntLevel()
{

}

void HuntLevel::Start()
{
	//Zone1 = CreateActor<MonsterSpawnZone>();
	//Zone1->SetColMap("HuntDebugMap.Png");
	//Zone1->SetMonsterToZone(MonstersName::Crane, 5);
	//Zone1->SetMonsterToZone(MonstersName::Crane, 2);
	//Zone1->SetZonePosAndScale({ 2500, -1100.0f }, 500.0f);

	//Zone2 = CreateActor<MonsterSpawnZone>();
	//Zone2->SetColMap("HuntDebugMap.Png");
	//Zone2->SetMonsterToZone(MonstersName::Crane, 5);
	//Zone2->SetMonsterToZone(MonstersName::Crane, 3);
	//Zone2->SetZonePosAndScale({ 1700, -1100.0f }, 1000.0f);

	GameEngineInput::AddInputObject(this);
}

void HuntLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	//RegenTime += _Delta;
	//if (RegenTime > RegenCoolTime)
	//{
	//	CraneMob = CreateActor<CraneMonster>(ContentsObjectType::Monster);
	//	CraneMob->Transform.SetWorldPosition({ 2550.0f, -1100.0f });
	//	CraneMob->SetDebugMap("HuntDebugMap.Png");

	//	CraneMob = CreateActor<CraneMonster>(ContentsObjectType::Monster);
	//	CraneMob->Transform.SetWorldPosition({ 2500.0f, -1100.0f });
	//	CraneMob->SetDebugMap("HuntDebugMap.Png");

	//	CraneMob = CreateActor<CraneMonster>(ContentsObjectType::Monster);
	//	CraneMob->Transform.SetWorldPosition({ 2300.0f, -900.0f });
	//	CraneMob->SetDebugMap("HuntDebugMap.Png");

	//	RegenTime = 0.0f;
	//}

	//Count = GlobalValue::GetMonsterValue()->GetCurMonsterValue();
	//std::string MobCount = "잡은 수 : ";
	//MobCount += std::to_string(Count);
	//MobCount += "\n";
	//OutputDebugStringA(MobCount.c_str());

	//Count = (GlobalValue::GetDropValue()->GetDropItemValue() / 2);
	//std::string ItemCount = "드랍 수 : ";
	//ItemCount += std::to_string(Count);
	//ItemCount += "\n";
	//OutputDebugStringA(ItemCount.c_str());

}

void HuntLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("HuntMap.png"))
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
		GameEngineSprite::CreateSingle("HuntMap.png");
		GameEngineSprite::CreateSingle("HuntDebugMap.png");
	}
	if (nullptr == GameEngineSprite::Find("Potal"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("PotalFolder");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
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
		GameEngineSprite::CreateSingle("ExpBar.Png");
		GameEngineSprite::CreateSingle("ExpMax.Png");
		GameEngineSprite::CreateSingle("ErdaGauge.Png");
		GameEngineSprite::CreateSingle("SolErdagauge.Png");
		GameEngineSprite::CreateSingle("SolErdagaugeMax.Png");
	}

	if (nullptr == GameEngineSprite::Find("Crane"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("Crane");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("SolEldaPieceIcon.Png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("MonsterReward");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("SolEldaPieceIcon.png");
		GameEngineSprite::CreateSingle("SolEldaIcon.png");
	}

	if (nullptr == GameEngineSound::FindSound("TheothersideofShangriLa.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\FolderTexture\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("TheothersideofShangriLa.mp3"));
	}
	GlobalValue::GetNeedGlobalValue()->CurBgmStop();
	GlobalValue::GetNeedGlobalValue()->SetBgm("TheothersideofShangriLa.mp3", 3);
	
	if (Zone1 == nullptr)
	{
		Zone1 = CreateActor<MonsterSpawnZone>();
		Zone1->SetColMap("HuntDebugMap.Png");
		Zone1->SetMonsterToZone(MonstersName::Crane, 4);
		Zone1->SetZonePosAndScale({ 565.0f, -350.0f }, 250.0f);

		Zone2 = CreateActor<MonsterSpawnZone>();
		Zone2->SetColMap("HuntDebugMap.Png");
		Zone2->SetMonsterToZone(MonstersName::Crane, 2);
		Zone2->SetZonePosAndScale({ 400.0f, -590.0f }, 150.0f);

		Zone3 = CreateActor<MonsterSpawnZone>();
		Zone3->SetColMap("HuntDebugMap.Png");
		Zone3->SetMonsterToZone(MonstersName::Crane, 1);
		Zone3->SetZonePosAndScale({ 820.0f, -710.0f }, 50.0f);

		Zone4 = CreateActor<MonsterSpawnZone>();
		Zone4->SetColMap("HuntDebugMap.Png");
		Zone4->SetMonsterToZone(MonstersName::Crane, 3);
		Zone4->SetZonePosAndScale({ 525.0f, -900.0f }, 250.0f);

		Zone5 = CreateActor<MonsterSpawnZone>();
		Zone5->SetColMap("HuntDebugMap.Png");
		Zone5->SetMonsterToZone(MonstersName::Crane, 4);
		Zone5->SetZonePosAndScale({ 540.0f, -1100.0f }, 300.0f);

		Zone6 = CreateActor<MonsterSpawnZone>();
		Zone6->SetColMap("HuntDebugMap.Png");
		Zone6->SetMonsterToZone(MonstersName::Crane, 2);
		Zone6->SetZonePosAndScale({ 1300.0f, -610.0f }, 100.0f);

		Zone7 = CreateActor<MonsterSpawnZone>();
		Zone7->SetColMap("HuntDebugMap.Png");
		Zone7->SetMonsterToZone(MonstersName::Crane, 4);
		Zone7->SetZonePosAndScale({ 1350.0f, -900.0f }, 150.0f);

		Zone8 = CreateActor<MonsterSpawnZone>();
		Zone8->SetColMap("HuntDebugMap.Png");
		Zone8->SetMonsterToZone(MonstersName::Crane, 4);
		Zone8->SetZonePosAndScale({ 1400.0f, -1100.0f }, 300.0f);

		Zone9 = CreateActor<MonsterSpawnZone>();
		Zone9->SetColMap("HuntDebugMap.Png");
		Zone9->SetMonsterToZone(MonstersName::Crane, 1);
		Zone9->SetZonePosAndScale({ 1900.0f, -470.0f }, 40.0f);

		Zone10 = CreateActor<MonsterSpawnZone>();
		Zone10->SetColMap("HuntDebugMap.Png");
		Zone10->SetMonsterToZone(MonstersName::Crane, 1);
		Zone10->SetZonePosAndScale({ 1725.0f, -610.0f }, 100.0f);

		Zone11 = CreateActor<MonsterSpawnZone>();
		Zone11->SetColMap("HuntDebugMap.Png");
		Zone11->SetMonsterToZone(MonstersName::Crane, 2);
		Zone11->SetZonePosAndScale({ 2100.0f, -690.0f }, 100.0f);

		Zone12 = CreateActor<MonsterSpawnZone>();
		Zone12->SetColMap("HuntDebugMap.Png");
		Zone12->SetMonsterToZone(MonstersName::Crane, 3);
		Zone12->SetZonePosAndScale({ 2200.0f, -900.0f }, 100.0f);

		Zone13 = CreateActor<MonsterSpawnZone>();
		Zone13->SetColMap("HuntDebugMap.Png");
		Zone13->SetMonsterToZone(MonstersName::Crane, 3);
		Zone13->SetZonePosAndScale({ 2250.0f, -1100.0f }, 300.0f);

		Zone14 = CreateActor<MonsterSpawnZone>();
		Zone14->SetColMap("HuntDebugMap.Png");
		Zone14->SetMonsterToZone(MonstersName::Crane, 3);
		Zone14->SetZonePosAndScale({ 2525.0f, -390.0f }, 250.0f);

		Zone15 = CreateActor<MonsterSpawnZone>();
		Zone15->SetColMap("HuntDebugMap.Png");
		Zone15->SetMonsterToZone(MonstersName::Crane, 1);
		Zone15->SetZonePosAndScale({ 2535.0f, -610.0f }, 150.0f);

		Zone16 = CreateActor<MonsterSpawnZone>();
		Zone16->SetColMap("HuntDebugMap.Png");
		Zone16->SetMonsterToZone(MonstersName::Crane, 1);
		Zone16->SetZonePosAndScale({ 2730.0f, -900.0f }, 100.0f);
	}

	if (Map == nullptr)
	{
		Map = CreateActor<BackGroundMap>(static_cast<int>(ContentsObjectType::BackGround), "Map");
		Map->Init("HuntMap.png", "HuntDebugMap.png");
	}
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		PlayerObject->SetDebugMap("HuntDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 2780.0f, -1000.0f, static_cast<float>(DeepBufferType::Player) });
	}
	if (nullptr == PlayerSkill)
	{
		PlayerSkill = CreateActor<AdeleSkill>();
	}
	if (nullptr == Skill)
	{
		Skill = CreateActor<SkillManager>();
	}


	if (nullptr == UIObject)
	{
		UIObject = CreateActor<MainUIActor>(ContentsObjectType::UI);
	}
	if (nullptr == MouseObject)
	{
		MouseObject = CreateActor<Mouse>(ContentsObjectType::UI);
	}
	if (nullptr == QuestObject)
	{
		QuestObject = CreateActor<QuestIcon>(ContentsObjectType::NPC);
	}
	if (nullptr == SolObject)
	{
		SolObject = CreateActor<SolErdaGauge>(ContentsObjectType::UI);
	}

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("HuntDebugMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition(HScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void HuntLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("HuntMap.png"))
	{
		GameEngineSprite::Release("HuntMap.png");
		GameEngineSprite::Release("HuntDebugMap.png");
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
	//if (nullptr != PlayerObject)
	//{
	//	PlayerObject->Death();
	//	PlayerObject = nullptr;
	//}
	if (nullptr != UIObject)
	{
		UIObject->Death();
		UIObject = nullptr;
	}
	/*if (nullptr != SolObject)
	{
		SolObject->Death();
		SolObject = nullptr;
	}*/
	if (nullptr != MouseObject)
	{
		MouseObject->Death();
		MouseObject = nullptr;
	}

	if (nullptr != Zone1)
	{
		Zone1->Death();
		Zone1 = nullptr;
		Zone2->Death();
		Zone2 = nullptr;
		Zone3->Death();
		Zone3 = nullptr;
		Zone4->Death();
		Zone4 = nullptr;
		Zone5->Death();
		Zone5 = nullptr;
		Zone6->Death();
		Zone6 = nullptr;
		Zone7->Death();
		Zone7 = nullptr;
		Zone8->Death();
		Zone8 = nullptr;
		Zone9->Death();
		Zone9 = nullptr;
		Zone10->Death();
		Zone10= nullptr;
		Zone11->Death();
		Zone11 = nullptr;
		Zone12->Death();
		Zone12 = nullptr;
		Zone13->Death();
		Zone13 = nullptr;
		Zone14->Death();
		Zone14 = nullptr;
		Zone15->Death();
		Zone15 = nullptr;
		Zone16->Death();
		Zone16 = nullptr;
	}
}