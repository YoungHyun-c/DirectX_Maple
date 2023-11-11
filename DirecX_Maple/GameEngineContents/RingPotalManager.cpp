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
}

void RingPotalManager::Update(float _Delta)
{
	SetPlayerLinkedPos();

	if (LinkedMap == "")
	{
		return;
	}

	if (LinkedMap == GetLinkedMap())
	{
		EventParameter PotalEvent;
		PotalEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* Col)
			{
				if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()))
				{
					GameEngineCore::ChangeLevel(LinkedMap);
				}
			};
		RingPotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
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