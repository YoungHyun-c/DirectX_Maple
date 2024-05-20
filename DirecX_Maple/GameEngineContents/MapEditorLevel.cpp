#include "PreCompile.h"
#include "MapEditorLevel.h"

// Monster
#include "CraneMonster.h"
#include "Monster.h"
#include "CravingMonster.h"
#include "GhostDamien.h"
#include "GhostSwoo.h"

// UI
#include "Mouse.h"


MapEditorLevel::MapEditorLevel()
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::Start()
{
	// 이미지 불러오기
	Resource();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		BackGroundActor = CreateActor<GameEngineActor>();
		BackGroundRenderer = BackGroundActor->CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
		BackGroundRenderer->SetSprite("HuntMap.png");

		BackDebugActor = CreateActor<GameEngineActor>();
		BackDebugRenderer = BackDebugActor->CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGround);
		BackDebugRenderer->SetSprite("HuntDebugMap.Png");

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("HuntMap.Png");
		GlobalValue::MapScale = Tex->GetScale();
		float4 HScale = Tex->GetScale().Half();
		HScale.Y *= -1.0f;

		HScale.Z = 10.0f;
		BackGroundRenderer->Transform.SetLocalPosition(HScale);
		BackDebugActor->Transform.SetLocalPosition(HScale);
	}

	MouseObject = CreateActor<Mouse>();
	GameEngineInput::AddInputObject(this);
}

void MapEditorLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		std::shared_ptr<CraneMonster> Object = CreateActor<CraneMonster>(ContentsObjectType::Monster);
		Object->SetDebugMap("HuntDebugMap.png");
		Object->Transform.SetLocalPosition(GetMainCamera()->GetWorldMousePos2D());
	}

	MoveCam(_Delta);

	if (GameEngineInput::IsDown('B', this))
	{
		SwitchMap();
	}
}

void MapEditorLevel::MoveCam(float _Delta)
{
	float MoveSpeed = 200;

	if (GameEngineInput::IsPress(VK_LSHIFT, this))
	{
		MoveSpeed *= 5.0f;
	}

	if (GameEngineInput::IsPress('A', this))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::LEFT * _Delta * MoveSpeed);
	}

	if (GameEngineInput::IsPress('D', this))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::RIGHT * _Delta * MoveSpeed);
	}

	if (GameEngineInput::IsPress('W', this))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::UP * _Delta * MoveSpeed);
	}

	if (GameEngineInput::IsPress('S', this))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::DOWN * _Delta * MoveSpeed);
	}

	if (GameEngineInput::IsPress('Q', this))
	{
		GetMainCamera()->AddZoomValue(_Delta);
	}
	if (GameEngineInput::IsPress('E', this))
	{
		GetMainCamera()->AddZoomValue(-_Delta);
	}
}

void MapEditorLevel::SwitchMap()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		BackGroundRenderer->On();
		BackDebugRenderer->Off();
	}
	else
	{
		BackGroundRenderer->Off();
		BackDebugRenderer->On();
	}
}

void MapEditorLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<CraneMonster> Crane = CreateActor<CraneMonster>(ContentsObjectType::Monster, "Crane");
	Crane->SetDebugMap("HuntDebugMap.png");
	Crane->Transform.SetWorldPosition(float4(300.0f, -500.0f));
	
	std::shared_ptr<CravingMonster> Craving = CreateActor<CravingMonster>(ContentsObjectType::Monster, "Craving");
	Craving->SetDebugMap("HuntDebugMap.png");
	Craving->Transform.SetWorldPosition(float4(700.0f, -800.0f));
	Craving->CallRegen();

	std::shared_ptr<GhostDamien> Damien = CreateActor<GhostDamien>(ContentsObjectType::Monster, "Damien");
	Damien->SetDebugMap("HuntDebugMap.png");
	Damien->Transform.SetWorldPosition(float4(800.0f, -800.0f));
	Damien->CallRegen();

	std::shared_ptr<GhostSwoo> Swoo = CreateActor<GhostSwoo>(ContentsObjectType::Monster, "Swoo");
	Swoo->SetDebugMap("HuntDebugMap.png");
	Swoo->Transform.SetWorldPosition(float4(900.0f, -800.0f));
	Swoo->CallRegen();
}
void MapEditorLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}


void MapEditorLevel::Resource()
{
	if (nullptr == GameEngineSprite::Find("Monster"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\FolderTexture\\Monster");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (GameEngineDirectory& pDirectory : Directorys)
		{
			GameEngineSprite::CreateFolder(pDirectory.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("HuntMap.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\BackGround");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineTexture::Load(pFiles.GetStringPath());
			GameEngineSprite::CreateSingle(pFiles.GetFileName());
		}
	}
}