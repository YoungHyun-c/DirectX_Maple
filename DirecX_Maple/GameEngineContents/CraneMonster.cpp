#include "Precompile.h"
#include "CraneMonster.h"
#include "BackGroundMap.h"

#include "MonsterSpawnZone.h"
#include "DropItem.h"

CraneMonster::CraneMonster()
{
	MyName = static_cast<int>(MonstersName::Crane);
}

CraneMonster::~CraneMonster()
{

}

void CraneMonster::LevelStart(GameEngineLevel* _PrevLevel)
{
	//ColMap = BackGroundMap::MainMap->GetColMap();
	CurPos = Transform.GetWorldPosition();
}

void CraneMonster::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void CraneMonster::Start()
{
	SetDropItemList();
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	MonsterRenderer->CreateAnimation("Stand", "Crane_Stand", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Move", "Crane_Move", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Attack", "Crane_Attack", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Death", "Crane_Death", 0.1f, -1, -1, false);
	MonsterRenderer->ChangeAnimation("Move");
	
	MonsterRenderer->AutoSpriteSizeOn();
	MonsterRenderer->SetPivotType(PivotType::Bottom);
	MonsterRenderer->On();

	MonsterRenderer->SetFrameEvent("Attack", 6, [&](GameEngineSpriteRenderer*)
		{
			CraneSkillCol->On();
		}
	);

	MonsterRenderer->SetFrameEvent("Attack", 11, [&](GameEngineSpriteRenderer*)
		{
			CraneSkillCol->Off();
		}
	);

	{
		MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		MonsterCollision->Transform.SetLocalScale({ 100.0f, 200.0f });
		MonsterCollision->Transform.SetLocalPosition({ 0.0f, 120.0f });
		MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
		MonsterCollision->On();


		CraneAttackRangeCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterAttackRange);
		CraneAttackRangeCol->Transform.SetLocalScale({ 350.0f, 250.0f });
		CraneAttackRangeCol->Transform.SetLocalPosition({ -200.0f, 100.0f });
		CraneAttackRangeCol->SetCollisionType(ColType::AABBBOX2D);
		CraneAttackRangeCol->On();

		CraneSkillCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
		CraneSkillCol->Transform.SetLocalScale({ 350.0f, 250.0f });
		//CraneSkillCol->Transform.SetLocalPosition({ 200.0f, 100.0f });
		CraneSkillCol->SetCollisionType(ColType::AABBBOX2D);
		CraneSkillCol->Off();
	}

	Hp = 10663732800;
	SetMoveSpeed(MoveSpeed);
	ActorDir::Left;
	ChangeState(MonsterState::Spawn);
}

void CraneMonster::Update(float _Delta)
{

	//if (DeathCount == true)
	//{
	//	ChangeState(MonsterState::Spawn);
	//}

	if (DeathCount == true)
	{
		IsRegenStart += _Delta;
	}

	if (IsRegenStart >= RegenCool)
	{
		IsRegenStart = 0.0f;
		DeathCount = false;
		GetMyZone()->MonsterNumDown(static_cast<int>(MonstersName::Crane));
		Death();
	}

	if (DeathValue == true)
	{
		size_t Size = DropItemList.size();
		for (size_t i = 0; i < Size; i++)
		{
			std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
			NewItem->SetQuadraticFunction(-30.0f + (i * 50) + 5.0f, Transform.GetWorldPosition() + float4{ 0.0f, 50.0f }, 100.0f);
			NewItem->SetDropItemInfo(DropItemList[i].first, static_cast<int>(ItemType::Etc));
		}
		DeathValue = false;
		return;
	}

	StateUpdate(_Delta);

	if (Hp <= 0)
	{
		ChangeState(MonsterState::Death);
		return;
	}

	AttackEvent(_Delta);
}

void CraneMonster::Spawn(float _Delta)
{
	//if (DeathCount == true)
	//{
	//	IsRegenStart += _Delta;
	//}

	//if (IsRegenStart >= RegenCool)
	//{
	//	//ChangeState(MonsterState::Spawn);
	//	IsRegenStart = 0.0f;
	//	DeathCount = false;
	//	GetMyZone()->NumOfMonsterDown(static_cast<int>(MonstersName::Crane));
	//	Death();
	//}
	ChangeState(MonsterState::Move);
}

void CraneMonster::SetDropItemList()
{
	DropItemList.reserve(2);

	DropItemList.push_back({ "SolElda", 75 });
	DropItemList.push_back({ "SolEldaPiece", 75 });
}

