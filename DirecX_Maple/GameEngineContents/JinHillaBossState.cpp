#include "PreCompile.h"
#include "Player.h"

#include "JinHillaBoss.h"
#include "CravingMonster.h"
#include "GhostSwoo.h"
#include "GhostDamien.h"

#define TelePortX 50.0f

void JinHillaBoss::RegenUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
		return;
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

void JinHillaBoss::StandUpdate(float _Delta)
{
	JinDirCheck();

	// 소환 몹 부르기
	CallMobDeathCheck(_Delta);

	if (CravingMob1->GetState() == (MonsterState::Max))
	{
		CallCraving1 = true;
		ChangeState(MonsterState::Skill3);

		return;
	}

	if (CravingMob2->GetState() == (MonsterState::Max))
	{
		CallCraving2 = true;
		ChangeState(MonsterState::Skill3);
		return;
	}

	if (SwooMob->GetState() == (MonsterState::Max) && Pattern >= 3)
	{
		CallSwoo = true;
		ChangeState(MonsterState::Skill3);
		return;
	}

	if (DamienMob->GetState() == (MonsterState::Max) && Pattern == 4)
	{
		CallDamien = true;
		ChangeState(MonsterState::Skill3);
		return;
	}

	M_FStopTime += _Delta;
	if (M_FStopTime >= M_FStopLimitTime)
	{
		ChangeState(MonsterState::Move);
		return;
	}
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
			return ChangeState(MonsterState::Skill1);
			break;
		case 1:
			return ChangeState(MonsterState::Move);
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
	JinDirCheck();
}

void JinHillaBoss::MoveUpdate(float _Delta)
{
	if (MoveDistance >= MoveLimit)
	{
		// 상태 함수 테스트 (순간이동?)
		BossStateCheck();
		MoveDistance = 0.0f;
		return;
	}

	// 소환 몹 부르기
	CallMobDeathCheck(_Delta);

	JinDirCheck();
	float4 MovePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;

	MonsterDirX = Transform.GetWorldPosition().X;
	PlayerDirX = Player::GetMainPlayer()->GetPlayerPos().X;

	float4 CompareDir = PlayerDirX - MonsterDirX;// -1.0f;
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
		MovePos += MoveDir * -CompareDir * MoveSpeed * _Delta;
	}
	if (Dir == ActorDir::Right)
	{
		MoveDistance += MoveSpeed * _Delta;
		MovePos += MoveDir * CompareDir * MoveSpeed * _Delta;
	}

	if (Dir == ActorDir::Right && PlayerDirX - MonsterDirX <= 100.0f)
	{
		Dir = ActorDir::Right;
		return;
	}
	if (Dir == ActorDir::Left && MonsterDirX - PlayerDirX <= 100.0f)
	{
		Dir = ActorDir::Left;
		return;
	}
	//if (CompareDir.X >= 1.0f || CompareDir.X <= -1.0f)
	{
		Transform.AddLocalPosition(MovePos);
	}
}

void JinHillaBoss::AttackStart()
{
	std::string AnimationName = "Attack";
	MonsterRenderer->SetPivotType(PivotType::Center);

	JinDirCheck();

	PatternCheckAttack();
}

void JinHillaBoss::AttackUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Move);
	}
}

void JinHillaBoss::AttackEvent(float _Delta)
{
	if (CallMob == true)
	{
		return;
	}

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
			return;
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
		return;
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
	MonsterCollision->Off();
	JinHillaAttackRangeCol->Off();
}

void JinHillaBoss::Skill_1AfterUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
		return;
	}
}



void JinHillaBoss::Skill_3Start()
{
	ChangeAnimationState("SKill3");
	CallMob = true;
}

void JinHillaBoss::Skill_3Update(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd() && CallCraving1 == true)
	{
		CravingMob1->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetWorldPosition().X + 20.0f, -760.0f });
		CravingMob1->CallRegen();
		CallCraving1 = false;

		CallMob = false;
		ChangeState(MonsterState::Stand);
		return;
	}
	if (true == MonsterRenderer->IsCurAnimationEnd() && CallCraving2 == true)
	{
		CravingMob2->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetWorldPosition().X - 20.0f, -760.0f });
		CravingMob2->CallRegen();

		CallCraving2 = false;

		CallMob = false;
		ChangeState(MonsterState::Stand);
		return;
	}

	if (true == MonsterRenderer->IsCurAnimationEnd() && CallSwoo == true && Pattern >= 3)
	{
		SwooMob->CallRegen();

		CallSwoo = false;

		CallMob = false;
		ChangeState(MonsterState::Stand);
		return;
	}

	if (true == MonsterRenderer->IsCurAnimationEnd() && CallDamien == true && Pattern == 4)
	{
		//DamienMob->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetWorldPosition().X - 150.0f, -650.0f });
		DamienMob->CallRegen();

		CallDamien = false;

		CallMob = false;
		ChangeState(MonsterState::Stand);
		return;
	}
}

