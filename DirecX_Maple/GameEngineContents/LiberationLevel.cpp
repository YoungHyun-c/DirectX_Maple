#include "PreCompile.h"
#include "LiberationLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "MainUIActor.h"
#include "Mouse.h"

#include "AtereEffect.h"

LiberationLevel::LiberationLevel()
{

}

LiberationLevel::~LiberationLevel()
{

}

void LiberationLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	{
		GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<AtereEffect>();
	}
}

void LiberationLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}
}

void LiberationLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("LiberationMap.png"))
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
		GameEngineSprite::CreateSingle("LiberationMap.png");
		GameEngineSprite::CreateSingle("LiberationDebugMap.png");
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
	}
	if (nullptr == GameEngineSound::FindSound("Pain And Sorrow.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\FolderTexture\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Pain And Sorrow.mp3"));
	}
	GlobalValue::GetNeedGlobalValue()->CurBgmStop();
	GlobalValue::GetNeedGlobalValue()->SetBgm("Pain And Sorrow.mp3", 2);


	if (Map == nullptr)
	{
		Map = CreateActor<BackGroundMap>(static_cast<int>(ContentsObjectType::BackGround), "Map");
		Map->Init("LiberationMap.png", "LiberationDebugMap.png");
	}
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		PlayerObject->SetDebugMap("LiberationDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 1080.0f, -820.0f, static_cast<float>(DeepBufferType::Player) });
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


	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("LiberationMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void LiberationLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("LiberationMap.png"))
	{
		GameEngineSprite::Release("LiberationMap.png");
		GameEngineSprite::Release("LiberationDebugMap.png");
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