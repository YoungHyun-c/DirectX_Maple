#include "PreCompile.h"
#include "PotalManager.h"
#include "Player.h"
#include "BackGroundMap.h"
#include "JinHillaEnterAnime.h"

PotalManager::PotalManager()
{

}

PotalManager::~PotalManager()
{

}



void PotalManager::Start()
{
	PotalCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Potal);
	PotalCol->Transform.SetLocalScale({ 80.0f, 100.0f });
}

void PotalManager::Update(float _Detla)
{
	if (LinkedMap == "PracticeLevel")
	{
		EventParameter PotalEvent;
		PotalEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
			{
				if (GameEngineInput::IsDown(VK_UP))
				{
					GameEngineCore::ChangeLevel("PracticeLevel");
				}
			};
		PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	}

	if (LinkedMap == "BossEntranceLevel")
	{
		EventParameter PotalEvent;
		PotalEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
			{
				if (GameEngineInput::IsDown(VK_UP))
				{
					GameEngineCore::ChangeLevel("BossEntranceLevel");
				}
			};
		PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	}

	if (LinkedMap == "BossLevel")
	{
		EventParameter PotalEvent;
		PotalEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
			{
				if (GameEngineInput::IsDown(VK_UP))
				{
					GameEngineCore::ChangeLevel("BossLevel");
				}
			};
		PotalCol->CollisionEvent(ContentsCollisionType::Player, PotalEvent);
	}

}