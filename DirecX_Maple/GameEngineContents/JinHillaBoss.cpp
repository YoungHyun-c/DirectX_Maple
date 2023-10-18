#include "PreCompile.h"
#include "JinHillaBoss.h"


JinHillaBoss::JinHillaBoss()
{

}

JinHillaBoss::~JinHillaBoss()
{

}

void JinHillaBoss::Start()
{
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	MonsterRenderer->CreateAnimation("Regen", "JinHilla_Regen", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Stand", "JinHilla_Stand", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Move", "JinHilla_Move", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Death", "JinHilla_Death", 0.1f, -1, -1, false);

	MonsterRenderer->CreateAnimation("Attack", "BossGreenAttack", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Attack2", "BossPurpleAttack", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Attack3", "BossAttack3_Knock", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Attack4", "BossAttack4_Front", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Attack5", "Attack5_Side", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Attack7", "JinHilla_Attack7_Chopping", 0.1f, -1, -1, false);

	MonsterRenderer->CreateAnimation("Skill1", "JinHilla_Skill1_Craving", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Skill2", "JinHilla_Skill2_Animation", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Skill3", "JinHilla_Skill3_TelePort", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Skill3After", "JinHilla_SKill3_TeleportAfter", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Skill4", "JinHilla_Skill4_Summon", 0.1f, -1, -1, false);
	
	MonsterRenderer->ChangeAnimation("Stand");
	MonsterRenderer->AutoSpriteSizeOn();
	MonsterRenderer->SetPivotType(PivotType::Bottom);
	MonsterRenderer->Off();
	
	TimeCounting();
	// 볼
	//MonsterRenderer->CreateAnimation("Attack6", "JinHilla_Attack6_Ball", 0.1f, -1, -1, false);

	// 공격 프레임 추가 해야됨

	//몸통
	{
		MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		MonsterCollision->Transform.SetLocalScale({ 100.0f, 200.0f });
		MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
		MonsterCollision->Off();
	}

	// 공격범위
	{
		JinHillaAttackRangeCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterAttackRange);
		JinHillaAttackRangeCol->Transform.SetLocalScale({ 400.0f, 300.0f });
		JinHillaAttackRangeCol->Transform.SetLocalPosition({ -160.0f, 200.0f });
		JinHillaAttackRangeCol->SetCollisionType(ColType::AABBBOX2D);
		JinHillaAttackRangeCol->Off();
	}

	SetMoveSpeed(MoveSpeed);
	SetColPos(-150.0f, -150.0f, 40.0f);
	GameEngineInput::AddInputObject(this);
	Dir = ActorDir::Right;
}

void JinHillaBoss::Update(float _Delta)
{
	GameEngineDebug::DrawBox2D(MonsterRenderer->GetImageTransform(), float4::GREEN);
	MonsterFunction::Update(_Delta);

	if (GameEngineInput::IsDown('5', this))
	{
		ChangeState(MonsterState::Regen);
	}
	if (GameEngineInput::IsDown('6', this))
	{
		MonsterRenderer->ChangeAnimation("Attack");
	}
	if (GameEngineInput::IsDown('7', this))
	{
		MonsterRenderer->ChangeAnimation("Attack2");
	}
	if (GameEngineInput::IsDown('8', this))
	{
		MonsterRenderer->ChangeAnimation("Attack4");
	}
	if (GameEngineInput::IsDown('9', this))
	{
		MonsterRenderer->ChangeAnimation("Attack5");
	}
	if (GameEngineInput::IsDown('0', this))
	{
		MonsterRenderer->ChangeAnimation("Attack7");
	}


	StateUpdate(_Delta);
	DirCheck();
	InsideLockMap();
	AttackEvent(_Delta);
}

void JinHillaBoss::StandStart()
{
	ChangeAnimationState("Stand");
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 170.0f });
	MonsterCollision->On();
	JinHillaAttackRangeCol->On();
	MonsterRenderer->SetPivotType(PivotType::Right);
}

void JinHillaBoss::AttackStart()
{
	ChangeAnimationState("Attack7");

	//if (Dir == ActorDir::Right)
	//{
	//	MonsterRenderer->Transform.SetLocalPosition({ 300.0f, 170.0f });
	//}

	if (Dir == ActorDir::Right)
	{
		//MonsterRenderer->SetPivotType(PivotType::Left);
	}
}

void JinHillaBoss::AttackUpdate(float _Delta)
{
	if (JinHillaHp <= 0)
	{
		ChangeState(MonsterState::Death);
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Move);
		//MonsterRenderer->SetPivotType(PivotType::Right);
	}
}

void JinHillaBoss::AttackEvent(float _Delta)
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
		JinHillaAttackRangeCol->CollisionEvent(ContentsCollisionType::Player, AttackRange);
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

void JinHillaBoss::Hit(long long _Damage, bool _Attack)
{
	if (_Attack == false)
	{
		return;
	}

	if (_Attack == true)
	{
		JinHillaHp -= _Damage;
	}

	if (JinHillaHp <= 0)
	{
		ChangeState(MonsterState::Death);
	}
}