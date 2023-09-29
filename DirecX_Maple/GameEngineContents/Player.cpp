#include "PreCompile.h"
#include "Player.h"


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
		
		MainSpriteRenderer->CreateAnimation("Battle_Stand", "Battle_Stand", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Walk", "Battle_Walk", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Alert", "Battle_Alert", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Prone", "Battle_Prone", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Attack", "Battle_Attack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_ProneAttack", "Battle_ProneAttack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Jump", "Battle_Jump", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Fly", "Battle_Fly", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Impale", "Battle_Impale", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Dead", "Battle_Dead", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Rope", "Battle_Rope", 0.1f, -1, -1, true);


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
		MainSpriteRenderer->SetPivotType(PivotType::Center);
		Clothes = PlayerClothes::Normal;


		//{
		//	SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
		//	SkillRenderer->AutoSpriteSizeOn();
		//	SkillRenderer->CreateAnimation("DobleJump", "JumpNormal", 0.1f, -1, -1, true);
		//	SkillRenderer->ChangeAnimation("DobleJump");
		//	SkillRenderer->Off();

		//}
		
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
		Col->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
		Col->Transform.SetLocalScale({ 50.0f, 50.0f, 1.0f });
	}

	ChangeState(PlayerState::Stand);
	Dir = ActorDir::Left;

	float4 Pos = MainSpriteRenderer->Transform.GetWorldPosition();

	int a = 0;
}

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	int a = 0;
}

void Player::Update(float _Delta)
{
	GameEngineDebug::DrawBox2D(MainSpriteRenderer->GetImageTransform(), float4::BLUE);

	PlayerActor::Update(_Delta);
	DirCheck();
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
		Clothes = PlayerClothes::Battle;
	}

	if (GameEngineInput::IsDown('2'))
	{
		Clothes = PlayerClothes::Normal;
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
		SkillRenderer->On();
		SkillRenderer->Transform.SetLocalPosition(MainSpriteRenderer->Transform.GetLocalPosition());
	}


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


}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (State)
		{
		case PlayerState::Stand:
			StandEnd();
			break;
		case PlayerState::Walk:
			WalkEnd();
			break;
		case PlayerState::Jump:
			JumpEnd();
			break;
		default:
			break;
		}

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

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Stand:
		return StandUpdate(_Delta);
	case PlayerState::Walk:
		return WalkUpdate(_Delta);
	case PlayerState::Alert:
		return AlertUpdate(_Delta);
	case PlayerState::Prone:
		return ProneUpdate(_Delta);
	case PlayerState::Attack:
		return AttackUpdate(_Delta);
	case PlayerState::ProneAttack:
		return ProneAttackUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	case PlayerState::DoubleJump:
		return DoubleJumpUpdate(_Delta);
	case PlayerState::Fly:
		return FlyUpdate(_Delta);
	case PlayerState::Dead:
		return DeadUpdate(_Delta);
	default:
		break;
	}
}

void Player::DirCheck()
{
	ActorDir CheckDir = ActorDir::Max;

	if (true == GameEngineInput::IsPress(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		CheckDir = ActorDir::Left;
		MainSpriteRenderer->LeftFlip();
		//if (IsGround == true)
		//{
		//	ChangeAnimationState("Walk");
		//}
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && true == GameEngineInput::IsFree(VK_LEFT))
	{
		CheckDir = ActorDir::Right;
		MainSpriteRenderer->RightFlip();
		//if (IsGround == true)
		//{
		//	ChangeAnimationState("Walk");
		//}
	}
	else if(true == GameEngineInput::IsPress(VK_RIGHT) && true == GameEngineInput::IsDown(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT) && true == GameEngineInput::IsPress(VK_LEFT))
	{
		Dir = CheckDir;
		if (IsGround == true)
		{
			ChangeAnimationState("Stand");
		}
		return;
	}

	if (CheckDir != ActorDir::Max)
	{
		Dir = CheckDir;
	}

}


void Player::ChangeAnimationState(const std::string& _StateName)
{
	switch (Clothes)
	{
	case PlayerClothes::Battle:
		AnimationName = "Battle_";
		break;
	case PlayerClothes::Normal:
		AnimationName = "Normal_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	MainSpriteRenderer->ChangeAnimation(AnimationName);
}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}
