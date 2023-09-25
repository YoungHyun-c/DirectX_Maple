#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BackGroundMap.h"
#include "Monster.h"

Player* Player::MainPlayer = nullptr;

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
		MainSpriteRenderer->SetImageScale({ 256.0f, 256.0f });
		//MainSpriteRenderer->CreateAnimation("Battle_Alert", "Battle_Alert", 0.1f, -1, -1, true);

		MainSpriteRenderer->CreateAnimation("Normal_Stand", "Stand", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Walk", "Walk", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Alert", "Alert", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Prone", "Prone", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Attack", "Attack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_ProneAttack", "ProneAttack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Jump", "Jump", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Fly", "Fly", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Impale", "Impale", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Dead", "Dead", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Rope", "Rope", 0.1f, -1, -1, true);

		MainSpriteRenderer->ChangeAnimation("Normal_Stand");
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

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		Col->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	}

	ChangeState(PlayerState::Stand);
	Dir = PlayerDir::Left;
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

	StateUpdate(_Delta);

	// 줌인 줌아웃
	if (GameEngineInput::IsPress('I'))
	{
		GetLevel()->GetMainCamera()->AddZoomValue(-_Delta);
	}
	if (GameEngineInput::IsPress('O'))
	{
		GetLevel()->GetMainCamera()->AddZoomValue(_Delta);
	}

	if (GameEngineInput::IsDown('P'))
	{
		MainSpriteRenderer->AnimationPauseSwitch();
	}

	if (GameEngineInput::IsDown(VK_SHIFT))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Attack");
	}

	if (GameEngineInput::IsDown('1'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Alert");
	}

	if (GameEngineInput::IsDown('2'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Dead");
	}
	if (GameEngineInput::IsDown('3'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Fly");
	}
	if (GameEngineInput::IsDown('4'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Impale");
	}
	if (GameEngineInput::IsDown('5'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Jump");
	}
	if (GameEngineInput::IsDown('6'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Prone");
	}
	if (GameEngineInput::IsDown('7'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_ProneAttack");
	}
	if (GameEngineInput::IsDown('8'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Rope");
	}
	if (GameEngineInput::IsDown('9'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Stand");
	}
	if (GameEngineInput::IsDown('0'))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Walk");
	}


	//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Transform.GetWorldPosition());

	float4 WorldMousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	OutputDebugStringA(WorldMousePos.ToString("\n").c_str());

	//BackGroundMap::MainMap->GetLevel()->GetName();

	//GameEngineColor Color = BackGroundMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED, DebugMapName);
	//if (GameEngineColor::RED != Color)
	//{
	//	GravityForce.Y -= _Delta * 900.0f;
	//	Transform.AddLocalPosition(GravityForce * _Delta);
	//}
	//else
	//{
	//	//if (Color != GameEngineColor::White)
	//	//{
	//	//	Transform.AddLocalPosition(float4::UP);
	//	//}
	//	GravityForce = 0.0f;
	//}

	PlayerActor::Update(_Delta);
	PlayerActor::CameraFocus(_Delta);
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Stand:
		return StandUpdate(_Delta);
		break;
	case PlayerState::Walk:
		return WalkUpdate(_Delta);
		break;
	case PlayerState::Alert:
		return AlertUpdate(_Delta);
		break;
	case PlayerState::Prone:
		return ProneUpdate(_Delta);
		break;
	case PlayerState::Attack:
		return AttackUpdate(_Delta);
		break;
	case PlayerState::ProneAttack:
		return ProneAttackUpdate(_Delta);
		break;
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
		break;
	case PlayerState::DoubleJump:
		return DoubleJumpUpdate(_Delta);
		break;
	case PlayerState::Fly:
		return FlyUpdate(_Delta);
		break;
	case PlayerState::Dead:
		return DeadUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Stand:
			StandStart();
			break;
		case PlayerState::Walk:
			WalkStart();
			break;
		case PlayerState::Alert:
			AlertStart();
			break;
		case PlayerState::Prone:
			ProneStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::ProneAttack:
			ProneAttackStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::DoubleJump:
			DoubleJumpStart();
			break;
		case PlayerState::Fly:
			FlyStart();
			break;
		case PlayerState::Dead:
			DeadStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	if (true == GameEngineInput::IsFree(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LEFT) )//|| true == GameEngineInput::IsFree(VK_RIGHT))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT))// || true == GameEngineInput::IsFree(VK_LEFT))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;
	}
}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	switch (Dir)
	{
	// 이미지 뒤집을 생각
	case PlayerDir::Left:
		MainSpriteRenderer->RightFlip();
		break;
	case PlayerDir::Right:
		MainSpriteRenderer->LeftFlip();
		break;
	default:
		break;
	}

	CurState = _StateName;

	MainSpriteRenderer->ChangeAnimation(CurState);
}
