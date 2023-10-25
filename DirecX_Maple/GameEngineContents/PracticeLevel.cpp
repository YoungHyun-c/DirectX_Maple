#include "PreCompile.h"
#include "PracticeLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "Monster.h"
#include "MainUIActor.h"
#include "TileMap.h"
#include "AdeleSkill.h"
#include "DamageRenderer.h"
#include "SkillManager.h"

#include "Mouse.h"
#include "SummonUi.h"

PracticeLevel::PracticeLevel()
{

}

PracticeLevel::~PracticeLevel()
{

}

void PracticeLevel::Start()
{
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });

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
		GameEngineSprite::CreateSingle("Dark.png");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
		GameEngineSprite::CreateSingle("Mugong_stand.png");
	}

	{
		Map = CreateActor<BackGroundMap>(static_cast<int>(ContentsObjectType::BackGround), "Map");
		Map->Init("PracticeMap.png", "PracticeDebugMap.png");
	}

	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		PlayerObject->SetDebugMap("PracticeDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 500.0f, -500.0f, static_cast<float>(DeepBufferType::Player) });
	}

	{
		std::shared_ptr<MainUIActor> UIObject = CreateActor<MainUIActor>(ContentsObjectType::UI);
	}

	{
		std::shared_ptr<SummonUi> SummonObject = CreateActor<SummonUi>(ContentsObjectType::UI);
		MouseObject = CreateActor<Mouse>(ContentsObjectType::UI);
	}

	{
		MonsterObject = CreateActor<Monster>(ContentsObjectType::Monster);
		MonsterObject->Transform.SetLocalPosition({ 500.0f, -700.0f, static_cast<float>(DeepBufferType::Monster) });
	}

	{
		//std::shared_ptr<AdeleSkill> Skill = CreateActor<AdeleSkill>();
	}

	{
		CreateActor<SkillManager>();
	}

	{
		std::shared_ptr<DamageRenderer> DamageRender = CreateActor<DamageRenderer>();
	}

	GameEngineInput::AddInputObject(this);
}

void PracticeLevel::Update(float _Delta)
{
	//std::string FPS = "FPS : ";
	//FPS += std::to_string(static_cast<int>(1.0f / _Delta));
	//FPS += "\n";
	//OutputDebugStringA(FPS.c_str());

	long long MonsterHp = Monster::Monsters->GetMonsterHp();
	std::string CurMonsterHp = "MonsterHp : ";
	CurMonsterHp += std::to_string(MonsterHp);
	CurMonsterHp += "\n";
	OutputDebugStringA(CurMonsterHp.c_str());


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
		MonsterObject->Transform.SetLocalPosition({ PlayerPos.X, -750.0f, 100.0f });
	}
}

void PracticeLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("PracticeMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition(HScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	
	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void PracticeLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}