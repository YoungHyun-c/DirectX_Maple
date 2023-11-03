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
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });
	GameEngineInput::AddInputObject(this);
}

void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('1', this))
	{
		GameEngineCore::ChangeLevel("2.PracticeLevel");
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("JinHillaTitle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaTitle");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("JinHillaAnime"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaAnime");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	{
		JinHillaAniMation = CreateActor<JinHillaAnime>(ContentsObjectType::BackGround);
	}
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("JinHillaTitle"))
	{
		GameEngineSprite::Release("JinHillaTitle");
	}

	if (nullptr != JinHillaAniMation)
	{
		JinHillaAniMation->Death();
		JinHillaAniMation = nullptr;
	}
}