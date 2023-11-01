#include "PreCompile.h"
#include "GhostDamien.h"
#include "Player.h"

GhostDamien* GhostDamien::SummonDamien;

GhostDamien::GhostDamien()
{
	
}

GhostDamien::~GhostDamien()
{

}



void GhostDamien::Start()
{
	TimeCounting();

	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	MonsterRenderer->CreateAnimation("Regen", "GhostDamien_Regen", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Stand", "GhostDamien_Stand", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Attack", "GhostDamien_Attack", 0.1f, -1, -1, false); // 슬라이드 공격(밀격)
	MonsterRenderer->CreateAnimation("Skill1", "GhostDamien_Skill1", 0.1f, -1, -1, false); // 걸어서 움직이지 않음 플레이어 주변에 순간이동
	MonsterRenderer->CreateAnimation("Skill1After", "GhostDamien_Skill1After", 0.1f, -1, -1, false); // 순간이동 후

	MonsterRenderer->SetFrameEvent("Attack", 6, [&](GameEngineSpriteRenderer*)
		{
			SlideAttack = true;
			SlideAttackCol->On();
		}
	);
	MonsterRenderer->SetFrameEvent("Attack", 10, [&](GameEngineSpriteRenderer*)
		{
			SlideAttack = false;
			SlideAttackCol->Off();
		}
	);

	MonsterRenderer->SetFrameEvent("Skill1", 4, [&](GameEngineSpriteRenderer*)
		{
			MonsterCollision->Off();
			DamienAttackRangeCol->Off();
		}
	);
	MonsterRenderer->SetFrameEvent("Skill1After", 4, [&](GameEngineSpriteRenderer*)
		{
			MonsterCollision->On();
			DamienAttackRangeCol->On();
		}
	);

	MonsterRenderer->CreateAnimation("Skill2", "GhostDamien_Skill2", 0.1f, -1, -1, false); // 
	MonsterRenderer->CreateAnimation("Skill2After", "GhostDamien_Skill2After", 0.1f, -1, -1, false);

	MonsterRenderer->SetFrameEvent("Skill2", 5, [&](GameEngineSpriteRenderer*)
		{
			MonsterCollision->Off();
			DamienAttackRangeCol->Off();
		}
	);
	MonsterRenderer->SetFrameEvent("Skill2", 11, [&](GameEngineSpriteRenderer*)
		{
			MonsterCollision->Transform.SetLocalPosition({ 20.0f, 400.0f });
			MonsterCollision->On();
		}
	);


	MonsterRenderer->CreateAnimation("Death", "GhostDamien_Death", 0.1f, -1, -1, false);

	MonsterRenderer->ChangeAnimation("Stand");
	MonsterRenderer->AutoSpriteSizeOn();
	MonsterRenderer->SetPivotType(PivotType::Center);
	Dir = ActorDir::Right;
	MonsterRenderer->Off();

	{
		MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		MonsterCollision->Transform.SetLocalScale({ 75.0f, 130.0f });
		MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
		MonsterCollision->Off();

		DamienAttackRangeCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
		DamienAttackRangeCol->Transform.SetLocalPosition({ 50.0f, 50.0f });
		DamienAttackRangeCol->Transform.SetLocalScale({ 800.0f, 250.0f });
		DamienAttackRangeCol->SetCollisionType(ColType::AABBBOX2D);
		DamienAttackRangeCol->Off();

		SlideAttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
		SlideAttackCol->Transform.SetLocalPosition({ 100.0f, 0.0f });
		SlideAttackCol->Transform.SetLocalScale({ 100.0f, 200.0f });
		SlideAttackCol->SetCollisionType(ColType::AABBBOX2D);
		SlideAttackCol->Off();
	}
	HitEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::MonsterSkill);
	HitEffect->CreateAnimation("BackEffect", "GhostDamien_Attack1_BackEffect", 0.1f, -1, -1, false); // 
	HitEffect->CreateAnimation("Skill2Hit", "GhostDamien_Skill2Hit", 0.1f, -1, -1, false);

	HitEffect->ChangeAnimation("BackEffect");
	HitEffect->AutoSpriteSizeOn();
	HitEffect->SetPivotType(PivotType::Center);
	HitEffect->Off();

	SetMoveSpeed(MoveSpeed);
	SetStandLimitTime(4.0f);

	SetColPos(-50.0f, 50.0f, 0.0f);
	GameEngineInput::AddInputObject(this);
}

