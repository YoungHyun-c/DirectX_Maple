#include "PreCompile.h"
#include "GhostSwoo.h"

GhostSwoo* GhostSwoo::SummonSwoo = nullptr;

GhostSwoo::GhostSwoo()
{
	
}

GhostSwoo::~GhostSwoo()
{

}

void GhostSwoo::Start()
{
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	MonsterRenderer->CreateAnimation("Regen", "GhostSwoo_Regen", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Stand", "GhostSwoo_Stand", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Move", "GhostSwoo_Move", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Attack", "GhostSwoo_Attack", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Skill1", "GhostSwoo_Skill1", 0.1f, -1, -1, false); // 순간이동
	MonsterRenderer->CreateAnimation("Skill1After", "GhostSwoo_Skill1After", 0.1f, -1, -1, false); // 순간이동 후
	MonsterRenderer->CreateAnimation("Death", "GhostSwoo_Death", 0.1f, -1, -1, false);
	
	//MonsterRenderer->CreateAnimation("Skill2", "GhostSwoo_Skill2", 0.1f, -1, -1, false);
	// 볼은 따로 클래스 만드는게 나을까 생각듬
	//BallSprite = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	//BallSprite->CreateAnimation("Ball_Regen", "BounceBall_Regen", 0.1f, -1, -1, false);
	//BallSprite->CreateAnimation("Ball_Loop", "BounceBall_Loop", 0.1f, -1, -1, true);
	//BallSprite->ChangeAnimation("Ball_Regen");
	//BallSprite->AutoSpriteSizeOn();
	//BallSprite->Off();

	MonsterRenderer->SetFrameEvent("Attack", 9, [&](GameEngineSpriteRenderer*)
		{
			SwooAttackCol->On();
		}
	);
	MonsterRenderer->SetFrameEvent("Attack", 19, [&](GameEngineSpriteRenderer*)
		{
			SwooAttackCol->Off();
		}
	);

	MonsterRenderer->SetFrameEvent("Skill1", 1, [&](GameEngineSpriteRenderer*)
		{
			MonsterCollision->Off();
			SwooAttackRangeCol->Off();
		}
	);
	MonsterRenderer->SetFrameEvent("Skill1After", 6, [&](GameEngineSpriteRenderer*)
		{
			MonsterCollision->On();
			SwooAttackRangeCol->On();
		}
	);

	MonsterRenderer->ChangeAnimation("Stand");
	MonsterRenderer->AutoSpriteSizeOn();
	MonsterRenderer->SetPivotType(PivotType::Center);
	Dir = ActorDir::Right;
	MonsterRenderer->Off();

	{
		MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		MonsterCollision->Transform.SetLocalScale({ 75.0f, 130.0f });
		MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
		MonsterCollision->SetName(std::string("Boss"));
		MonsterCollision->Off();

		SwooAttackRangeCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
		SwooAttackRangeCol->Transform.SetLocalPosition({ 0.0f, 0.0f });
		SwooAttackRangeCol->Transform.SetLocalScale({ 600.0f, 250.0f });
		SwooAttackRangeCol->SetCollisionType(ColType::AABBBOX2D);
		SwooAttackRangeCol->Off();

		SwooAttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
		SwooAttackCol->Transform.SetLocalPosition({ 200.0f, 0.0f });
		SwooAttackCol->Transform.SetLocalScale({ 350.0f, 180.0f });
		SwooAttackCol->SetCollisionType(ColType::AABBBOX2D);
		SwooAttackCol->Off();
	}

	SetMoveSpeed(MoveSpeed);

	SetColPos(0, 0, 0.0f);
	//GameEngineInput::AddInputObject(this);
}

void GhostSwoo::Update(float _Delta)
{
	MonsterFunction::Update(_Delta);

	TimeCounting();

	if (Hp <= 0)
	{
		ChangeState(MonsterState::Death);
		return;
	}

	AttackEvent(_Delta);
	StateUpdate(_Delta);


	SwooAttackCol->Collision(ContentsCollisionType::Player, std::bind(&GhostSwoo::CollisionEvent, this, std::placeholders::_1));

	SwooAttackCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 20.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);
}