void JinHillaBoss::CallMobDeathCheck(float _Delta)
{
	if (CravingMob1->GetState() == (MonsterState::Death))
	{
		Craving1DeathTime += _Delta;
		if (Craving1DeathTime > DeathLimitTime && IsAttack == false)
		{
			Craving1DeathTime = 0.0f;
			CallCraving1 = true;
			ChangeState(MonsterState::Skill3);
			return;
		}
	}

	if (CravingMob2->GetState() == (MonsterState::Death))
	{
		Craving2DeathTime += _Delta;
		if (Craving2DeathTime > DeathLimitTime && IsAttack == false)
		{
			Craving2DeathTime = 0.0f;
			CallCraving2 = true;
			ChangeState(MonsterState::Skill3);
			return;
		}
	}

	if (SwooMob->GetState() == (MonsterState::Death))
	{
		SwooDeathTime += _Delta;
		if (SwooDeathTime > DeathLimitTime && IsAttack == false)
		{
			SwooDeathTime = 0.0f;
			CallSwoo = true;
			ChangeState(MonsterState::Skill3);
			return;
		}
	}

	if (DamienMob->GetState() == (MonsterState::Death))
	{
		DamienDeathTime += _Delta;
		if (DamienDeathTime > DeathLimitTime && IsAttack == false)
		{
			DamienDeathTime = 0.0f;
			CallDamien = true;
			ChangeState(MonsterState::Skill3);
			return;
		}
	}
}

void JinHillaBoss::DeathStart()
{
	ChangeAnimationState("Death");
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 250.0f });
	MonsterCollision->Off();
	GameEngineSound::SoundPlay("Die.mp3");
}
void JinHillaBoss::DeathUpdate(float _Delta)
{

}

void JinHillaBoss::PatternCheckAttack()
{
	if (Pattern == 1)
	{
		switch (TestPattern)
		{
		case 1:
			ChangeAnimationState("Attack3");
			if (Dir == ActorDir::Left)
			{
				MonsterRenderer->Transform.SetLocalPosition({ -330.0f, 120.0f });
				MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });

				JinHillBindSkillCol->Transform.SetLocalPosition({ -350.0f, 100.0f });
				JinHillKnockSkillCol->Transform.SetLocalPosition({ -350.0f, 100.0f });
			}
			if (Dir == ActorDir::Right)
			{
				MonsterRenderer->Transform.SetLocalPosition({ 330.0f, 120.0f });
				MonsterCollision->Transform.SetLocalPosition({ 40.0f, 120.0f });

				JinHillBindSkillCol->Transform.SetLocalPosition({ 350.0f, 100.0f });
				JinHillKnockSkillCol->Transform.SetLocalPosition({ 350.0f, 100.0f });
			}
			TestPattern += 1;
			break;
		case 2:
			ChangeAnimationState("Attack4");
			if (Dir == ActorDir::Left)
			{
				MonsterRenderer->Transform.SetLocalPosition({ -260.0f, 100.0f });
				MonsterCollision->Transform.SetLocalPosition({ -40.0f, 100.0f });

				JinHillFrontSlapSkillCol->Transform.SetLocalPosition({ -250.0f, 50.0f });
			}
			if (Dir == ActorDir::Right)
			{
				MonsterRenderer->Transform.SetLocalPosition({ 260.0f, 100.0f });
				MonsterCollision->Transform.SetLocalPosition({ 40.0f, 100.0f });

				JinHillFrontSlapSkillCol->Transform.SetLocalPosition({ 250.0f, 50.0f });
			}
			TestPattern += 1;
			break;
		case 3:
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
			TestPattern = 1;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (TestPattern)
		{
		case 1:
			ChangeAnimationState("Attack");
			AnimationName = "Attack";

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
			TestPattern += 1;
			break;
		case 2:
			ChangeAnimationState("Attack2");
			AnimationName = "Attack2";
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
			TestPattern += 1;
			break;
		case 3:
			ChangeAnimationState("Attack3");
			if (Dir == ActorDir::Left)
			{
				MonsterRenderer->Transform.SetLocalPosition({ -330.0f, 120.0f });
				MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });

				JinHillBindSkillCol->Transform.SetLocalPosition({ -350.0f, 100.0f });
				JinHillKnockSkillCol->Transform.SetLocalPosition({ -350.0f, 100.0f });
			}
			if (Dir == ActorDir::Right)
			{
				MonsterRenderer->Transform.SetLocalPosition({ 330.0f, 120.0f });
				MonsterCollision->Transform.SetLocalPosition({ 40.0f, 120.0f });

				JinHillBindSkillCol->Transform.SetLocalPosition({ 350.0f, 100.0f });
				JinHillKnockSkillCol->Transform.SetLocalPosition({ 350.0f, 100.0f });
			}
			TestPattern += 1;
			break;
		case 4:
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
			TestPattern = 1;
			break;
		default:
			break;
		}
	}
}