#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
	CreateActor<Player>();

	//CreateChild<GameEngineRenderer>(); �̷��� �ϸ� ���� �ʾƼ� ���
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}