#include "PreCompile.h"
#include "MonsterFunction.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "BackGroundMap.h"
#include "Player.h"

MonsterFunction* MonsterFunction::MonsterFunc = nullptr;

MonsterFunction::MonsterFunction()
{
	MonsterFunc = this;
}

MonsterFunction::~MonsterFunction()
{

}


// 몬스터 행동 관련
void MonsterFunction::RegenStart()
{
	ChangeAnimationState("Regen");
	MonsterRenderer->On();
}
void MonsterFunction::RegenUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
	}
}

void MonsterFunction::StandStart()
{
	ChangeAnimationState("Stand");
}
void MonsterFunction::StandUpdate(float _Delta)
{
	M_FStopTime += _Delta;
	if (M_FStopTime >= M_FStopLimitTime)
	{
		ChangeState(MonsterState::Move);
	}
}
void MonsterFunction::StandEnd()
{
	M_FStopTime = 0.0f;
}

void MonsterFunction::MoveStart()
{
	ChangeAnimationState("Move");
}

void MonsterFunction::MoveUpdate(float _Delta)
{
	if (MoveDistance >= MoveLimitDistance)
	{
		StateCheck();
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


void MonsterFunction::AttackStart()
{
	ChangeAnimationState("Attack");
}
void MonsterFunction::AttackUpdate(float _Delta)
{

}
void MonsterFunction::DieStart()
{
	ChangeAnimationState("Die");
}
void MonsterFunction::DieUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Dieing);
	}
}
void MonsterFunction::DieingStart()
{
	ChangeAnimationState("Dieing");
}
void MonsterFunction::DieingUpdate(float _Delta)
{
	M_DieingTime += _Delta;
	if (M_DieingTime >= M_DieingLimitTime)
	{
		ChangeState(MonsterState::Awake);
		M_DieingTime = 0.0f;
	}
}
void MonsterFunction::DieingEnd()
{

}

void MonsterFunction::AwakeStart()
{
	ChangeAnimationState("Awake");
}
void MonsterFunction::AwakeUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
	}
}
void MonsterFunction::DeathStart()
{
	ChangeAnimationState("Death");
}

void MonsterFunction::DeathUpdate(float _Delta)
{

}

void MonsterFunction::Skill_1Start()
{
	ChangeAnimationState("Skill1");
}

void MonsterFunction::Skill_1Update(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		M_DisappearTime += _Delta;
	}
	if (M_DisappearTime >= M_AppearTime)
	{
		M_DisappearTime = 0.0f;
		ChangeState(MonsterState::Skill1After);
		return;
	}
}

void MonsterFunction::Skill_1After()
{
	ChangeAnimationState("Skill1After");
	float4 TestPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	if (TestPos.X <= LeftCheck)
	{
		Transform.SetWorldPosition({ TestPos.X + LeftCheck, -700.0f });
		return;
	}
	else if (TestPos.X >= RightCheck)
	{
		Transform.SetWorldPosition({ RightCheck - 20.0f, -700.0f });
		return;
	}
	else
	{
		Transform.SetWorldPosition({ TestPos.X, -700.0f });
	}
}

void MonsterFunction::Skill_1AfterUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Stand);
	}
}

void MonsterFunction::Skill_2Start()
{
	ChangeAnimationState("Skill2");
}

void MonsterFunction::Skill_2Update(float _Delta)
{

}


// 몬스터 상태관련
void MonsterFunction::StateCheck()
{
	if (State == MonsterState::Move)
	{
		//MoveDistance = 0.0f;
		
		GameEngineRandom StateRandom;
		CurStateNumber = StateRandom.RandomInt(0, 2);

		switch (CurStateNumber)
		{
		case 0:
			Dir = ActorDir::Left;
			ChangeState(MonsterState::Move);
			break;
		case 1:
			Dir = ActorDir::Right;
			ChangeState(MonsterState::Move);
			break;
		case 2:
			ChangeState(MonsterState::Stand);
			break;
		default:
			break;
		}
	}
}

