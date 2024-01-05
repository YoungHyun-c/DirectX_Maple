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
#include "BossChat.h"
#include "AchieveUI.h"

#include "GhostSwoo.h"

#include "AtereEffect.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}


void TestLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	{
		GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<AtereEffect>();
	}
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

	if (nullptr == GameEngineSprite::Find("GhostSwooMob"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("GhostSwooMob");
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

	if (Map == nullptr)
	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("BossMap.png", "BossDebugMap.png");
	}

	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		PlayerObject->Transform.SetWorldPosition({ 900.0f, -500.0f });
		PlayerObject->SetDebugMap("BossDebugMap.png");
	}

	std::shared_ptr<GhostSwoo> TestSwoo = CreateActor<GhostSwoo>(ContentsObjectType::Monster);
	TestSwoo->Transform.SetWorldPosition({ 900.0f, -650.0f });
	TestSwoo->SetDebugMap("BossDebugMap.Png");


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

	if (nullptr == GameEngineSound::FindSound("TheothersideofShangriLa.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\FolderTexture\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("TheothersideofShangriLa.mp3"));
	}
	MapBgm = GameEngineSound::SoundPlay("TheothersideofShangriLa.mp3", 3);


	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossDebugMap.png");
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
	if (GameEngineSound::FindSound("TheothersideofShangriLa.mp3"))
	{
		MapBgm.Stop();
	}
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