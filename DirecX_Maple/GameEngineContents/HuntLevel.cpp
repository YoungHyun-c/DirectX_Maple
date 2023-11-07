#include "PreCompile.h"
#include "HuntLevel.h"
#include "BackGroundMap.h"
#include "CrossLoadLevel.h"


#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "MainUIActor.h"
#include "Mouse.h"

HuntLevel::HuntLevel()
{

}

HuntLevel::~HuntLevel()
{

}

void HuntLevel::Start()
{
	GameEngineInput::AddInputObject(this);
}

void HuntLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}
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