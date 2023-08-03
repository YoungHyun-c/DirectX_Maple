#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	//CreateChild<GameEngineRenderer>();

	std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
	// Renderer->SetCameraOrder(0);
}

void Player::Update(float _Delta)
{
	int  a = 0;
}