void GhostDamien::Update(float _Delta)
{
	GameEngineDebug::DrawBox2D(MonsterRenderer->GetImageTransform(), float4::GREEN);
	MonsterFunction::Update(_Delta);
	TimeCounting();

	if (Hp <= 0)
	{
		ChangeState(MonsterState::Death);
		return;
	}

	AttackEvent(_Delta);
	StateUpdate(_Delta);

	if (GameEngineInput::IsDown('5', this))
	{
		ChangeState(MonsterState::Regen);

	}
	if (GameEngineInput::IsDown('6', this))
	{
	//	HitEffect->ChangeAnimation("BackEffect");
	//	HitEffect->Transform.SetLocalPosition({ -50.0f });
	//	HitEffect->On();
	//	MonsterRenderer->ChangeAnimation("Attack");
	//	DirCheck();
	//	MonsterRenderer->Transform.SetLocalPosition({ -10.0f, -50.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ 50.0f, 150.0f });
		ChangeState(MonsterState::Stand);
	}
	//if (GameEngineInput::IsDown('7', this))
	//{
	//	//ChangeState(MonsterState::Die);
	//	//MonsterRenderer->RightFlip();
	//	//Dir = ActorDir::Left;
	//	MonsterRenderer->ChangeAnimation("Skill1");
	//	DirCheck();
	//	MonsterRenderer->Transform.SetLocalPosition({ -5.0f, -5.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ 50.0f, 150.0f });
	//}
	//if (GameEngineInput::IsDown('8', this))
	//{
	//	//ChangeState(MonsterState::Skill1);
	//	MonsterRenderer->ChangeAnimation("Skill1After");
	//	DirCheck();
	//	MonsterRenderer->Transform.SetLocalPosition({ 5.0f, -10.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ 50.0f, 150.0f });
	//}
	if (GameEngineInput::IsDown('9', this))
	{
		ChangeState(MonsterState::Skill2);
		//MonsterRenderer->ChangeAnimation("Skill2");
		//DirCheck();
		//MonsterRenderer->Transform.SetLocalPosition({ 30.0f, 0.0f });
		//MonsterCollision->Transform.SetLocalPosition({ 50.0f, 150.0f });
	}

	if (GameEngineInput::IsDown('0', this))
	{
		HitEffect->ChangeAnimation("Skill2Hit");
		MonsterRenderer->ChangeAnimation("Skill2After");
		DirCheck();
		MonsterRenderer->Transform.SetLocalPosition({ 400.0f, -10.0f });
		MonsterCollision->Transform.SetLocalPosition({ 440.0f, 150.0f });
	}

	if (GameEngineInput::IsDown('-', this))
	{
		//ChangeState(MonsterState::Death);
		MonsterRenderer->ChangeAnimation("Death");
		DirCheck();
		MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
		MonsterCollision->Transform.SetLocalPosition({ 50.0f, 150.0f });
	}

	//DirCheck();
	//InsideLockMap();
	SlideAttackCol->Collision(ContentsCollisionType::Player, std::bind(&GhostDamien::CollisionEvent, this, std::placeholders::_1));
}

void GhostDamien::CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
{
	//Player::GetMainPlayer()->PlayerBind(1.5f);
	float4 Dir = Player::GetMainPlayer()->Transform.GetWorldPosition().X - Transform.GetWorldPosition().X;
	Dir.Normalize();
	Player::GetMainPlayer()->KnockBack(Dir, 500.0f, 800.0f, 1.0f);
}


void GhostDamien::StandStart()
{
	DirCheck();
	ChangeAnimationState("Stand");
	MonsterCollision->On();
	DamienAttackRangeCol->On();
}

void GhostDamien::StandUpdate(float _Delta)
{
	M_FStopTime += _Delta;
	if (M_FStopTime >= M_FStopLimitTime)
	{
		ChangeState(MonsterState::Skill1);
	}
}

void GhostDamien::AttackStart()
{
	DirCheck();
	ChangeAnimationState("Attack");
}

