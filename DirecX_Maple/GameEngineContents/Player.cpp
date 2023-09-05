#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"
#include "Monster.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(30);
		MainSpriteRenderer->CreateAnimation("Attack", "Divideframes", 0.1f, -1, -1, false);
		//MainSpriteRenderer->CreateAnimation("Attack", "blosom.frames", 0.1f, 0, 14, false);
		//MainSpriteRenderer->CreateAnimation("Attack", "blosom.frames", 0.1f, 0, 39, true);
		//MainSpriteRenderer->CreateAnimation("Run", "9833020.img.skill1.frames"); 
		MainSpriteRenderer->ChangeAnimation("Attack");
		//MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
		MainSpriteRenderer->SetSamplerState(SamplerOption::POINT);

		MainSpriteRenderer->SetEndEvent("Attack", std::bind(&Player::TestEvent, this, std::placeholders::_1));

		//MainSpriteRenderer->AutoSpriteSizeOn();
		//MainSpriteRenderer->SetAutoScaleRatio(0.8f);
		MainSpriteRenderer->Transform.SetLocalScale({ -100.0f, 100.0f, 1.0f });


		// 자동으로 내부에서 트랜스폼을 이미지 크기로 변경까지 할것이다.
		//MainSpriteRenderer->SetSprite("TestPlayer.png", 5);

		//std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
		/*Renderer->Transform.SetLocalPosition({ 0, 150, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });*/
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
	/*if (xxxx 상황이 되면)
	{
		MainSpriteRenderer->Death();
		MainSpriteRenderer = nullptr;
	}*/

	// 충돌했냐 안했냐만 보면 (만들어질 인터페이스 형식일뿐)
	std::list<std::shared_ptr<Monster>> MonsterList =
		GetLevel()->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);

	for (std::shared_ptr<Monster> MonsterPtr : MonsterList)
	{
		// 렌더러로 하는 이유 => 엑터로도 할 수 있는데
		// 보통 엑터는 위치와 기준을 잡아주는 용도로 사용됩니다.
		// MainSpriteRenderer->Transform.Collision(MonsterPtr->Renderer->Transform);

		GameEngineTransform& Left = MainSpriteRenderer->Transform;
		GameEngineTransform& Right = MonsterPtr->Renderer->Transform;
				
		if (GameEngineTransform::Collision({Left, Right}))
		{
		//	// 충돌 했다.
		}
	}


	float Speed = 100.0f;

	if (GameEngineInput::IsDown('P'))
	{
		MainSpriteRenderer->AnimationPauseSwitch();
	}

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}
	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}
	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}
	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}
	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}
	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}

	GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		GravityForce.Y -= _Delta * 10.0f;
		Transform.AddLocalPosition(GravityForce * _Delta);
	}
	else
	{
		GravityForce = 0.0f;
	}
}