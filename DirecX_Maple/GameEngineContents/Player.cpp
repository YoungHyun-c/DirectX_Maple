#include "PreCompile.h"
#include "Player.h"


#include "BackGroundMap.h"
#include "Monster.h"
#include "SkillManager.h"
#include "BossSkillEffect.h"

#include "DropItem.h"

Player* Player::MainPlayer = nullptr;

#define Rope_Y_PIVOT 15.0f
#define Laader_Color GameEngineColor(0, 255, 0, 255)


Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	// 폰트 테스트
	//{
	//	std::shared_ptr<GameEngineSpriteRenderer> FontRender = CreateComponent<GameEngineSpriteRenderer>(30);
	//	FontRender->SetText("돋움", "안녕", 0.0f, float4::RED, FW1_CENTER);
	//}

	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Player);
		MainSpriteRenderer->Transform.SetLocalPosition({ 0, 0, 1 });
		//MainSpriteRenderer->SetMaterial("2DTextureOver"); //10/10
		//MainSpriteRenderer->SetImageScale({ 256.0f, 256.0f });
		//MainSpriteRenderer->RenderBaseInfoValue.Target1 = 1; // 렌더타겟 이용 업데이트

		//MainSpriteRenderer->CreateAnimation("Battle_Stand", "Battle_Stand", 0.3f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Walk", "Battle_Walk", 0.3f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Alert", "Battle_Alert", 0.1f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Prone", "Battle_Prone", 0.1f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Attack", "Battle_Attack", 0.1f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_ProneAttack", "Battle_ProneAttack", 0.3f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Jump", "Battle_Jump", 0.1f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Fly", "Battle_Fly", 0.1f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Impale", "Battle_Impale", 0.3f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Dead", "Battle_Dead", 0.1f, -1, -1, true);
		//MainSpriteRenderer->CreateAnimation("Battle_Rope", "Battle_Rope", 0.1f, -1, -1, true);


		MainSpriteRenderer->CreateAnimation("Normal_Stand", "Stand", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Walk", "Walk", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Alert", "Alert", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Prone", "Prone", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Attack", "Attack", 0.25f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_ProneAttack", "ProneAttack", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Jump", "Jump", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Fly", "Fly", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Impale", "Impale", 0.3f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Dead", "Dead", 0.1f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("Normal_Rope", "Rope", 0.1f, -1, -1, true);

		std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Stand");
		PlayerScale = Sprite->GetSpriteData(0).GetScale();
		Sprite = nullptr;

		/*SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		SkillRenderer->CreateAnimation("Divide1Hit_", "Divide1_Hit", 0.05f);
		SkillRenderer->ChangeAnimation("Divide1Hit_");
		SkillRenderer->Off();*/

		State = PlayerState::Stand;
		MainSpriteRenderer->ChangeAnimation("Normal_Stand");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetPivotType(PivotType::Center);


		// 색 검은색으로 만들기.
		//MainSpriteRenderer->RenderBaseInfoValue.BaseColorOnly = 1;
	}

	//PlayerPos = Transform.GetWorldPosition();
	Dir = ActorDir::Right;
	Clothes = PlayerClothes::Normal;
	//ChangeState(PlayerState::Stand);

	{
		PlayerCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		PlayerCol->SetCollisionType(ColType::AABBBOX2D); //10/10
		PlayerCol->Transform.SetLocalPosition({ -5.0f, -10.0f});
		PlayerCol->Transform.SetLocalScale({ 30.0f, 50.0f, 1.0f });

		PlayerDropCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerDropBody);
		PlayerDropCol->SetCollisionType(ColType::AABBBOX2D); //10/10
		PlayerDropCol->Transform.SetLocalPosition({ 0.0f, 0.0f });
		PlayerDropCol->Transform.SetLocalScale({ 500.0f, 500.0f });
	}

	//std::shared_ptr<GameEngineFrameAnimation> _Animation = MainSpriteRenderer->FindAnimation("Divide");
	//_Animation->Inter[0] = 0.05f;
	//_Animation->Inter[1] = 0.05f;

	/*{
		SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->CreateAnimation("DobleJump", "JumpNormal", 0.1f, -1, -1, true);
		SkillRenderer->ChangeAnimation("DobleJump");
		SkillRenderer->Off();
	}*/

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

	//Transform.SetLocalPosition({ 0, 0, static_cast<float>(ContentsObjectType::Player) });
	GameEngineInput::AddInputObject(this);
}

