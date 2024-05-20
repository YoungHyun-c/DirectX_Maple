#include "PreCompile.h"
#include "CravingMonster.h"

#include "Player.h"

CravingMonster* CravingMonster::CravingMonsters;

CravingMonster::CravingMonster()
{

}

CravingMonster::~CravingMonster()
{

}


void CravingMonster::Start()
{
	{
		if (nullptr == GameEngineSprite::Find("Craving"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("FolderTexture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("Craving");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}

	TimeCounting();
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	MonsterRenderer->CreateAnimation("Regen", "Craving_Regen", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Stand", "Craving_Stand", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Move", "Craving_Move", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Attack", "Craving_Attack", 0.08f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Die", "Craving_Die", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Dieing", "Craving_Dieing", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Awake", "Craving_Awake", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Death", "Craving_Death", 0.1f, -1, -1, false);

	// 공격프레임
	MonsterRenderer->SetFrameEvent("Attack", 11, [&](GameEngineSpriteRenderer*)
		{
			CravingSkillCol->On();
		}
	);
	MonsterRenderer->SetFrameEvent("Attack", 18, [&](GameEngineSpriteRenderer*)
		{
			CravingSkillCol->Off();
		}
	);

	MonsterRenderer->ChangeAnimation("Stand");
	MonsterRenderer->AutoSpriteSizeOn();
	MonsterRenderer->SetPivotType(PivotType::Bottom);
	MonsterRenderer->Off();

	{
		MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Craving);
		MonsterCollision->Transform.SetLocalScale({ 90.0f, 200.0f });
		MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
		MonsterCollision->Off();

		CravingSkillCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
		CravingSkillCol->Transform.SetLocalScale({ 350.0f, 270.0f });
		CravingSkillCol->Transform.SetLocalPosition({ 0.0f, 120.0f });
		CravingSkillCol->SetCollisionType(ColType::AABBBOX2D);
		CravingSkillCol->Off();

		CravingDieCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		CravingDieCol->Transform.SetLocalScale({ 110.0f, 70.0f });
		CravingDieCol->Transform.SetLocalPosition({ 0.0f, 50.0f });
		CravingDieCol->SetCollisionType(ColType::AABBBOX2D);
		CravingDieCol->SetName(std::string("CravingDiebody"));
		CravingDieCol->Off();

		CravingAttackRangeCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterAttackRange);
		CravingAttackRangeCol->Transform.SetLocalScale({ 400.0f, 300.0f });
		CravingAttackRangeCol->Transform.SetLocalPosition({ 0.0f, 120.0f });
		CravingAttackRangeCol->SetCollisionType(ColType::AABBBOX2D);
		CravingAttackRangeCol->Off();
	}

	SetMoveSpeed(MoveSpeed);
	SetColPos(-10.0f, 40.0f, 120.0f);
	GameEngineInput::AddInputObject(this);
	ActorDir::Left;
}

void CravingMonster::Update(float _Delta)
{
	//MonsterFunction::Update(_Delta);

	CravingSkillCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 20.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);

	CravingDieCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 10.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);

	AttackEvent(_Delta);
	TimeCounting();
	DirCheck();
	
	StateUpdate(_Delta);
	InsideLockMap();
}

void CravingMonster::StandStart()
{
	Hp = 10000000;
	ChangeAnimationState("Stand");
	CravingAttackRangeCol->On();
	MonsterCollision->On();
}

void CravingMonster::DieStart()
{
	DeathCount -= 1;
	ChangeAnimationState("DIe");
	CravingAttackRangeCol->Off();
	MonsterCollision->Off();
}

void CravingMonster::DieingStart()
{
	CravingDieCol->On();
	CravingSkillCol->Off();
}

void CravingMonster::DieingEnd()
{
	CravingDieCol->Off();
}

void CravingMonster::DeathStart()
{
	ChangeAnimationState("Death");
	CravingSkillCol->Off();
	CravingAttackRangeCol->Off();
	MonsterCollision->Off();
}

void CravingMonster::DeathUpdate(float _Delta)
{
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		MonsterRenderer->Off();
		CravingAttackRangeCol->Off();
	}
}

void CravingMonster::AttackUpdate(float _Delta)
{
	if (Hp <= 0)
	{
		CravingSkillCol->Off();
		ChangeState(MonsterState::Die);
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Move);
	}
}


void CravingMonster::AttackEvent(float _Delta)
{
	EventParameter AttackRange;

	if (IsAttack == false && AttackStart < AttackCool)
	{
		AttackRange.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Player)
			{
				IsAttack = true;
			};
		AttackRange.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Player)
			{
				IsAttack = true;
			};
		CravingAttackRangeCol->CollisionEvent(ContentsCollisionType::Player, AttackRange);
	}

	if (IsAttack == true)
	{
		AttackStart += _Delta;
		if (0.5f > AttackStart)
		{
			ChangeState(MonsterState::Attack);
		}
		if (AttackStart > AttackCool)
		{
			AttackStart = 0.0f;
			IsAttack = false;
		}
	}
}

void CravingMonster::Hit(long long _Damage, bool _Attack)
{
	if (_Attack == false)
	{
		return;
	}

	if (_Attack == true)
	{
		Hp -= _Damage;
	}

	if (DeathCount <= 0)
	{
		CravingSkillCol->Off();
		ChangeState(MonsterState::Death);
		return;
	}

	if (Hp <= 0 && CurState != MonsterState::Die)
	{
		ChangeState(MonsterState::Die);
		return;
	}
}

void CravingMonster::CallRegen()
{
	DeathCount = 3;
	ChangeState(MonsterState::Regen);
}

void CravingMonster::CallDie()
{
	ChangeState(MonsterState::Die);
}

void CravingMonster::LevelStart(GameEngineLevel* PrevLevel)
{
	MonsterName = static_cast<int>(MonstersName::CarvingMonster);
}
void CravingMonster::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}