#include "PreCompile.h"
#include "BossLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "JinHillaAnime.h"


BossLevel::BossLevel()
{

}

BossLevel::~BossLevel()
{

}

void BossLevel::Start()
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

		GameEngineSprite::CreateSingle("BossMap.png");
		GameEngineSprite::CreateSingle("BossDebugMap.png");
	}

	//std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	//float4 HScale = Tex->GetScale().Half();
	//GlobalValue::MapScale = Tex->GetScale();
	//HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("BossMap.png", "BossDebugMap.png");
	}

	{
		std::shared_ptr<Player> NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
		NewPlayer->SetDebugMap("BossDebugMap.png");
	}

	// ÁøÈú¶ó ³´º£±â
	//{
	//	std::shared_ptr<JinHillaAnime> NewMonster = CreateActor<JinHillaAnime>(ContentsObjectType::BackGround);
	//}
}

void BossLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B'))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('4'))
	{
		GameEngineCore::ChangeLevel("BossRewardLevel");
	}
}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	float4 HScale = Tex->GetScale().Half();
	GlobalValue::MapScale = Tex->GetScale();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);;
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}