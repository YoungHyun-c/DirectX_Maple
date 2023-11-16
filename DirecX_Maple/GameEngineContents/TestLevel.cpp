#include "PreCompile.h"
#include "BackGroundMap.h"
#include "TestLevel.h"


#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "MainUIActor.h"
#include "Mouse.h"
#include "SummonUi.h"

#include "GhostDamien.h"


#include "MonsterFunction.h"
#include "CravingMonster.h"
#include "JinHillaBoss.h"

#include "ContentsTimer.h"
#include "JinHillaSickleCut.h"

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
	//if (nullptr == GameEngineSprite::Find("LWGaugeUI_background.Png"))
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentsResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("FolderTexture");
	//	Dir.MoveChild("UITexture");

	//	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	//	for (size_t i = 0; i < Files.size(); i++)
	//	{
	//		GameEngineFile& File = Files[i];
	//		GameEngineTexture::Load(File.GetStringPath());
	//	}
	//	GameEngineSprite::CreateSingle("LWGaugeUI_background.Png");
	//	GameEngineSprite::CreateSingle("LWGaugeUI.gauge.png");
	//}

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
	/*if (nullptr == MouseObject)
	{
		MouseObject = CreateActor<Mouse>(ContentsObjectType::UI);
	}*/

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

	if (nullptr == GhostDamienMob)
	{
		GhostDamienMob = CreateActor<GhostDamien>(ContentsObjectType::Monster);
		GhostDamienMob->Transform.SetWorldPosition({ 500.0f, -650.0f, static_cast<float>(DeepBufferType::Monster) });
		GhostDamienMob->SetDebugMap("BossDebugMap.Png");
	}

	/*std::shared_ptr<ContentsTimer> Test = CreateActor<ContentsTimer>(ContentsObjectType::UI);
	Test->SetTimeValue(1785.0f);

	std::shared_ptr<JinHillaSickleCut> SickleAni = CreateActor<JinHillaSickleCut>(ContentsObjectType::JinHillaAnime);*/

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