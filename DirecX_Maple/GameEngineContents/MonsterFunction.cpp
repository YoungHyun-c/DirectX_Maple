#include "PreCompile.h"
#include "MonsterFunction.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "BackGroundMap.h"

MonsterFunction* MonsterFunction::MonsterFunc;

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
	if (M_FStopTime >= M_FStopLimiTime)
	{
		ChangeState(MonsterState::Move);
		M_FStopTime = 0.0f;
	}
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

	float4 MovePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;

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
		//MonsterRenderer->Transform.AddLocalPosition({ -MoveSpeed * _Delta, });
		MoveDistance += MoveSpeed * _Delta;
		MonsterRenderer->RightFlip();
		MovePos += MoveDir * MoveSpeed * _Delta;
	}
	if (Dir == ActorDir::Right)
	{
		//MonsterRenderer->Transform.AddLocalPosition({ MoveSpeed * _Delta, });
		MoveDistance += MoveSpeed * _Delta;
		MonsterRenderer->LeftFlip();
		MovePos += MoveDir * MoveSpeed * _Delta;
	}

	Transform.AddLocalPosition(MovePos);



	//float4 CurPos = Transform.GetLocalPosition();
	//float4 CurColorPos = (float4{ CurPos.X, CurPos.Y });
	//GameEngineColor CurColor = DebugMap->GetColor( static_cast<int>(CurColorPos.X), static_cast<int>(CurColorPos.Y) , DefaultGroundColor);
	//if (Dir == ActorDir::Left)
	//{
	//	//MonsterRenderer->Transform.AddLocalPosition({ -MoveSpeed * _Delta, });
	//	NextPos = Transform.GetLocalPosition() + (-MoveSpeed * _Delta, 0);
	//	//NextPos = (LeftCheck -MoveSpeed * _Delta, 0);
	//}
	//if (Dir == ActorDir::Right)
	//{
	//	NextPos = Transform.GetLocalPosition() + (MoveSpeed * _Delta, 0);
	//	//NextPos = (RightCheck + MoveSpeed * _Delta, 0);
	//}
	////float4 NextPos = Transform.GetLocalPosition() + ( * MoveSpeed * _Delta , 0 );
	//float4 NextColorPos = CurColorPos + ( NextPos.X, NextPos.Y );
	//GameEngineColor NextColor = DebugMap->GetColor( NextColorPos.X,NextColorPos.Y , DefaultGroundColor);


	//if (CurColor == GameEngineColor::RED)
	//{
	//	float4 CopyNextColorPos = NextColorPos;
	//	GameEngineColor CopyNextColor = NextColor;

	//	int DownCount = 0;

	//	while (CopyNextColor == GameEngineColor::RED)
	//	{
	//		MoveDistance += MoveSpeed * _Delta;
	//		//CopyNextColorPos.X++;
	//		Transform.SetLocalPosition(NextPos);
	//		CopyNextColor = DebugMap->GetColor(static_cast<int>(CopyNextColorPos.X), static_cast<int>(CopyNextColorPos.Y), DefaultGroundColor);
	//		DownCount++;

	//		if (DownCount >= 10)
	//		{
	//			return;
	//		}
	//	}

	//	if (DownCount < 10)
	//	{
	//		return;
	//	}
	//}

	//float4 MovePos = float4::ZERO;
	//float4 MoveDir = float4::ZERO;

	//switch (Dir)
	//{
	//case ActorDir::Right:
	//	MoveDir = float4::RIGHT;
	//	break;
	//case ActorDir::Left:
	//	MoveDir = float4::LEFT;
	//	break;
	//default:
	//	break;
	//}

	//if (Dir == ActorDir::Left)
	//{
	//	MoveDistance += MoveSpeed * _Delta;
	//	MovePos += MoveDir * MoveSpeed * _Delta;
	//	NextPos = Transform.GetLocalPosition() + LeftCheck;
	//}
	//if (Dir == ActorDir::Right)
	//{
	//	MoveDistance += MoveSpeed * _Delta;
	//	MovePos += MoveDir * MoveSpeed * _Delta;
	//	NextPos = Transform.GetLocalPosition()+ RightCheck;
	//}

	//CheckColor = CheckSideColor(NextPos);
	//
	//if (DefaultGroundColor == CheckColor)
	//{
	//	if (Dir == ActorDir::Left)
	//	{
	//		Dir = ActorDir::Right;
	//	}
	//	else if (Dir == ActorDir::Right)
	//	{
	//		Dir = ActorDir::Left;
	//	}
	//}
	//Transform.AddLocalPosition(MovePos);
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

}
void MonsterFunction::DieingStart()
{
	ChangeAnimationState("Dieing");
}
void MonsterFunction::DieingUpdate(float _Delta)
{

}
void MonsterFunction::AwakeStart()
{
	ChangeAnimationState("Awake");
}
void MonsterFunction::AwakeUpdate(float _Delta)
{

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
	//else if (State == MonsterState::Stand || State == MonsterState::Hit)
	//{
	//	GameEngineRandom StateRandom;
	//	CurStateNumber = StateRandom.RandomInt(0, 2);

	//	switch (CurStateNumber)
	//	{
	//	case 0:
	//		Dir = ActorDir::Left;
	//		ChangeAnimationState("Move");
	//		break;
	//	case 1:
	//		Dir = ActorDir::Right;
	//		ChangeAnimationState("Move");
	//		break;
	//	case 2:
	//		State = MonsterState::Stand;
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

void MonsterFunction::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
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
	GameEngineColor CheckColor = BackGroundMap::MainMap->GetColor(Transform.GetWorldPosition() + CheckPos, GameEngineColor::White, DebugMapName);
	return CheckColor;
}

void MonsterFunction::DirCheck()
{
	if (Dir == ActorDir::Left)
	{
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + LeftColPos,
			MonsterRenderer->Transform.GetLocalPosition().Y + YColPos });
	}
	else if (Dir == ActorDir::Right)
	{
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + RightColPos,
			MonsterRenderer->Transform.GetLocalPosition().Y + YColPos });
	}
}

void MonsterFunction::InsideLockMap()
{
	GlobalValue::CurMonsterPos = MonsterRenderer->Transform.GetWorldPosition();

	if (Transform.GetWorldPosition().X < LeftCheck)
	{
		GlobalValue::CurMonsterPos.X + 100.0f;
		Dir = ActorDir::Right;
		ChangeState(MonsterState::Move);
	}
	else if (Transform.GetWorldPosition().X > RightCheck)
	{
		GlobalValue::CurMonsterPos.X - 200.0f;
		Dir = ActorDir::Left;
		ChangeState(MonsterState::Move);
	}
}