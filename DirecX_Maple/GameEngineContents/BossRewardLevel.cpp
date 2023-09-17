#include "PreCompile.h"
#include "BossRewardLevel.h"
#include "BackGroundMap.h"

#include "Player.h"

BossRewardLevel::BossRewardLevel()
{

}

BossRewardLevel::~BossRewardLevel()
{

}

void BossRewardLevel::Start()
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

		GameEngineSprite::CreateSingle("RewardMap.png");
		GameEngineSprite::CreateSingle("RewardDebugMap.png");
	}

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("RewardMap.png");
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("RewardMap.png", "RewardDebugMap.png");
	}

	{
		std::shared_ptr<Player> NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
	}
}

void BossRewardLevel::Update(float _Delta)
{

}

void BossRewardLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void BossRewardLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}