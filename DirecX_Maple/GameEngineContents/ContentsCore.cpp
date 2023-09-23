#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "TitleLevel.h"
#include "PracticeLevel.h"
#include "BossEntranceLevel.h"
#include "BossLevel.h"
#include "BossRewardLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::Start()
{
	// �⺻������ SpriteRenderer�� ���� �� �־��� ���÷��� �����Ѵ�.


	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PracticeLevel>("PracticeLevel");
	GameEngineCore::CreateLevel<BossEntranceLevel>("BossEntranceLevel");
	GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	GameEngineCore::CreateLevel<BossRewardLevel>("BossRewardLevel");

	GameEngineCore::ChangeLevel("PracticeLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}