void Player::Update(float _Delta)
{
	PlayerPos = Transform.GetWorldPosition();

	InsideLockMap();
	PlayerActor::Update(_Delta);

	if (Bind == true)
	{
		CurTime += _Delta;
		PlayerBind();
		return;
	}

	if (isKnockBack == true)
	{
		KnockBackUpdate(_Delta);
		return;
	}
	GetItem();

	//FlyCheckUpdate();

	DirCheck();
	RopeCheck();
	StateUpdate(_Delta);

	if ((PlayerState::Prone == State || PlayerState::Alert == State || PlayerState::Stand == State || PlayerState::Walk == State) && false == IsGround)
	{
		ChangeState(PlayerState::Jump);
	}

	if (true == IsGround && (PlayerState::Jump != State && PlayerState::Walk != State))
	{
		MoveVectorForceReset();
		GravityReset();
	}


	//if (GameEngineInput::IsDown('Y', this))
	//{
	//	std::shared_ptr<AdeleSkill> Shard = GetLevel()->CreateActor<AdeleSkill>();

	//	Shard->SetSkillActor("Shard");
	//}

	//if (GameEngineInput::IsDown('R', this))
	//{
	//	std::shared_ptr<AdeleSkill> Maestro = GetLevel()->CreateActor<AdeleSkill>();

	//	//Maestro->SetSkillActor("Maestro");
	//}

	////////////////////// 데미지 렌더 테스트중//////////////////////
	//if (GameEngineInput::IsDown('3', this))
	//{
	//	std::shared_ptr<AdeleSkill> Ruin = GetLevel()->CreateActor<AdeleSkill>();
	//	Ruin->SetSkillActor("Ruin");
	//	/*std::shared_ptr<DamageRenderer> NewDR = GetLevel()->CreateActor<DamageRenderer>();
	//	NewDR->PushDamage(480);*/
	//}

	//if (GameEngineInput::IsDown('Z', this))
	//{
	//	std::shared_ptr<AdeleSkill> Impale = GetLevel()->CreateActor<AdeleSkill>();

	//	Impale->SetSkillActor("Impale", this);
	//}

	//if (GameEngineInput::IsDown('C', this))
	//{
	//	std::shared_ptr<AdeleSkill> Lesonens = GetLevel()->CreateActor<AdeleSkill>();

	//	Lesonens->SetSkillActor("Lesonens");
	//}

	if (GameEngineInput::IsDown('5', this))
	{
		PlayerValue::GetValue()->SetGrade(5);
	}
	if (GameEngineInput::IsDown('6', this))
	{
		PlayerValue::GetValue()->SetGrade(6);
	}

	if (PlayerValue::GetValue()->GetDivide6Use() == true)
	{
		DivideTime += _Delta;
		if (DivideTime >= DivideCool)
		{
			PlayerValue::GetValue()->SetDivideUse(false);
			DivideTime = 0.0f;
		}
	}
}

void Player::ChangeToStand()
{
	if (true == IsGround)
	{
		GroundJump = false;
		DoubleJump = false;
	}

	if (0.0f < AlertTime)
	{
		ChangeState(PlayerState::Alert);
	}
	else
	{
		ChangeState(PlayerState::Stand);
	}
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
		case PlayerState::Fly:
			FlyEnd();
			break;
		case PlayerState::Rope:
			RopeEnd();
			break;
		case PlayerState::Attack:
			AttackEnd();
			break;
		case PlayerState::Alert:
			AlertEnd();
			break;
		case PlayerState::Prone:
			ProneEnd();
			break;
		case PlayerState::Max:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려 했습니다.");
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
		case PlayerState::Rope:
			RopeStart();
			break;
		case PlayerState::Fly:
			FlyStart();
			break;
		case PlayerState::Dead:
			DeadStart();
			break;
		case PlayerState::Max:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려 했습니다.");
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
	case PlayerState::Rope:
		return RopeUpdate(_Delta);
	case PlayerState::Fly:
		return FlyUpdate(_Delta);
	case PlayerState::Dead:
		return DeadUpdate(_Delta);
	case PlayerState::Max:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌리려 했습니다.");
		break;
	}
}

