#include "PreCompile.h"
#include "PotalManager.h"
#include "Player.h"
#include "BackGroundMap.h"


PotalManager::PotalManager()
{

}

PotalManager::~PotalManager()
{

}



void PotalManager::Start()
{
	PotalSprite = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Potal);
	PotalSprite->CreateAnimation("Potal", "Potal");
	PotalSprite->AutoSpriteSizeOn();
	PotalSprite->ChangeAnimation("Potal");

	PotalCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Potal);
	PotalCol->Transform.SetLocalScale({ 80.0f, 100.0f });
	PotalCol->SetCollisionType(ColType::AABBBOX2D);
}

void PotalManager::Update(float _Detla)
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
		PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	}

	//if (LinkedMap == "3.CrossLoadLevel")
	//{
	//	EventParameter PotalEvent;
	//	PotalEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	//		{
	//			if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()))
	//			{
	//				GameEngineCore::ChangeLevel("3.CrossLoadLevel");
	//			}
	//		};
	//	PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	//}

	//if (LinkedMap == "2.PracticeLevel")
	//{
	//	EventParameter PotalEvent;
	//	PotalEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	//		{
	//			if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()))
	//			{
	//				GameEngineCore::ChangeLevel("2.PracticeLevel");
	//			}
	//		};
	//	PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	//}

	//if (LinkedMap == "3.BossEntranceLevel")
	//{
	//	EventParameter PotalEvent;
	//	PotalEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	//		{
	//			if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()))
	//			{
	//				GameEngineCore::ChangeLevel("3.BossEntranceLevel");
	//			}
	//		};
	//	PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	//}

	//if (LinkedMap == "4.BossEnterAniLevel")
	//{
	//	EventParameter PotalEvent;
	//	PotalEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	//		{
	//			if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()))
	//			{
	//				GameEngineCore::ChangeLevel("4.BossEnterAniLevel");
	//			}
	//		};
	//	PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	//}

	/*if (LinkedMap == "BossLevel")
	{
		EventParameter PotalEvent;
		PotalEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
			{
				if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()))
				{
					GameEngineCore::ChangeLevel("BossLevel");
				}
			};
		PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	}*/

}