void MonsterFunction::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		switch (State)
		{
		case MonsterState::Stand:
			StandEnd();
			break;
		case MonsterState::Dieing:
			DieingEnd();
			break;
		//case MonsterState::Skill1:
		//	Skill_1End();
			break;
		default:
			break;
		}

		switch (_State)
		{
		case MonsterState::Regen:
			RegenStart();
			break;
		case MonsterState::Stand:
			StandStart();
			break;
		case MonsterState::Move:
			MoveStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		case MonsterState::Skill1:
			Skill_1Start();
			break;
		case MonsterState::Skill1After:
			Skill_1After();
			break;
		case MonsterState::Skill2:
			Skill_2Start();
			break;
		case MonsterState::Die:
			DieStart();
			break;
		case MonsterState::Dieing:
			DieingStart();
			break;
		case MonsterState::Awake:
			AwakeStart();
			break;
		case MonsterState::Death:
			DeathStart();
			break;
		case MonsterState::Max:
			break;
		default:
			break;
		}
	}

	State = _State;
}

void MonsterFunction::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Regen:
		return RegenUpdate(_Delta);
	case MonsterState::Stand:
		return StandUpdate(_Delta);
	case MonsterState::Move:
		return MoveUpdate(_Delta);
	case MonsterState::Attack:
		return AttackUpdate(_Delta);
	case MonsterState::Skill1:
		return Skill_1Update(_Delta);
	case MonsterState::Skill1After:
		return Skill_1AfterUpdate(_Delta);
	case MonsterState::Skill2:
		return Skill_2Update(_Delta);
	case MonsterState::Die:
		return DieUpdate(_Delta);
	case MonsterState::Dieing:
		return DieingUpdate(_Delta);
	case MonsterState::Awake:
		return AwakeUpdate(_Delta);
	case MonsterState::Death:
		return DeathUpdate(_Delta);
	case MonsterState::Max:
		break;
	default:
		break;
	}
}


void MonsterFunction::ChangeAnimationState(const std::string& _StateName)
{
	AnimationName = _StateName;

	MonsterRenderer->ChangeAnimation(AnimationName);
}


void MonsterFunction::TimeCounting()
{
	CurTime = static_cast<float>(clock());
	TimeCount = (CurTime - PrevTime) / 1000.0f;
	PrevTime = CurTime;
}

void MonsterFunction::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurMapScale = BackGroundMap::MainMap->GetMapScale();
}

GameEngineColor MonsterFunction::CheckSideColor(float4 CheckPos)
{
	GameEngineColor CheckColor = BackGroundMap::MainMap->GetColor(Transform.GetWorldPosition() + CheckPos, GameEngineColor::WHITE, DebugMapName);
	return CheckColor;
}

void MonsterFunction::DirCheck()
{
	PlayerDirX = Player::GetMainPlayer()->Transform.GetWorldPosition().X;
	MonsterDirX = MonsterRenderer->Transform.GetWorldPosition().X;
	
	if (PlayerDirX > MonsterDirX)
	{
		Dir = ActorDir::Right;
	}
	if (PlayerDirX < MonsterDirX)
	{
		Dir = ActorDir::Left;
	}
	if (Dir == ActorDir::Left)
	{
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + LeftColPos,
			MonsterRenderer->Transform.GetLocalPosition().Y + YColPos });
		return;
	}
	else if (Dir == ActorDir::Right)
	{
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + RightColPos,
			MonsterRenderer->Transform.GetLocalPosition().Y + YColPos });
		return;
	}
}

void MonsterFunction::InsideLockMap()
{
	GlobalValue::CurMonsterPos = MonsterRenderer->Transform.GetWorldPosition();
	MonsterPos = MonsterRenderer->Transform.GetWorldPosition();
	if (Transform.GetWorldPosition().X < LeftCheck)
	{
		MonsterRenderer->Transform.SetLocalPosition(MonsterPos.X + 100.0f);
		Dir = ActorDir::Right;
		ChangeState(MonsterState::Move);
	}
	else if (Transform.GetWorldPosition().X > RightCheck)
	{
		MonsterRenderer->Transform.SetLocalPosition(MonsterPos.X - 200.0f);
		Dir = ActorDir::Left;
		ChangeState(MonsterState::Move);
	}
}