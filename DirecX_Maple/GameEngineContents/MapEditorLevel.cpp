#include "PreCompile.h"
#include "MapEditorLevel.h"

MapEditorLevel::MapEditorLevel()
{

}

MapEditorLevel::~MapEditorLevel()
{

}

void MapEditorLevel::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

}

void MapEditorLevel::Update(float _Delta)
{

}

void MapEditorLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void MapEditorLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
