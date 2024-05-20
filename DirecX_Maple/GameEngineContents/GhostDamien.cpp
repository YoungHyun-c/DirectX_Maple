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
			//MonsterCollision->Transform.SetLocalPosition({ 20.0f, 400.0f });
			//MonsterCollision->On();
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
		MonsterCollision->SetName(std::string("Boss"));
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

		ChopAttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
		ChopAttackCol->Transform.SetLocalPosition({ 0.0f, 0.0f });
		ChopAttackCol->Transform.SetLocalScale({ 400.0f, 400.0f });
		ChopAttackCol->SetCollisionType(ColType::AABBBOX2D);
		ChopAttackCol->Off();
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
}

void GhostDamien::Update(float _Delta)
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

	SlideAttackCol->Collision(ContentsCollisionType::Player, std::bind(&GhostDamien::CollisionEvent, this, std::placeholders::_1));
	SlideAttackCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 2.2f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);
	ChopAttackCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 10.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);
}

void GhostDamien::CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
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
		AttackNum += 1;
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
	if (Player::GetMainPlayer() != nullptr)
	{
		float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	}
	float4 PlayerPos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();

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
		Dir = ActorDir::Right;
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + RightColPos,
			MonsterRenderer->Transform.GetLocalPosition().Y + YColPos });
		MonsterRenderer->LeftFlip();
		Transform.SetWorldPosition({ PlayerPos.X - 200.0f, -650.0f });
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
}

void GhostDamien::Skill_2Update(float _Delta)
{
	DirCheck();
	MonsterRenderer->Transform.SetLocalPosition({ 30.0f, 200.0f });
	MonsterCollision->Transform.SetLocalPosition({ 50.0f, 0.0f });
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Skill2After);
		return;
	}
}
void GhostDamien::Skill_2After()
{
	ChangeAnimationState("Skill2After");
	if (MonsterRenderer->Transform.GetWorldPosition().X + 400.0f >= RightCheck && Dir == ActorDir::Right)
	{
		return;
	}
	if (MonsterRenderer->Transform.GetWorldPosition().X - 400.0f <= LeftCheck && Dir == ActorDir::Left)
	{
		return;
	}
	if (Dir == ActorDir::Right)
	{
		MonsterRenderer->Transform.SetLocalPosition({ 400.0f, 200.0f });
		ChopAttackCol->Transform.SetLocalPosition({ 400.0f, -50.0f });
	}
	if (Dir == ActorDir::Left)
	{
		MonsterRenderer->Transform.SetLocalPosition({ -400.0f, 200.0f });
		ChopAttackCol->Transform.SetLocalPosition({ -400.0f, -50.0f });
	}
}
void GhostDamien::Skill_2AfterUpdate(float _Delta)
{
	InsideLockMap();
	ChopAttackCol->On();
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
		MonsterCollision->Transform.SetLocalPosition({ 0.0f, 0.0f });
		AttackNum = 1;
		ChopAttackCol->Off();
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
			switch (AttackNum)
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
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
	Hp = 18688692000;
	ChangeState(MonsterState::Regen);
}

void GhostDamien::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}