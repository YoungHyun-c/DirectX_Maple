#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BackGroundMap.h"
#include "Monster.h"
#include "ContentsEnum.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Player);
		MainSpriteRenderer->CreateAnimation("Attack2", "Battle_Alert", 0.1f, -1, -1, true);

		MainSpriteRenderer->CreateAnimation("Alert", "Alert", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Attack", "Attack", 0.3f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("Impale", "Impale", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Dead", "Dead", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Fly", "Fly", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Jump", "Jump", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Prone", "Prone", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("ProneAttack", "ProneAttack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Rope", "Rope", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Stand", "Stand", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Walk", "Walk", 0.1f, -1, -1, true);
		MainSpriteRenderer->SetSamplerState(SamplerOption::POINT);

		//MainSpriteRenderer->CreateAnimation("Attack", "blosom.frames", 0.1f, 0, 14, false);
		//MainSpriteRenderer->CreateAnimation("Attack", "blosom.frames", 0.1f, 0, 39, true);
		//MainSpriteRenderer->CreateAnimation("Run", "9833020.img.skill1.frames"); 
		MainSpriteRenderer->ChangeAnimation("Stand");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetPivotType(PivotType::Bottom);
		
		//MainSpriteRenderer->SetSprite("HoHoYee_AttackABC2");
		//MainSpriteRenderer->SetImageScale({ 91.0f, 80.0f });
		//MainSpriteRenderer->SetImageScale({ 1000.0f,1000.0f });
		//MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
		//MainSpriteRenderer->SetSamplerState(SamplerOption::POINT);

		//MainSpriteRenderer->SetEndEvent("Attack", std::bind(&Player::TestEvent, this, std::placeholders::_1));

		//MainSpriteRenderer->AutoSpriteSizeOn();
		//MainSpriteRenderer->SetAutoScaleRatio(0.8f);
		//MainSpriteRenderer->Transform.SetLocalScale({ -200.0f, 200.0f, 1.0f });


		// 자동으로 내부에서 트랜스폼을 이미지 크기로 변경까지 할것이다.
		//MainSpriteRenderer->SetSprite("TestPlayer.png", 5);

		//std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
		/*Renderer->Transform.SetLocalPosition({ 0, 150, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });*/
	}

	//{
	//	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(30);
	//	MainSpriteRenderer->SetSprite("HoHoYee_AttackABC2");
	//	MainSpriteRenderer->Transform.SetLocalPosition({ 0, 70, 1.0f });
	//	MainSpriteRenderer->SetImageScale({ 100.0f, 20.0f });
	//	MainSpriteRenderer->SetPivotType(PivotType::Left);
	//}


	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		Col->Transform.SetLocalScale({ -100.0f, 100.0f, 1.0f });
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	int a = 0;
}

void Player::Update(float _Delta)
{
	//MainSpriteRenderer->AddImageScale(float4{ -10.0f, 0.0f, 0.0f } * _Delta);
	/*if (xxxx 상황이 되면)
	{
		MainSpriteRenderer->Death();
		MainSpriteRenderer = nullptr;
	}*/

	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			Col->GetActor()->Death();
			int a = 0;
		};

	Event.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			int a = 0;
		};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			int a = 0;
		};

	Col->CollisionEvent(ContentsCollisionType::Monster, Event);

	// 충돌했냐 안했냐만 보면 (만들어질 인터페이스 형식일뿐)
	//std::list<std::shared_ptr<Monster>> MonsterList =
	//	GetLevel()->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);

	//for (std::shared_ptr<Monster> MonsterPtr : MonsterList)
	//{
	//	// 렌더러로 하는 이유 => 엑터로도 할 수 있는데
	//	// 보통 엑터는 위치와 기준을 잡아주는 용도로 사용됩니다.
	//	// MainSpriteRenderer->Transform.Collision(MonsterPtr->Renderer->Transform);
	//	
	//	GameEngineTransform& Left = MainSpriteRenderer->Transform;
	//	GameEngineTransform& Right = MonsterPtr->Renderer->Transform;
	//	Right.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	//	if (GameEngineTransform::Collision({Left, Right}))
	//	{
	//		MonsterPtr->Death();
	//		int a = 0;
	//		// 충돌 했다.
	//	}
	//}


	float Speed = 1000.0f;

	if (GameEngineInput::IsDown('P'))
	{
		MainSpriteRenderer->AnimationPauseSwitch();
	}

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
		MainSpriteRenderer->ChangeAnimation("Walk");
	}
	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
		MainSpriteRenderer->ChangeAnimation("Walk");
	}
	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
		MainSpriteRenderer->ChangeAnimation("Walk");
	}
	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
		MainSpriteRenderer->ChangeAnimation("Walk");
	}
	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}
	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}

	if (GameEngineInput::IsDown(VK_SHIFT))
	{
		MainSpriteRenderer->ChangeAnimation("Attack");
	}

	if (GameEngineInput::IsDown('1'))
	{
		MainSpriteRenderer->ChangeAnimation("Alert");
	}

	if (GameEngineInput::IsDown('2'))
	{
		MainSpriteRenderer->ChangeAnimation("Dead");
	}
	if (GameEngineInput::IsDown('3'))
	{
		MainSpriteRenderer->ChangeAnimation("Fly");
	}
	if (GameEngineInput::IsDown('4'))
	{
		MainSpriteRenderer->ChangeAnimation("Impale");
	}
	if (GameEngineInput::IsDown('5'))
	{
		MainSpriteRenderer->ChangeAnimation("Jump");
	}
	if (GameEngineInput::IsDown('6'))
	{
		MainSpriteRenderer->ChangeAnimation("Prone");
	}
	if (GameEngineInput::IsDown('7'))
	{
		MainSpriteRenderer->ChangeAnimation("ProneAttack");
	}
	if (GameEngineInput::IsDown('8'))
	{
		MainSpriteRenderer->ChangeAnimation("Rope");
	}
	if (GameEngineInput::IsDown('9'))
	{
		MainSpriteRenderer->ChangeAnimation("Stand");
	}
	if (GameEngineInput::IsDown('0'))
	{
		MainSpriteRenderer->ChangeAnimation("Walk");
	}


	//GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	//if (GameEngineColor::RED != Color)
	//{
	//	GravityForce.Y -= _Delta * 10.0f;
	//	Transform.AddLocalPosition(GravityForce * _Delta);
	//}
	//else
	//{
	//	GravityForce = 0.0f;
	//}
}