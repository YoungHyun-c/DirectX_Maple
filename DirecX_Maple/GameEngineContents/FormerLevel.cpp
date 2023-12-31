#include "PreCompile.h"
#include "FormerLevel.h"
#include "BackGroundMap.h"
#include "HuntLevel.h"

#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "MainUIActor.h"
#include "SolErdaGauge.h"
#include "Mouse.h"

#include "GrandisGoddess.h"
#include "AtereEffect.h"

FormerLevel::FormerLevel()
{

}

FormerLevel::~FormerLevel()
{

}

void FormerLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	{
		GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<AtereEffect>();
	}
}

void FormerLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}
}

void FormerLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("6thMap.png"))
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
		GameEngineSprite::CreateSingle("6thMap.png");
		GameEngineSprite::CreateSingle("6thDebugMap.png");
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
	if (nullptr == GameEngineSprite::Find("Npc"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Npc");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("ChatBack.Png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Npc");
		Dir.MoveChild("Chat");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("ChatBack.Png");
		GameEngineSprite::CreateSingle("ChatBackBig.Png");
		GameEngineSprite::CreateSingle("Accept.Png");
		GameEngineSprite::CreateSingle("OK.Png");
		GameEngineSprite::CreateSingle("NameTag.Png");
		GameEngineSprite::CreateSingle("FormerNpc0.Png");
		GameEngineSprite::CreateSingle("FormerNpc1.Png");
		GameEngineSprite::CreateSingle("FormerNpc2.Png");
		GameEngineSprite::CreateSingle("FormerNpc3.Png");
	}

	if (nullptr == GameEngineSound::FindSound("Tangled Nebula.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\FolderTexture\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Tangled Nebula.mp3"));
	}
	GlobalValue::GetNeedGlobalValue()->CurBgmStop();
	GlobalValue::GetNeedGlobalValue()->SetBgm("Tangled Nebula.mp3", 3);


	if (Map == nullptr)
	{
		Map = CreateActor<BackGroundMap>(static_cast<int>(ContentsObjectType::BackGround), "Map");
		Map->Init("6thMap.png", "6thDebugMap.png");
	}
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		PlayerObject->SetDebugMap("6thDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 650.0f, -850.0f, static_cast<float>(DeepBufferType::Player) });
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
	if (nullptr == SolObject)
	{
		SolObject = CreateActor<SolErdaGauge>(ContentsObjectType::UI);
	}
	if (nullptr == FormerNpc)
	{
		FormerNpc = CreateActor<GrandisGoddess>(ContentsObjectType::UI);
		FormerNpc->Transform.SetWorldPosition({ 1275.0f, -535.0f });
	}


	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("6thMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void FormerLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("6thMap.png"))
	{
		GameEngineSprite::Release("6thMap.png");
		GameEngineSprite::Release("6thDebugMap.png");
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
	if (nullptr != FormerNpc)
	{
		FormerNpc->Death();
		FormerNpc = nullptr;
	}
}