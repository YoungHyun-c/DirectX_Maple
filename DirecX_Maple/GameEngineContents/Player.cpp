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
		//MainSpriteRenderer->SetMaterial("2DTextureOver"); //10/10
		MainSpriteRenderer->SetImageScale({ 256.0f, 256.0f });

		MainSpriteRenderer->CreateAnimation("Battle_Stand", "Battle_Stand", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Walk", "Battle_Walk", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Alert", "Battle_Alert", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Prone", "Battle_Prone", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Attack", "Battle_Attack", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_ProneAttack", "Battle_ProneAttack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Jump", "Battle_Jump", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Fly", "Battle_Fly", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Impale", "Battle_Impale", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Dead", "Battle_Dead", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Battle_Rope", "Battle_Rope", 0.1f, -1, -1, true);


		MainSpriteRenderer->CreateAnimation("Normal_Stand", "Stand", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Walk", "Walk", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Alert", "Alert", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Prone", "Prone", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Attack", "Attack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_ProneAttack", "ProneAttack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Jump", "Jump", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Fly", "Fly", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Impale", "Impale", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Dead", "Dead", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Rope", "Rope", 0.1f, -1, -1, true);


		MainSpriteRenderer->ChangeAnimation("Normal_Stand");
		//MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetPivotType(PivotType::Center);

		std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Stand");
		PlayerScale = Sprite->GetSpriteData(0).GetScale();
		Sprite = nullptr;
	}

	Dir = ActorDir::Right;
	Clothes = PlayerClothes::Normal;
	ChangeState(PlayerState::Stand);

	{
		PlayerCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		PlayerCol->SetCollisionType(ColType::AABBBOX2D); //10/10
		PlayerCol->Transform.SetLocalPosition({ -5.0f, -10.0f, 1.0f });
		PlayerCol->Transform.SetLocalScale({ 30.0f, 50.0f, 1.0f });
	}

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
		

	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	//float4 Pos = MainSpriteRenderer->Transform.GetWorldPosition();

	Transform.SetLocalPosition({ 0, 0, static_cast<float>(ContentsObjectType::Player) });
	GameEngineInput::AddInputObject(this);
}

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	int a = 0;
}

