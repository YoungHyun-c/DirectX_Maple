#include "PreCompile.h"
#include "PracticeLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "Monster.h"

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

		//GameEngineSprite::CreateSingle("JinHilla.png");
	}

	{
		std::shared_ptr<Player> NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
	}

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("PracticeMap.png");
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("PracticeMap.png", "PracticeDebugMap.png");
	}
}

void PracticeLevel::Update(float _Delta)
{
	std::string FPS = "FPS : ";
	FPS += std::to_string(static_cast<int>(1.0f / _Delta));
	FPS += "\n";
	OutputDebugStringA(FPS.c_str());

	static size_t X = 0;

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

	if (GameEngineInput::IsDown('B'))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("BossEntranceLevel");
	}
}

void PracticeLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PracticeLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}