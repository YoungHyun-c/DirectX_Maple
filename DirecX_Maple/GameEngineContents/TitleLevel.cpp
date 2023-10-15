#include "PreCompile.h"
#include "TitleLevel.h"
#include "BackGroundMap.h"
#include "JinHillaAnime.h"


TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
{

	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentsResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("BackGround");
	//	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	//	for (size_t i = 0; i < Files.size(); i++)
	//	{
	//		GameEngineFile& File = Files[i];
	//		GameEngineTexture::Load(File.GetStringPath());
	//	}

	//	GameEngineSprite::CreateSingle("BossMap.png");
	//}


	//std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	//float4 HScale = Tex->GetScale().Half();
	//HScale.Y *= -1.0f;

	//GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	//{
	//	std::shared_ptr<BackGroundMap> Object = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
	//	Map->Init("BossMap.png", "BossMap.png");
	//	Map = Object;
	//}

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });

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
	}

	//std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	//float4 HScale = Tex->GetScale().Half();
	//HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		//Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		//Map->Init("JinHillaN001.png", "JinHillaN001.png");
	}

	{
		std::shared_ptr<JinHillaAnime> NewMonster = CreateActor<JinHillaAnime>(ContentsObjectType::BackGround);
	}

	GameEngineInput::AddInputObject(this);
}

void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('1', this))
	{
		GameEngineCore::ChangeLevel("PracticeLevel");
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}