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

	//CreateChild<GameEngineRenderer>(); 이렇게 하면 좋지 않아서 고민
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}