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
	GetMainCamera()->Transform.SetLocalPostion({ 0.0f, 0.0f, -500.0f });

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();

	// GetMainCamera()->SetParent(NewPlayer);
	//CreateActor<Player>();

	//CreateChild<GameEngineRenderer>(); 이렇게 하면 좋지 않아서 고민
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}