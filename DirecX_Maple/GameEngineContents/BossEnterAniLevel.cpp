#include "PreCompile.h"
#include "BossEnterAniLevel.h"

#include "JinHillaEnterAnime.h"

BossEnterAniLevel::BossEnterAniLevel()
{

}

BossEnterAniLevel::~BossEnterAniLevel()
{

}


void BossEnterAniLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("JinHilla_Enter"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHilla_Enter");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	if (nullptr == EnterAni)
	{
		EnterAni = CreateActor<JinHillaEnterAnime>(ContentsObjectType::UI);
	}

}
void BossEnterAniLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("JinHilla_Enter"))
	{
		GameEngineSprite::Release("JinHilla_Enter");
	}

	if (nullptr != EnterAni)
	{
		EnterAni->Death();
		EnterAni = nullptr;
	}
}
