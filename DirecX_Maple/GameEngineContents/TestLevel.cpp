#include "PreCompile.h"
#include "TestLevel.h"

#include "Player.h"
#include "BackGroundMap.h"
#include "MonsterFunction.h"
#include "GhostDamien.h"
#include "CravingMonster.h"
#include "JinHillaBoss.h"

#include "SkillManager.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}


void TestLevel::Start()
{
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

	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("BossMap.png", "BossDebugMap.png");
	}

	{
		NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
		NewPlayer->SetDebugMap("BossDebugMap.png");
		NewPlayer->Transform.SetWorldPosition({ 900.0f, -500.0f });
	}
	{
		CreateActor<SkillManager>();
	}

	{
		GhostDamienMob = CreateActor<GhostDamien>(ContentsObjectType::Monster);
		GhostDamienMob->Transform.SetWorldPosition({ 500.0f, -650.0f, static_cast<float>(DeepBufferType::Monster) });
		GhostDamienMob->SetDebugMap("BossDebugMap.Png");
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
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition(HScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}