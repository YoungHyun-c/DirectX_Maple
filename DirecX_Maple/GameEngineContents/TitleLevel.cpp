#include "PreCompile.h"
#include "TitleLevel.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
}

void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}