void Player::Update(float _Delta)
{
	if (Bind == true)
	{
		return;
	}
	
	PlayerPos = Transform.GetWorldPosition();

	PlayerActor::Update(_Delta);

	GameEngineDebug::DrawBox2D(MainSpriteRenderer->GetImageTransform(), float4::BLUE);

	DirCheck();
	StateUpdate(_Delta);
	InsideLockMap();

	float Speed = 100.0f;
	if (GameEngineInput::IsPress('A', this))
	{
		MainSpriteRenderer->LeftFlip();
		Transform.AddLocalPosition(float4::FORWARD * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D', this))
	{
		MainSpriteRenderer->RightFlip();
		Transform.AddLocalPosition(float4::BACKWARD * _Delta * Speed);
	}

	// 줌인 줌아웃
	if (GameEngineInput::IsPress('I', this))
	{
		GetLevel()->GetMainCamera()->AddZoomValue(-_Delta);
	}
	if (GameEngineInput::IsPress('O', this))
	{
		GetLevel()->GetMainCamera()->AddZoomValue(_Delta);
	}

	if (GameEngineInput::IsDown('P', this))
	{
		MainSpriteRenderer->AnimationPauseSwitch();
	}

	if (GameEngineInput::IsDown('Y', this))
	{
		std::shared_ptr<AdeleSkill> Shard = GetLevel()->CreateActor<AdeleSkill>();

		Shard->SetSkillActor("Shard");
	}

	if (GameEngineInput::IsDown('R', this))
	{
		std::shared_ptr<AdeleSkill> Maestro = GetLevel()->CreateActor<AdeleSkill>();

		Maestro->SetSkillActor("Maestro");
	}

	//////////////////// 데미지 렌더 테스트중//////////////////////
	if (GameEngineInput::IsDown('3', this))
	{
		std::shared_ptr<AdeleSkill> Ruin = GetLevel()->CreateActor<AdeleSkill>();
		Ruin->SetSkillActor("Ruin");
		/*std::shared_ptr<DamageRenderer> NewDR = GetLevel()->CreateActor<DamageRenderer>();
		NewDR->PushDamage(480);*/
	}

	if (GameEngineInput::IsDown('Z', this))
	{
		std::shared_ptr<AdeleSkill> Impale = GetLevel()->CreateActor<AdeleSkill>();

		Impale->SetSkillActor("Impale", this);
	}

	if (GameEngineInput::IsDown('C', this))
	{
		std::shared_ptr<AdeleSkill> Lesonens = GetLevel()->CreateActor<AdeleSkill>();

		Lesonens->SetSkillActor("Lesonens");
	}

	if (GameEngineInput::IsDown('1', this))
	{
		Clothes = PlayerClothes::Battle;
	}

	if (GameEngineInput::IsDown('2', this))
	{
		Clothes = PlayerClothes::Normal;
	}
	if (GameEngineInput::IsDown('-', this))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Fly");
	}
	if (GameEngineInput::IsDown('4', this))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Impale");
	}
	if (GameEngineInput::IsDown('5', this))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Jump");
	}
	if (GameEngineInput::IsDown('6', this))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Prone");
	}
	if (GameEngineInput::IsDown('7', this))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_ProneAttack");
	}
	if (GameEngineInput::IsDown('8', this))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Rope");
	}
	if (GameEngineInput::IsDown('9', this))
	{
		MainSpriteRenderer->ChangeAnimation("Normal_Stand");
	}
	//if (GameEngineInput::IsDown('0'))
	//{
	//	SkillRenderer->On();
	//	SkillRenderer->Transform.SetLocalPosition(MainSpriteRenderer->Transform.GetLocalPosition());
	//}


	// 출력
	//float4 WorldMousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	//OutputDebugStringA(WorldMousePos.ToString("\n").c_str());
	//float MonsterHp = Monster::Monsters->GetMonsterHp();
	//std::string CurMonsterHp = "MonsterHp : ";
	//CurMonsterHp += std::to_string(static_cast<int>(MonsterHp));
	//CurMonsterHp += "\n";
	//OutputDebugStringA(CurMonsterHp.c_str());
	//BackGroundMap::MainMap->GetLevel()->GetName();

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
		case PlayerState::Attack:
			AttackEnd();
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

	if (IsAttack == true)
	{
		return;
	}

	if (true == GameEngineInput::IsPress(VK_LEFT, this) && true == GameEngineInput::IsFree(VK_RIGHT, this))
	{
		CheckDir = ActorDir::Left;
		MainSpriteRenderer->LeftFlip();
		//if (IsGround == true)
		//{
		//	ChangeAnimationState("Walk");
		//}
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT, this) && true == GameEngineInput::IsFree(VK_LEFT, this))
	{
		CheckDir = ActorDir::Right;
		MainSpriteRenderer->RightFlip();
		//if (IsGround == true)
		//{
		//	ChangeAnimationState("Walk");
		//}
	}
	else if(true == GameEngineInput::IsPress(VK_RIGHT, this) && true == GameEngineInput::IsDown(VK_LEFT, this)
		|| true == GameEngineInput::IsDown(VK_RIGHT, this) && true == GameEngineInput::IsPress(VK_LEFT, this))
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

void Player::InsideLockMap()
{
	float4 CurPos = Transform.GetWorldPosition();
	if (0 >= CurPos.X + LeftCheck.X)
	{
		Transform.SetLocalPosition(float4{ - LeftCheck.X, CurPos.Y });
	}
	else if (CurMapScale.X <= CurPos.X + RightCheck.X)
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - RightCheck.X, CurPos.Y });
	}

	CurPos.Y *= -1.0f;
	if (0 >= CurPos.Y - UpCheck.Y)
	{
		Transform.SetLocalPosition(float4{ CurPos.X, - UpCheck.Y });
		MoveVectorForceReset();
	}
	else if (CurMapScale.Y <= CurPos.Y + GroundCheck.Y)
	{
		Transform.SetLocalPosition(float4{ CurPos.X, CurMapScale.Y + GroundCheck.Y });
	}
}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
	CurMapScale = BackGroundMap::MainMap->GetMapScale();
}