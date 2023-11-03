#include "PreCompile.h"
#include "PracticeLevel.h"
#include "BackGroundMap.h"
#include "BossEntranceLevel.h"

#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

#include "Monster.h"
#include "MainUIActor.h"
#include "Mouse.h"
#include "SummonUi.h"
#include "DamageRenderer.h"


PracticeLevel::PracticeLevel()
{

}

PracticeLevel::~PracticeLevel()
{

}

void PracticeLevel::Start()
{
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });

	GameEngineInput::AddInputObject(this);
}

void PracticeLevel::Update(float _Delta)
{
	//long long MonsterHp = Monster::Monsters->GetMonsterHp();
	//std::string CurMonsterHp = "MonsterHp : ";
	//CurMonsterHp += std::to_string(MonsterHp);
	//CurMonsterHp += "\n";
	//OutputDebugStringA(CurMonsterHp.c_str());


	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('2', this))
	{
		GameEngineCore::ChangeLevel("BossEntranceLevel");
	}


	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	
	if (false == Monster::Monsters->MonsterAppearValue())
	{
		MonsterObject->Transform.SetLocalPosition({ PlayerPos.X, -700.0f, 100.0f });
	}

}

void PracticeLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		if (nullptr == GameEngineSprite::Find("PracticeMap.png"))
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
			GameEngineSprite::CreateSingle("PracticeMap.png");
			GameEngineSprite::CreateSingle("PracticeDebugMap.png");
		}
	}

	if (nullptr == GameEngineSprite::Find("Mugong"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("Mugong");
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
		Map->Init("PracticeMap.png", "PracticeDebugMap.png");
	}
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		BossEntranceLevel* Level = dynamic_cast<BossEntranceLevel*>(_PrevLevel);
		PlayerObject->SetDebugMap("PracticeDebugMap.png");
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
	if (nullptr == MonsterObject)
	{
		MonsterObject = CreateActor<Monster>(ContentsObjectType::Monster);
		MonsterObject->Transform.SetLocalPosition({ 500.0f, -700.0f, static_cast<float>(DeepBufferType::Monster) });
	}

	if (nullptr == UIObject)
	{
		UIObject = CreateActor<MainUIActor>(ContentsObjectType::UI);
	}
	if (nullptr == MouseObject)
	{
		SummonObject = CreateActor<SummonUi>(ContentsObjectType::UI);
		MouseObject = CreateActor<Mouse>(ContentsObjectType::UI);
	}



	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("PracticeMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	
	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void PracticeLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("PracticeMap.png"))
	{
		GameEngineSprite::Release("PracticeMap.png");
		GameEngineSprite::Release("PracticeDebugMap.png");
	}
	if (nullptr != GameEngineSprite::Find("Mugong"))
	{
		GameEngineSprite::Release("Mugong");
	}
	if (nullptr != GameEngineSprite::Find("LWGaugeUI_background.png"))
	{
		GameEngineSprite::Release("LWGaugeUI_background.png");
		GameEngineSprite::Release("LWGaugeUI.gauge.png");
	}
	if (nullptr != GameEngineSprite::Find("Adele_Character"))
	{
		GameEngineSprite::Release("Adele_Character");
		GameEngineSprite::Release("Adele_Battle_Character");
		GameEngineSprite::Release("Skill");
		GameEngineSprite::Release("UITexture");
	}

	if (nullptr != MonsterObject)
	{
		MonsterObject->Death();
		MonsterObject = nullptr;
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
		SummonObject->Death();
		SummonObject = nullptr;
		MouseObject->Death();
		MouseObject = nullptr;
	}
}