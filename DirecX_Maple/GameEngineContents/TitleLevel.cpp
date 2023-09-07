#include "PreCompile.h"
#include "TitleLevel.h"
#include "BackGround.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
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

	GameEngineSprite::CreateSingle("PracticeTest.png");

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("PracticeTest.png");
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;

	GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	//TitleRenderer->SetSprite("EntranceMap.png");

	{
		std::shared_ptr<BackGround> Object = CreateActor<BackGround>(ContentsObjectType::BackGround);
		Map = Object;
	}
}

void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
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