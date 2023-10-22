#include "PreCompile.h"
#include "JinHillaBoss.h"
#include "Player.h"

#define TelePortX 50.0f

void JinHillaBoss::RegenUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
	}
}

void JinHillaBoss::StandStart()
{
	ChangeAnimationState("Stand");
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 120.0f });
	MonsterRenderer->On();
	MonsterCollision->Transform.SetLocalPosition({ 0.0f, 120.0f });
	MonsterCollision->On();
	JinHillaAttackRangeCol->On();
	MonsterRenderer->SetPivotType(PivotType::Center);
}

void JinHillaBoss::BossStateCheck()
{
	if (State == MonsterState::Move)
	{
		GameEngineRandom StateRandom;
		CurStateNumber = StateRandom.RandomInt(0, 2);

		switch (CurStateNumber)
		{
		case 0:
			ChangeState(MonsterState::Skill1);
			break;
		case 1:
			ChangeState(MonsterState::Move);
			break;
		default:
			break;
		}
	}
}

void JinHillaBoss::MoveStart()
{
	ChangeAnimationState("Move");
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 100.0f });
}

void JinHillaBoss::MoveUpdate(float _Delta)
{
	if (MoveDistance >= MoveLimit)
	{
		// ���� �Լ� �׽�Ʈ (�����̵�?)
		//BossStateCheck();
		ChangeState(MonsterState::Stand);
		MoveDistance = 0.0f;
		return;
	}

	DirCheck();
	float4 MovePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;

	MonsterDirX = Transform.GetWorldPosition().X;
	PlayerDirX = Player::GetMainPlayer()->GetPlayerPos().X;

	float4 CompareDir = PlayerDirX - MonsterDirX + 10.0f;
	CompareDir.Normalize();

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = float4::RIGHT;
		break;
	case ActorDir::Left:
		MoveDir = float4::LEFT;
		break;
	default:
		break;
	}

	if (Dir == ActorDir::Left)
	{
		MoveDistance += MoveSpeed * _Delta;
		MonsterRenderer->RightFlip();
		MovePos += MoveDir * -CompareDir * MoveSpeed * _Delta;
	}
	if (Dir == ActorDir::Right)
	{
		MoveDistance += MoveSpeed * _Delta;
		MonsterRenderer->LeftFlip();
		MovePos += MoveDir * CompareDir * MoveSpeed * _Delta;
	}

	Transform.AddLocalPosition(MovePos);
}

void JinHillaBoss::AttackStart()
{
	
	std::string AnimationName = "Attack";

	TestPattern += 1;
	switch (TestPattern)
	{
	case 1:
		ChangeAnimationState("Attack");
		if (Dir == ActorDir::Left)
		{
			MonsterRenderer->Transform.SetLocalPosition({ -160.0f, 140.0f });
			MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
		}
		if (Dir == ActorDir::Right)
		{
			MonsterRenderer->Transform.SetLocalPosition({ 160.0f, 140.0f });
			MonsterCollision->Transform.SetLocalPosition({ 40.0f, 120.0f });
		}
		break;
	case 2:
		ChangeAnimationState("Attack2");
		if (Dir == ActorDir::Left)
		{
			MonsterRenderer->Transform.SetLocalPosition({ -160.0f, 140.0f });
			MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
		}
		if (Dir == ActorDir::Right)
		{
			MonsterRenderer->Transform.SetLocalPosition({ 160.0f, 140.0f });
			MonsterCollision->Transform.SetLocalPosition({ 40.0f, 120.0f });
		}
		break;
	case 3:
		ChangeAnimationState("Attack3");
		if (Dir == ActorDir::Left)
		{
			MonsterRenderer->Transform.SetLocalPosition({ -330.0f, 120.0f });
			MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
		}
		if (Dir == ActorDir::Right)
		{
			MonsterRenderer->Transform.SetLocalPosition({ 330.0f, 120.0f });
			MonsterCollision->Transform.SetLocalPosition({ 40.0f, 120.0f });
		}
		break;
	case 4:
		ChangeAnimationState("Attack4");
		if (Dir == ActorDir::Left)
		{
			MonsterRenderer->Transform.SetLocalPosition({ -260.0f, 100.0f });
			MonsterCollision->Transform.SetLocalPosition({ -40.0f, 100.0f });
		}
		if (Dir == ActorDir::Right)
		{
			MonsterRenderer->Transform.SetLocalPosition({ 260.0f, 100.0f });
			MonsterCollision->Transform.SetLocalPosition({ 40.0f, 100.0f });
		}
		break;
	case 5:
		ChangeAnimationState("Attack5");
		if (Dir == ActorDir::Left)
		{
			MonsterRenderer->Transform.SetLocalPosition({ -50.0f, 120.0f });
			MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
		}
		if (Dir == ActorDir::Right)
		{
			MonsterRenderer->Transform.SetLocalPosition({ 50.0f, 120.0f });
			MonsterCollision->Transform.SetLocalPosition({ 40.0f, 120.0f });
		}
	case 6:
		ChangeAnimationState("Attack7");
		if (Dir == ActorDir::Left)
		{
			MonsterRenderer->Transform.SetLocalPosition({ -200.0f, 120.0f });
			MonsterCollision->Transform.SetLocalPosition({ -50.0f, 120.0f });
		}
		if (Dir == ActorDir::Right)
		{
			MonsterRenderer->Transform.SetLocalPosition({ 200.0f, 120.0f });
			MonsterCollision->Transform.SetLocalPosition({ 50.0f, 120.0f });
		}
		TestPattern = 0;
		break;
	default:
		break;
	}

	//ChangeAnimationState("Attack7");

	//if (Dir == ActorDir::Left)
	//{
	//	MonsterRenderer->Transform.SetLocalPosition({ -200.0f, 120.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ -50.0f, 120.0f });
	//}
	//if (Dir == ActorDir::Right)
	//{
	//	MonsterRenderer->Transform.SetLocalPosition({ 200.0f, 120.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ 50.0f, 120.0f });
	//}
}

void JinHillaBoss::AttackUpdate(float _Delta)
{
	if (JinHillaCurHp <= 0)
	{
		ChangeState(MonsterState::Death);
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Move);
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
		JinHillaCurHp -= _Damage;
	}

	if (JinHillaCurHp <= 0)
	{
		ChangeState(MonsterState::Death);
	}
}

void JinHillaBoss::CallRegen()
{
	ChangeState(MonsterState::Regen);
	MonsterRenderer->On();
	MonsterRenderer->SetPivotType(PivotType::Bottom);
}

void JinHillaBoss::Skill_1Start()
{
	ChangeAnimationState("Skill1");
}


void JinHillaBoss::DeathStart()
{
	ChangeAnimationState("Death");
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 250.0f });
}
void JinHillaBoss::DeathUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		GameEngineCore::ChangeLevel("BossRewardLevel");
	}
}