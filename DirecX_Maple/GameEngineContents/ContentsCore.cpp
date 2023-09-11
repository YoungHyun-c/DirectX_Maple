#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PlayLevel.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::Start()
{
	// 기본적으로 SpriteRenderer를 만들 때 넣어줄 샘플러를 지정한다.
	GameEngineSpriteRenderer::SetDefaultSampler("POINT");

	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("TitleLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}