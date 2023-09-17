#include "PreCompile.h"
#include "BossEntranceLevel.h"
#include "BackGroundMap.h"

#include "Player.h"

BossEntranceLevel::BossEntranceLevel()
{

}

BossEntranceLevel::~BossEntranceLevel()
{

}

void BossEntranceLevel::Start()
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

		GameEngineSprite::CreateSingle("EntranceMap.png");
		GameEngineSprite::CreateSingle("EntranceDebugMap.png");
	}

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("EntranceMap.png");
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("EntranceMap.png", "EntranceDebugMap.png");
	}

	{
		std::shared_ptr<Player> NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
	}
}

void BossEntranceLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B'))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('3'))
	{
		GameEngineCore::ChangeLevel("BossLevel");
	}
}

void BossEntranceLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void BossEntranceLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
