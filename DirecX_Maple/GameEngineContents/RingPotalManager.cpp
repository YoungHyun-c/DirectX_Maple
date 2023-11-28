#include "PreCompile.h"
#include "RingPotalManager.h"
#include "Player.h"
#include "BackGroundMap.h"

RingPotalManager::RingPotalManager()
{

}

RingPotalManager::~RingPotalManager()
{

}

void RingPotalManager::Start()
{
	RingPotalSprite = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Potal);
	RingPotalSprite->CreateAnimation("RingPotal", "RingPotal");
	RingPotalSprite->AutoSpriteSizeOn();
	RingPotalSprite->ChangeAnimation("RingPotal");

	RingPotalCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Potal);
	RingPotalCol->Transform.SetLocalScale({ 80.0f, 100.0f });
	RingPotalCol->SetCollisionType(ColType::AABBBOX2D);

	DarkRenderer = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::Mouse);
	DarkRenderer->SetSprite("Dark.Png");
	DarkRenderer->GetColorData().MulColor.A = 0;
	DarkRenderer->Transform.SetWorldPosition(0);
	DarkRenderer->Off();
}

void RingPotalManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	DarkRenderer->GetColorData().MulColor.A = 0;
}

void RingPotalManager::Update(float _Delta)
{
	if (LinkedMap == "")
	{
		SetPlayerLinkedPos();
		return;
	}

	if (LinkedMap == GetLinkedMap())
	{
		EventParameter PotalEvent;
		PotalEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* Col)
			{
				if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()))
				{
					//GameEngineCore::ChangeLevel(LinkedMap);
					ChangeLevel = true;
				}
			};
		RingPotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	}

	if (ChangeLevel == true)
	{
		DarkRenderer->Transform.SetWorldPosition(0);
		DarkRenderer->GetColorData().MulColor.A += _Delta * 0.5f;
		DarkRenderer->On();
	}
	if (DarkRenderer->GetColorData().MulColor.A >= 1)
	{
		GameEngineCore::ChangeLevel(LinkedMap);
		ChangeLevel = false;
	}
}


void RingPotalManager::SetPlayerLinkedPos()
{
	EventParameter RingPotalEvent;
	RingPotalEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()) == true)
			{
				Player::GetMainPlayer()->Transform.SetWorldPosition(LinkedPos);
			}
		};
	RingPotalCol->CollisionEvent(ContentsCollisionType::Player, RingPotalEvent);
	
	/*if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()) == true)
	{
		Player::GetMainPlayer()->Transform.SetWorldPosition(LinkedPos);
	}*/
}