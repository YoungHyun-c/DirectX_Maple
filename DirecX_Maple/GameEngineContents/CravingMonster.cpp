#include "PreCompile.h"
#include "CravingMonster.h"

std::list<CravingMonster*> CravingMonster::CravingMonsters;

CravingMonster::CravingMonster()
{
	MonsterName = static_cast<int>(MonstersName::CarvingMonster);
	CravingMonsters.push_back(this);
}

CravingMonster::~CravingMonster()
{

}


void CravingMonster::Start()
{
	//CravingMob = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	//CravingMob->CreateAnimation("Craving_Regen", "Craving_Regen", 0.1f, -1, -1, false);
	//CravingMob->CreateAnimation("Craving_Stand", "Craving_Stand", 0.1f, -1, -1, true);
	//CravingMob->CreateAnimation("Craving_Move", "Craving_Move", 0.1f, -1, -1, true);
	//CravingMob->CreateAnimation("Craving_Attack", "Craving_Attack", 0.1f, -1, -1, false);
	//CravingMob->CreateAnimation("Craving_Die", "Craving_Die", 0.1f, -1, -1, false);
	//CravingMob->CreateAnimation("Craving_Dieing", "Craving_Dieing", 0.1f, -1, -1, true);
	//CravingMob->CreateAnimation("Craving_Awake", "Craving_Awake", 0.1f, -1, -1, false);
	//CravingMob->CreateAnimation("Craving_Death", "Craving_Death", 0.1f, -1, -1, false);

	//CravingMob->ChangeAnimation("Craving_Regen");
	//CravingMob->AutoSpriteSizeOn();
	//CravingMob->SetPivotType(PivotType::Bottom);
	//CravingMob->Off();

	TimeCounting();

	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	MonsterRenderer->CreateAnimation("Regen", "Craving_Regen", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Stand", "Craving_Stand", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Move", "Craving_Move", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Attack", "Craving_Attack", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Die", "Craving_Die", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Dieing", "Craving_Dieing", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Awake", "Craving_Awake", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Death", "Craving_Death", 0.1f, -1, -1, false);

	MonsterRenderer->ChangeAnimation("Regen");
	MonsterRenderer->AutoSpriteSizeOn();
	MonsterRenderer->SetPivotType(PivotType::Bottom);
	MonsterRenderer->Off();

	MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
	MonsterCollision->Transform.SetLocalScale({ 90.0f, 200.0f });
	//MonsterCollision->Transform.SetLocalPosition({ 0.0f, 100.0f, 1.0f });
	MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
	MonsterCollision->Off();

	SetMoveSpeed(MoveSpeed);

	ActorDir::Left;
}

void CravingMonster::Update(float _Delta)
{
	//StateUpdate(_Delta);

	MonsterFunction::Update(_Delta);


	if (GameEngineInput::IsDown('5'))
	{
		MonsterRenderer->On();
		MonsterCollision->On();
		ChangeState(MonsterState::Regen);
	}
	if (GameEngineInput::IsDown('6'))
	{
		ChangeState(MonsterState::Attack);
	}
	if (GameEngineInput::IsDown('7'))
	{
		ChangeState(MonsterState::Die);
	}
	if (GameEngineInput::IsDown('8'))
	{
		ChangeState(MonsterState::Awake);
	}
	if (GameEngineInput::IsDown('9'))
	{
		ChangeState(MonsterState::Dieing);
	}

	if (GameEngineInput::IsDown('0'))
	{
		ChangeState(MonsterState::Death);
	}

	TimeCounting();
	StateUpdate(_Delta);

	//MonsterRenderer->Transform.SetLocalPosition(MonsterRenderer->Transform.GetLocalPosition());
	if (Dir == ActorDir::Left)
	{
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X - 10.0f,
			MonsterRenderer->Transform.GetLocalPosition().Y + 120.0f});
	}
	else if (Dir == ActorDir::Right)
	{
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + 40.0f,
	MonsterRenderer->Transform.GetLocalPosition().Y + 120.0f });
	}

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

	int a = 0;
}
//
//void CravingMonster::ChangeState(CravingState _State)
//{
//	if (_State != State)
//	{
//		switch (_State)
//		{
//		case CravingState::Regen:
//			RegenStart();
//			break;
//		case CravingState::Stand:
//			StandStart();
//			break;
//		case CravingState::Move:
//			MoveStart();
//			break;
//		case CravingState::Attack:
//			AttackStart();
//			break;
//		case CravingState::Die:
//			DieStart();
//			break;
//		case CravingState::Dieing:
//			DieingStart();
//			break;
//		case CravingState::Awake:
//			AwakeStart();
//			break;
//		case CravingState::Death:
//			DeathStart();
//			break;
//		default:
//			break;
//		}
//	}
//
//	State = _State;
//}
//
//void CravingMonster::StateUpdate(float _Delta)
//{
//	switch (State)
//	{
//	case CravingState::Regen:
//		return RegenUpdate(_Delta);
//	case CravingState::Stand:
//		return StandUpdate(_Delta);
//	case CravingState::Move:
//		return MoveUpdate(_Delta);
//	case CravingState::Attack:
//		return AttackUpdate(_Delta);
//	case CravingState::Die:
//		return DieUpdate(_Delta);
//	case CravingState::Dieing:
//		return DieingUpdate(_Delta);
//	case CravingState::Awake:
//		return AwakeUpdate(_Delta);
//	case CravingState::Death:
//		return DeathUpdate(_Delta);
//	case CravingState::Max:
//		break;
//	default:
//		break;
//	}
//}
//void CravingMonster::RegenStart()
//{
//	ChangeAnimationState("Craving_Regen");
//}
//void CravingMonster::RegenUpdate(float _Delta)
//{
//	if(true == CravingMob->IsCurAnimationEnd())
//	{
//		ChangeState(CravingState::Stand);
//	}
//}
//void CravingMonster::StandStart()
//{
//	ChangeAnimationState("Craving_Stand");
//}
//void CravingMonster::StandUpdate(float _Delta)
//{
//	M_FStopTime += _Delta;
//	if (M_FStopTime >= M_FStopLimiTime)
//	{
//		ChangeState(CravingState::Move);
//		M_FStopTime = 0.0f;
//	}
//}
//void CravingMonster::MoveStart()
//{
//	GameEngineRandom NewRandom;
//	idx = NewRandom.RandomInt(0, 2);
//	Dir = idx ? ActorDir::Left : ActorDir::Right;
//
//	ChangeAnimationState("Craving_Move");
//}
//void CravingMonster::MoveUpdate(float _Delta)
//{
//	M_FMoveTime += _Delta;
//
//	if (Dir == ActorDir::Left)
//	{
//		CravingMob->Transform.AddLocalPosition({ -MoveSpeed * _Delta, });
//		CravingMob->RightFlip();
//	}
//	if (Dir == ActorDir::Right)
//	{
//		CravingMob->Transform.AddLocalPosition({ MoveSpeed * _Delta, });
//		CravingMob->LeftFlip();
//	}
//
//	if (M_FMoveTime >= M_FMoveLinitTime)
//	{
//		M_FMoveTime = 0.0f;
//		ChangeState(CravingState::Stand);
//	}
//}
//void CravingMonster::AttackStart()
//{
//	ChangeAnimationState("Craving_Attack");
//}
//void CravingMonster::AttackUpdate(float _Delta)
//{
//
//}
//void CravingMonster::DieStart()
//{
//	ChangeAnimationState("Craving_Die");
//}
//void CravingMonster::DieUpdate(float _Delta)
//{
//
//}
//void CravingMonster::DieingStart()
//{
//	ChangeAnimationState("Craving_Dieing");
//}
//void CravingMonster::DieingUpdate(float _Delta)
//{
//
//}
//void CravingMonster::AwakeStart()
//{
//	ChangeAnimationState("Craving_Awake");
//}
//void CravingMonster::AwakeUpdate(float _Delta)
//{
//
//}
//void CravingMonster::DeathStart()
//{
//	ChangeAnimationState("Craving_Death");
//}
//
void CravingMonster::DeathUpdate(float _Delta)
{

}
//
//void CravingMonster::ChangeAnimationState(const std::string& _StateName)
//{
//	AnimationName = _StateName;
//
//	CravingMob->ChangeAnimation(AnimationName);
//}