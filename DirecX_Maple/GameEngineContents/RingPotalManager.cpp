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