void Player::DirCheck()
{
	if (IsAttack == true)
	{
		return;
	}

	ActorDir CheckDir = ActorDir::Max;

	if (true == GameEngineInput::IsPress(VK_LEFT, this) && true == GameEngineInput::IsFree(VK_RIGHT, this))
	{
		CheckDir = ActorDir::Left;
		MainSpriteRenderer->LeftFlip();
		/*if (IsGround == true && false == GameEngineInput::IsPress('X', this) && IsRope == false)
		{
			ChangeAnimationState("Walk");
		}*/
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT, this) && true == GameEngineInput::IsFree(VK_LEFT, this))
	{
		CheckDir = ActorDir::Right;
		MainSpriteRenderer->RightFlip();
		/*if (IsGround == true && false == GameEngineInput::IsPress('X', this) && IsRope == false)
		{
			ChangeAnimationState("Walk");
		}*/
	}
	else if(true == GameEngineInput::IsPress(VK_RIGHT, this) && true == GameEngineInput::IsDown(VK_LEFT, this)
		|| true == GameEngineInput::IsDown(VK_RIGHT, this) && true == GameEngineInput::IsPress(VK_LEFT, this))
	{
		Dir = CheckDir;
		/*if (IsGround == true && IsRope == false && AlertTime != 0.0f)
		{
			ChangeAnimationState("Stand");
		}*/
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
		Transform.SetLocalPosition(float4{ -LeftCheck.X, CurPos.Y });
	}
	else if (CurMapScale.X <= CurPos.X + RightCheck.X)
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - RightCheck.X, CurPos.Y });
	}

	CurPos.Y *= -1.0f;
	if (0 >= CurPos.Y - UpCheck.Y)
	{
		Transform.SetLocalPosition(float4{ CurPos.X, -UpCheck.Y });
		MoveVectorForceReset();
	}
	else if (CurMapScale.Y <= CurPos.Y + GroundCheck.Y)
	{
		Transform.SetLocalPosition(float4{ CurPos.X, CurMapScale.Y + GroundCheck.Y });
	}
}

void Player::PlayerBind(float _Time)
{
	Bind = true;
	if (CurTime >= _Time)
	{
		Bind = false;
		CurTime = 0.0f;
		return;
	}
}

void Player::KnockBack(float4 _Dir, float _Distance, float _Speed, float _MinTime)
{
	if (isKnockBack == false)
	{
		isKnockBack = true;
		if (MyKnockBackInfo == nullptr)
		{
			MyKnockBackInfo = std::make_shared<KnockBackInfo>();
			MyKnockBackInfo->Dir = _Dir;
			MyKnockBackInfo->Distance = _Distance;
			MyKnockBackInfo->Speed = _Speed;
			MyKnockBackInfo->MinTime = _MinTime;
		}
		else
		{
			MsgBoxAssert("KncokBackInfo?");
			return;
		}
	}
}

void Player::KnockBackUpdate(float _Delta)
{
	if (MyKnockBackInfo == nullptr)
	{
		MsgBoxAssert("넉백인포가 Nullptr인데 넉백되었습니다.");
	}

	CurTime = static_cast<float>(clock());
	TimeCount = (CurTime - PrevTime) / 1000.0f;
	PrevTime = CurTime;

	float4 CurPos = Transform.GetLocalPosition();
	Transform.SetLocalPosition(CurPos + MyKnockBackInfo->Dir * MyKnockBackInfo->Speed * _Delta);
	MyKnockBackInfo->Time += TimeCount;
	InsideLockMap();
	if (MyKnockBackInfo->Time >= MyKnockBackInfo->MinTime)
	{
		isKnockBack = false;
		MyKnockBackInfo = nullptr;
	}
}

