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
	//{
	//	GameEngineRandom NewRandom;
	//	for (size_t i = 0; i < 10; i++)
	//	{
	//		std::shared_ptr<Monster> Object = CreateActor<Monster>(ContentsObjectType::Monster);
	//		//Object->Transform.SetLocalPosition({ 0, 0 });
	//		Object->Transform.SetLocalPosition(NewRandom.RandomVectorBox2D(0, 1280, 0, -720));
	//	}

	//	std::shared_ptr<PlayMap> Object0 = CreateActor<PlayMap>(ContentsObjectType::Monster);
	//	std::shared_ptr<PlayMap> Object1 = CreateActor<PlayMap>(ContentsObjectType::Monster);
	//	std::shared_ptr<PlayMap> Object2 = CreateActor<PlayMap>(ContentsObjectType::Monster);
	//	std::shared_ptr<PlayMap> Object3 = CreateActor<PlayMap>(ContentsObjectType::Monster);
	//}
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

	//std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("RewardMap.png");
	//float4 HScale = Tex->GetScale().Half();
	//GlobalValue::MapScale = Tex->GetScale();
	//HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("RewardMap.png", "RewardDebugMap.png");
	}

	{
		std::shared_ptr<Player> NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
		NewPlayer->SetDebugMap("RewardDebugMap.png");
		NewPlayer->Transform.SetWorldPosition({ 250.0f, -600.0f });
	}
}

void BossRewardLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B'))
	{
		Map->SwitchRenderer();
	}
}

void BossRewardLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("RewardMap.png");
	float4 HScale = Tex->GetScale().Half();
	GlobalValue::MapScale = Tex->GetScale();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}

void BossRewardLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}