void GhostDamien::AttackUpdate(float _Delta)
{
	if (Dir == ActorDir::Right && SlideAttack == true)
	{
		Transform.AddLocalPosition({ 1000.0f * _Delta, 0.0f });
		SlideAttackCol->Transform.SetLocalPosition({ 100.0f, 0.0f });
		if (Transform.GetWorldPosition().X > RightCheck)
		{
			Transform.SetWorldPosition({ RightCheck, -650.0f });
			return;
		}
	}
	else if (Dir == ActorDir::Left && SlideAttack == true)
	{
		Transform.AddLocalPosition({ -1000.0f * _Delta, 0.0f });
		SlideAttackCol->Transform.SetLocalPosition({ -100.0f, 0.0f });
		if (Transform.GetWorldPosition().X < LeftCheck)
		{
			Transform.SetWorldPosition({ LeftCheck , -650.0f });
			return;
		}
	}
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
		return;
	}
}

void GhostDamien::Skill_1Start()
{
	ChangeAnimationState("Skill1");
}

void GhostDamien::Skill_1After()
{
	ChangeAnimationState("Skill1After");
	DirCheck();
	float4 TestPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	if (TestPos.X <= LeftCheck + 100.0f)
	{
		Transform.SetWorldPosition({ TestPos.X + LeftCheck + 100.0f, -650.0f });
		return;
	}
	else if (TestPos.X >= RightCheck)
	{
		Transform.SetWorldPosition({ RightCheck - 20.0f, -650.0f });
		return;
	}
	else
	{
		Dir = ActorDir::Right;
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + RightColPos,
			MonsterRenderer->Transform.GetLocalPosition().Y + YColPos });
		MonsterRenderer->LeftFlip();
		Transform.SetWorldPosition({ TestPos.X - 200.0f, -650.0f });
		return;
	}
}

void GhostDamien::Skill_1AfterUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
		return;
	}
}

void GhostDamien::Skill_2Start()
{
	ChangeAnimationState("Skill2");
	//MonsterRenderer->Transform.GetWorldPosition();
	//MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 250.0f });
	Transform.SetWorldPosition({ MonsterRenderer->Transform.GetWorldPosition().X, MonsterRenderer->Transform.GetWorldPosition().Y + 250.0f });
}

void GhostDamien::Skill_2Update(float _Delta)
{
	DirCheck();
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Skill2After);
		return;
	}
}
void GhostDamien::Skill_2After()
{
	ChangeAnimationState("Skill2After");
	//Transform.SetLocalPosition({ 0.0f, 250.0f });
}
void GhostDamien::Skill_2AfterUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
		return;
	}
}

void GhostDamien::DeathStart()
{
	MonsterRenderer->ChangeAnimation("Death");
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 250.0f });
	MonsterCollision->Off();
	DamienAttackRangeCol->Off();
	SlideAttackCol->Off();
}


void GhostDamien::DeathUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		MonsterRenderer->Off();
	}
}


void GhostDamien::Hit(long long _Damage, bool _Attack)
{
	if (_Attack == false)
	{
		return;
	}

	if (_Attack == true)
	{
		Hp -= _Damage;
	}

	if (Hp <= 0)
	{
		ChangeState(MonsterState::Death);
	}
}

void GhostDamien::AttackEvent(float _Delta)
{
	EventParameter AttackRange;

	if (IsAttack == false && StartAttack < AttackCool)
	{
		AttackRange.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Player)
			{
				IsAttack = true;
			};
		AttackRange.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Player)
			{
				IsAttack = true;
			};
		DamienAttackRangeCol->CollisionEvent(ContentsCollisionType::Player, AttackRange);
	}

	if (IsAttack == true)
	{
		StartAttack += _Delta;
		if (0.5f > StartAttack)
		{
			GameEngineRandom AttackRan;
			switch (1)
			{
			case 1:
				ChangeState(MonsterState::Attack);
				break;
			case 2:
				ChangeState(MonsterState::Skill2);
				break;
			default:
				break;
			}
		}
		if (StartAttack > AttackCool)
		{
			StartAttack = 0.0f;
			IsAttack = false;
		}
	}
}


void GhostDamien::InsideLockMap()
{
	if (Transform.GetWorldPosition().X < LeftCheck)
	{
		Transform.SetWorldPosition({ LeftCheck - 100.0f, -650.0f});
		return;
	}
	else if (Transform.GetWorldPosition().X > RightCheck)
	{
		Transform.SetWorldPosition({ RightCheck - 50.0f, -650.0f });
		return;
	}
}

void GhostDamien::LevelStart(GameEngineLevel* _PrevLevel)
{
	MonsterName = static_cast<int>(MonstersName::GhostDamien);
	SummonDamien = this;
}

void GhostDamien::CallRegen()
{
	ChangeState(MonsterState::Regen);
}