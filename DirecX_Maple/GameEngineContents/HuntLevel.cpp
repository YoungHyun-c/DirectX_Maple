#include "PreCompile.h"
#include "HuntLevel.h"
#include "BackGroundMap.h"
#include "CrossLoadLevel.h"


#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "MainUIActor.h"
#include "Mouse.h"

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

	//if (CraneMob == nullptr)
	{
		//CraneMob = CreateActor<CraneMonster>(ContentsObjectType::Monster);
		//CraneMob->Transform.SetWorldPosition({ 2550.0f, -1100.0f});
		//CraneMob->SetDebugMap("HuntDebugMap.Png");

		//CraneMob = CreateActor<CraneMonster>(ContentsObjectType::Monster);
		//CraneMob->Transform.SetWorldPosition({ 2500.0f, -1100.0f});
		//CraneMob->SetDebugMap("HuntDebugMap.Png");

		//CraneMob = CreateActor<CraneMonster>(ContentsObjectType::Monster);
		//CraneMob->Transform.SetWorldPosition({ 2300.0f, -900.0f});
		//CraneMob->SetDebugMap("HuntDebugMap.Png");
	}

	Zone1 = CreateActor<MonsterSpawnZone>();
	Zone1->SetColMap("HuntDebugMap.Png");
	Zone1->SetMonsterToZone(MonstersName::Crane, 5);
	Zone1->SetZonePosAndScale({ 2000, -1100.0f }, 500.0f);

	Zone2 = CreateActor<MonsterSpawnZone>();
	Zone2->SetColMap("HuntDebugMap.Png");
	Zone2->SetMonsterToZone(MonstersName::Crane, 5);
	Zone2->SetZonePosAndScale({ 1000, -1100.0f }, 500.0f);

	Zone3 = CreateActor<MonsterSpawnZone>();
	Zone3->SetColMap("HuntDebugMap.Png");
	Zone3->SetMonsterToZone(MonstersName::Crane, 3);
	Zone3->SetZonePosAndScale({ 2200, -900.0f }, 100.0f);


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
	if (nullptr != MouseObject)
	{
		MouseObject->Death();
		MouseObject = nullptr;
	}
}