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

	DarkRenderer = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::Mouse);
	DarkRenderer->SetSprite("Dark.Png");
	DarkRenderer->GetColorData().MulColor.A = 0;
	DarkRenderer->Transform.SetWorldPosition(0);
	DarkRenderer->Off();
}

void PotalManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	DarkRenderer->GetColorData().MulColor.A = 0;
}

void PotalManager::Update(float _Delta)
{
	if (LinkedMap == GetLinkedMap())
	{
		EventParameter PotalEvent;
		PotalEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* Col)
			{
				if (GameEngineInput::IsDown(VK_UP, Player::GetMainPlayer()))
				{
					ChangeLevel = true;
				}
			};
		PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
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