void CraneMonster::StandStart()
{
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
	ChangeAnimationState("Stand");
}

void CraneMonster::StandUpdate(float _Delta)
{
	M_FStopTime += _Delta;
	if (M_FStopTime >= M_FStopLimitTime)
	{
		ChangeState(MonsterState::Move);
	}
}

void CraneMonster::MoveStart()
{
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
	ChangeAnimationState("Move");
	StateCheck();
}

void CraneMonster::MoveUpdate(float _Delta)
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

	CurPos = Transform.GetLocalPosition();

	float4 ColorPos;

	if (Dir == ActorDir::Left)
	{
		MoveDistance += MoveSpeed * _Delta;
		MonsterRenderer->RightFlip();
		CraneAttackRangeCol->Transform.SetLocalPosition({ -200.0f, 100.0f });
		MovePos += MoveDir * MoveSpeed * _Delta;
		CheckPos = CurPos + LeftCheck;
	}
	if (Dir == ActorDir::Right)
	{
		MoveDistance += MoveSpeed * _Delta;
		MonsterRenderer->LeftFlip();
		CraneAttackRangeCol->Transform.SetLocalPosition({ 200.0f, 100.0f });
		MovePos += MoveDir * MoveSpeed * _Delta;
		CheckPos = CurPos + RightCheck;
	}

	//ColorPos.Y = Transform.GetLocalPosition().Y;

	GameEngineColor Color = { 0, 0, 128, 255 };
	GameEngineColor MapColor = BackGroundMap::MainMap->GetColor(CheckPos, DefaultWallColor, GetDebugMap());

	if (Color != MapColor)
	{
		Transform.AddLocalPosition(MovePos);
	}
	if (Color == MapColor)
	{
		if (Dir == ActorDir::Right)
		{
			Dir = ActorDir::Left;
			return;
		}
		if (Dir == ActorDir::Left)
		{
			Dir = ActorDir::Right;
			return;
		}
		//return;
	}
}

void CraneMonster::AttackStart()
{
	ChangeAnimationState("Attack");
	DirCheck();

	if (Dir == ActorDir::Left)
	{
		MonsterRenderer->Transform.SetLocalPosition({ -100.0f, -50.0f });
		CraneSkillCol->Transform.SetLocalPosition({ -200.0f, 100.0f });
		MonsterCollision->Transform.SetLocalPosition({ 0.0f, 120.0f });
	}
	if (Dir == ActorDir::Right)
	{
		MonsterRenderer->Transform.SetLocalPosition({ 100.0f, -50.0f });
		CraneSkillCol->Transform.SetLocalPosition({ 200.0f, 100.0f });
		MonsterCollision->Transform.SetLocalPosition({ 0.0f, 120.0f });
	}
}

void CraneMonster::AttackUpdate(float _Delta)
{
	if (Hp <= 0)
	{
		ChangeState(MonsterState::Death);
		return;
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Move);
		return;
	}
}

void CraneMonster::DeathStart()
{
	MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
	ChangeAnimationState("Death");
	MonsterCollision->Off();
	CraneAttackRangeCol->Off();
	CraneSkillCol->Off();
	DeathCount = true;
	GlobalValue::GetMonsterValue()->AddMonsterCatchCount(1);
}

void CraneMonster::DeathUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		MonsterRenderer->Off();
		//GetMyZone()->MonsterNumDown(static_cast<int>(MonstersName::Crane));
		//Death();
	}
	
	//IsRegenStart += _Delta;
	//if (IsRegenStart > RegenCool)
	//{
	//	GetMyZone()->NumOfMonsterDown(static_cast<int>(MonstersName::Crane));
	//}
}

void CraneMonster::AttackEvent(float _Delta)
{
	EventParameter AttackRange;

	if (IsAttack == false && IsAttackStart < AttackCool)
	{
		AttackRange.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Player)
			{
				IsAttack = true;
			};
		AttackRange.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Player)
			{
				IsAttack = true;
			};
		CraneAttackRangeCol->CollisionEvent(ContentsCollisionType::Player, AttackRange);
	}

	if (IsAttack == true)
	{
		IsAttackStart += _Delta;
		if (0.5f > IsAttackStart)
		{
			ChangeState(MonsterState::Attack);
		}
		if (IsAttackStart > AttackCool)
		{
			IsAttackStart = 0.0f;
			IsAttack = false;
		}
	}
}

void CraneMonster::Hit(long long _Damage, bool _Attack)
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
		DeathValue = true;
		ChangeState(MonsterState::Death);
	}
}