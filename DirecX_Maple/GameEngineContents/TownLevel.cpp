#include "PreCompile.h"
#include "TownLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "MainUIActor.h"
#include "Mouse.h"
#include "QuestIcon.h"
#include "SolErdaGauge.h"

//#include <GameEngineCore/GameEngineCoreWindow.h>
//#include <GameEngineCore/FadePostEffect.h>
//#include "PlayerEffect.h"

TownLevel::TownLevel()
{

}

TownLevel::~TownLevel()
{

}

void TownLevel::Start() 
{
	GameEngineInput::AddInputObject(this);

	// 렌더타겟 이용 테스트
	//std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	//if (nullptr != Window)
	//{
	//	Window->AddDebugRenderTarget(0, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	//}

	//{
	//	std::shared_ptr<GameEngineActor> NewTest = CreateActor<GameEngineActor>(3, "Test");
	//	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//	NewTest->Transform.SetLocalPosition({ HalfWindowScale.X, -900.0f, -100.0f });
	//	std::shared_ptr<GameEngineRenderer> NewRender = NewTest->CreateComponent<GameEngineSpriteRenderer>(5);
	//	NewRender->SetRenderOrder(5);
	//	NewRender->RenderBaseInfoValue.Target2 = 1;
	//}

	//{
	//	GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<PlayerEffect>();
	//}
}
void TownLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}
}


void TownLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("TownMap.png"))
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
		GameEngineSprite::CreateSingle("TownMap.png");
		GameEngineSprite::CreateSingle("TownDebugMap.png");
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
	//	GameEngineSprite::CreateSingle("ExpBar.Png");
	//	GameEngineSprite::CreateSingle("ExpMax.Png");
	//	GameEngineSprite::CreateSingle("ErdaGauge.Png");
	//	GameEngineSprite::CreateSingle("SolErdagauge.Png");
	//	GameEngineSprite::CreateSingle("SolErdagaugeMax.Png");
	//}
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

	if (nullptr == GameEngineSound::FindSound("Thelandofpeachblossoms.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\FolderTexture\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Thelandofpeachblossoms.mp3"));
	}
	GlobalValue::GetNeedGlobalValue()->CurBgmStop();
	GlobalValue::GetNeedGlobalValue()->SetBgm("Thelandofpeachblossoms.mp3", 2);


	if (Map == nullptr)
	{
		BackMap = CreateActor<BackGroundMap>(static_cast<int>(ContentsObjectType::BackGround), "Map");
		BackMap->Init("BackMap.png", "TownDebugMap.png");
		
		Map = CreateActor<BackGroundMap>(static_cast<int>(ContentsObjectType::BackGround), "Map");
		Map->Init("TownMap.png", "TownDebugMap.png");
	}
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		PlayerObject->SetDebugMap("TownDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 500.0f, -500.0f, static_cast<float>(DeepBufferType::Player) });
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

	// 포스트 이펙트 테스트
	//FadeEffect = GetLevelRenderTarget()->CreateEffect<FadePostEffect>();

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("TownMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 550.0f;
	BackMap->Transform.SetLocalPosition(HScale);
	BackMap->Transform.SetLocalScale({ 2.0f, 1.8f });

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}


void TownLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("TownMap.png"))
	{
		GameEngineSprite::Release("TownMap.png");
		GameEngineSprite::Release("BackMap.png");
		GameEngineSprite::Release("TownDebugMap.png");
	}

	if (nullptr != Map)
	{
		BackMap->Death();
		BackMap = nullptr;
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