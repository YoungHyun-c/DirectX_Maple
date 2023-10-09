#include "PreCompile.h"
#include "PracticeLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "Monster.h"
#include "MainUIActor.h"
#include "TileMap.h"
#include "AdeleSkill.h"
#include "DamageRenderer.h"

#include "Mouse.h"
#include "SummonUi.h"

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
		GameEngineSprite::CreateSingle("Mugong_stand.png");
	}

	//std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("PracticeMap.png");
	//GlobalValue::MapScale = Tex->GetScale();
	//float4 HScale = Tex->GetScale().Half();
	//HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("PracticeMap.png", "PracticeDebugMap.png");
	}

	{
		std::shared_ptr<Player> NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
		NewPlayer->SetDebugMap("PracticeDebugMap.png");
		NewPlayer->Transform.SetWorldPosition({ 500.0f, -500.0f });
	}

	{
		std::shared_ptr<MainUIActor> UIObject = CreateActor<MainUIActor>(ContentsObjectType::UI);
	}

	{
		std::shared_ptr<SummonUi> SummonObject = CreateActor<SummonUi>(ContentsObjectType::UI);

		MouseObject = CreateActor<Mouse>();
		MouseObject->SetCurMouse(MouseObject);
	}

	{
		MonsterObject = CreateActor<Monster>(ContentsObjectType::Monster);
		MonsterObject->Transform.SetLocalPosition({ 500.0f, -700.0f });
	}

	// 콜리전안에 몬스터 마릿수 확인 및 데미지 뜨도록 만들어야됨
	//{
	//	MonsterObject = CreateActor<Monster>(ContentsObjectType::Monster);
	//	MonsterObject->Transform.SetLocalPosition({ 600.0f, -700.0f });
	//}

	{
		std::shared_ptr<AdeleSkill> Skill = CreateActor<AdeleSkill>();
	}

	{
		std::shared_ptr<DamageRenderer> DamageRender = CreateActor<DamageRenderer>();
	}


	//{
	//	std::shared_ptr<TileMap> Object = CreateActor<TileMap>(ContentsObjectType::BackGround);

	//	size_t TileX = 300;
	//	size_t TileY = 300;

	//	Object->TileRenderer->CreateTileMap({ TileX, TileY, {32, 32}, "HoHoYee_AttackABC" });

	//	for (size_t y = 0; y < TileY; y++)
	//	{
	//		for (size_t x = 0; x < TileX; x++)
	//		{
	//			Object->TileRenderer->SetTileIndex({ y, x });
	//		}
	//	}

	//	TileMapObject = Object;
	//}
}

void PracticeLevel::Update(float _Delta)
{
	//std::string FPS = "FPS : ";
	//FPS += std::to_string(static_cast<int>(1.0f / _Delta));
	//FPS += "\n";
	//OutputDebugStringA(FPS.c_str());


	if (GameEngineInput::IsDown('B'))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("BossEntranceLevel");
	}


	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	
	if (false == Monster::Monsters->MonsterAppear)
	{
		MonsterObject->Transform.SetLocalPosition({ PlayerPos.X, PlayerPos.Y + 100.0f});
	}

}

void PracticeLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("PracticeMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}

void PracticeLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}