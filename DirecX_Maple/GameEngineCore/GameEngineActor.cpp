#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
}

GameEngineLevel* GameEngineActor::GetLevel()
{
	// ���߿� ������ �ɰŶ�� �Ѱ�.

	return GetParent<GameEngineLevel>();
}