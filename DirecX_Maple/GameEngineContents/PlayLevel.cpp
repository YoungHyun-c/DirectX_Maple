#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"


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

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();

	// GetMainCamera()->SetParent(NewPlayer);
	//CreateActor<Player>();

	//CreateChild<GameEngineRenderer>(); 이렇게 하면 좋지 않아서 고민
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}