void Player::GetItem()
{
	//if (GameEngineInput::IsDown('0',this) == false)
	//{
	//	return;
	//}

	EventParameter DropEvent;
	DropEvent.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			//if (GameEngineInput::IsDown('0', this) == true)
			{
				std::shared_ptr<DropItem> _Item = _Other->GetActor()->GetDynamic_Cast_This<DropItem>();
				_Item->GetItem();
			}
		};
	DropEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			//if (GameEngineInput::IsDown('0', this) == true)
			{
				std::shared_ptr<DropItem> _Item = _Other->GetActor()->GetDynamic_Cast_This<DropItem>();
				_Item->GetItem();
			}
		};
	PlayerDropCol->CollisionEvent(ContentsCollisionType::DropItem, DropEvent);

	/*std::shared_ptr<GameEngineCollision> collision = PlayerCol->Collision(ContentsCollisionType::DropItem, )
		Collision(static_cast<int>(CollisionOrder::DropItem), ColType::AABBBOX2D, ColType::AABBBOX2D);*/

}

void Player::Level_Up()
{
	if (LevelUp != nullptr && true != LevelUp->IsCurAnimationEnd())
	{
		return;
	}

	LevelUp = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	LevelUp->CreateAnimation("LevelUp", "LevelUp", 0.1f, false);
	LevelUp->Transform.SetLocalPosition({0.0f, 150.0f });
	LevelUp->AutoSpriteSizeOn();
	LevelUp->ChangeAnimation("LevelUp");
	LevelUp->On();
	LevelUp->SetEndEvent("LevelUp", [&](GameEngineSpriteRenderer*)
		{
			LevelUp->Off();
			LevelUpCol->Off();
		}
	);


	EventParameter HitEvent;

	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			std::shared_ptr<DamageRenderer> NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, 1, INT_MAX, 1);
		};

	LevelUpCol =  CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	LevelUpCol->SetCollisionType(ColType::AABBBOX2D);
	LevelUpCol->Transform.SetLocalPosition({ 0.0f, 150.0f });
	LevelUpCol->Transform.SetLocalScale({ 1000.0f, 800.0f });
	LevelUpCol->On();
	LevelUpCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
}

void Player::RopeCheck()
{
	float YPivot = 0.0f;
	if (GameEngineInput::IsPress(VK_UP, this))
	{
		YPivot = Rope_Y_PIVOT;
	}
	else if (GameEngineInput::IsPress(VK_DOWN, this))
	{
		//YPivot = -Rope_Y_PIVOT;
		YPivot = -3.0f;
	}

	IsRope = false;
	for (float i = -3.0f; i <= 3.0f; i += 1.0f)
	{
		GameEngineColor CheckColor = CheckGroundColor(float4(i, YPivot - 35.0f));
		if (Laader_Color == CheckColor)
		{
			IsRope = true;
			RopePivot = i;
			return;
		}
	}
}

void Player::FlyCheckUpdate()
{
	//if (State == PlayerState::Jump)
	{
		TimeCounting();
		if (UpDoubleClick == true)
		{
			UpDoubleClick = false;
		}
		if (true == GameEngineInput::IsDown(VK_UP, this))
		{
			if (UpClick == true)
			{
				UpDoubleClick = true;
				UpClick = false;
				UpClickCount = 0.0f;
			}
			else
			{
				UpClick = true;
				UpClickCount = 0.0f;
			}
		}
		if (UpClick == true)
		{
			UpClickCount += TimeCount;
			if (UpClickCount > 0.2f)
			{
				UpClick = false;
			}
		}

		if (UpDoubleClick == true && State == PlayerState::Jump)
		{
			ChangeState(PlayerState::Fly);
			return;
		}

		if (UpDoubleClick == true && State == PlayerState::Fly)
		{
			ChangeState(PlayerState::Stand);
			return;
		}
	}
}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
	CurMapScale = BackGroundMap::MainMap->GetMapScale();
}