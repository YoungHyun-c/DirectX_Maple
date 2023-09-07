#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "PlayMap.h"
#include "Monster.h"

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Texture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
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

		GameEngineSprite::CreateSingle("EntranceMap.png");
		GameEngineSprite::CreateSingle("JinHilla.png");
	}
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("EntranceMap.png");

	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	
	GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		std::shared_ptr<Player> NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
	}

	{
		std::shared_ptr<PlayMap> Object = CreateActor<PlayMap>(ContentsObjectType::BackGround);
		Map = Object;
	}

	{
		GameEngineRandom NewRandom;
		for (size_t i = 0; i < 10; i++)
		{
			std::shared_ptr<Monster> Object = CreateActor<Monster>(ContentsObjectType::Monster);
			//Object->Transform.SetLocalPosition({ 0, 0 });
			Object->Transform.SetLocalPosition(NewRandom.RandomVectorBox2D(0, 1280, 0, -720));
		}

		std::shared_ptr<PlayMap> Object0 = CreateActor<PlayMap>(ContentsObjectType::Monster);
		std::shared_ptr<PlayMap> Object1 = CreateActor<PlayMap>(ContentsObjectType::Monster);
		std::shared_ptr<PlayMap> Object2 = CreateActor<PlayMap>(ContentsObjectType::Monster);
		std::shared_ptr<PlayMap> Object3 = CreateActor<PlayMap>(ContentsObjectType::Monster);
	}
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;

	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A'))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}
	if (GameEngineInput::IsPress('D'))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}
	if (GameEngineInput::IsPress('W'))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}
	if (GameEngineInput::IsPress('S'))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}