void GhostSwoo::CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	float4 Dir = Player::GetMainPlayer()->Transform.GetWorldPosition().X - Transform.GetWorldPosition().X;
	Dir.Normalize();

	Player::GetMainPlayer()->KnockBack(Dir, 400.0f, 400.0f, 0.8f);
}

void GhostSwoo::StandStart()
{
	DirCheck();
	ChangeAnimationState("Stand");

	MonsterCollision->On();
	SwooAttackRangeCol->On();
}

void GhostSwoo::StandUpdate(float _Delta)
{
	M_FStopTime += _Delta;
	if (M_FStopTime >= M_FStopLimitTime)
	{
		ChangeState(MonsterState::Skill1);
	}
}

void GhostSwoo::AttackStart()
{
	DirCheck();
	ChangeAnimationState("Attack");
}

void GhostSwoo::AttackUpdate(float _Delta)
{
	if (Dir == ActorDir::Right)
	{
		MonsterRenderer->Transform.SetLocalPosition({ 90.0f, 30.0f });
		SwooAttackCol->Transform.SetLocalPosition({ 90.0f, 30.0f });
	}
	else if (Dir == ActorDir::Left)
	{
		MonsterRenderer->Transform.SetLocalPosition({ -90.0f, 30.0f });
		SwooAttackCol->Transform.SetLocalPosition({ -90.0f, 30.0f });
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
		SwooAttackCol->Transform.SetLocalPosition({ 0.0f, 0.0f });
		ChangeState(MonsterState::Stand);
		return;
	}
}

void GhostSwoo::Skill_1Start()
{
	ChangeAnimationState("Skill1");
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 100.0f });
}

void GhostSwoo::Skill_1After()
{
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });

	ChangeAnimationState("Skill1After");
	DirCheck();
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	if (PlayerPos.X <= LeftCheck + 100.0f)
	{
		Transform.SetWorldPosition({ PlayerPos.X + LeftCheck + 100.0f, -650.0f });
		return;
	}
	else if (PlayerPos.X >= RightCheck)
	{
		Transform.SetWorldPosition({ RightCheck - 20.0f, -650.0f });
		return;
	}
	else
	{
		Dir = ActorDir::Left;
		MonsterRenderer->RightFlip();
		Transform.SetWorldPosition({ PlayerPos.X + 200.0f, -650.0f });
		return;
	}
}

void GhostSwoo::Skill_1AfterUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
		return;
	}
}

void GhostSwoo::DeathStart()
{
	MonsterRenderer->ChangeAnimation("Death");

	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 160.0f });

	MonsterCollision->Off();

	SwooAttackRangeCol->Off();
	SwooAttackCol->Off();
}

void GhostSwoo::DeathUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		MonsterRenderer->Off();
	}
}

void GhostSwoo::Hit(long long _Damage, bool _Attack)
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


void GhostSwoo::AttackEvent(float _Delta)
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
		SwooAttackRangeCol->CollisionEvent(ContentsCollisionType::Player, AttackRange);
	}

	if (IsAttack == true)
	{
		StartAttack += _Delta;
		if (0.5f > StartAttack)
		{
			ChangeState(MonsterState::Attack);
		}
		if (StartAttack > AttackCool)
		{
			StartAttack = 0.0f;
			IsAttack = false;
		}
	}
}


void GhostSwoo::LevelStart(GameEngineLevel* _PrevLevel)
{
	MonsterName = static_cast<int>(MonstersName::GhostSwoo);
	SummonSwoo = this;
}

void GhostSwoo::CallRegen()
{
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
	MonsterCollision->Transform.SetLocalPosition({ 0.0f, 0.0f });
	Hp = 18688692000;
	ChangeState(MonsterState::Regen);
}

void GhostSwoo::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}