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

//#include <GameEngineCore/FadePostEffect.h>
//#include <GameEngineCore/GameEngineCoreWindow.h>
#include "AtereEffect.h"

TownLevel::TownLevel()
{

}

TownLevel::~TownLevel()
{

}

void TownLevel::Start() 
{
	GameEngineInput::AddInputObject(this);

	//// ����Ÿ�� �̿� �׽�Ʈ
	//std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	//if (nullptr != Window)
	//{
	//	Window->AddDebugRenderTarget(0, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	//}

	{
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
			GameEngineSprite::CreateSingle("LWGaugeUI.gaugeMask.png");
			GameEngineSprite::CreateSingle("LWGaugeBar.png");
		}
	}

	{
		GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<AtereEffect>();
	}
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
	GlobalValue::GetNeedGlobalValue()->SetBgm("Thelandofpeachblossoms.mp3", 3);

	if (nullptr == GameEngineSound::FindSound("AltarAppear.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\FolderTexture\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Use.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("2.mp3"));

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("AltarAppear.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("AltarSucceess.mp3"));

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Bind.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("OrderSound.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Blossom.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Divide1.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Divide2.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Divide3.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Divide4.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Divide5.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Divide6Special.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Geddering.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Infinite.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("MaestorEnd.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("MaeStroStart.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("OrderSound.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Restore.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Ruin.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Storm3.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Storm4.mp3"));

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("LevelUp.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("SolErdaMax.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("SolErdaParticleCreate.mp3"));

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("5thAdelesOathInfinite.mp3"));
	}

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

	// ����Ʈ ����Ʈ �׽�Ʈ
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