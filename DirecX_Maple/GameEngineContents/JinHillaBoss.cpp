#include "PreCompile.h"
#include "JinHillaBoss.h"
#include "CravingMonster.h"
#include "Player.h"

JinHillaBoss* JinHillaBoss::MainBoss = nullptr;

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

	MonsterRenderer->CreateAnimation("Attack", "BossGreenAttack", 0.1f, -1, -1, false); // 초앞
	MonsterRenderer->CreateAnimation("Attack2", "BossPurpleAttack", 0.1f, -1, -1, true); // 보뒤
	MonsterRenderer->CreateAnimation("Attack3", "BossAttack3_Knock", 0.1f, -1, -1, false); // 파바 넉백
	MonsterRenderer->CreateAnimation("Attack4", "BossAttack4_Front", 0.1f, -1, -1, false); // 앞휘두르기
	MonsterRenderer->CreateAnimation("Attack5", "Attack5_Side", 0.1f, -1, -1, false);	   // 양옆사이드 볼
	MonsterRenderer->CreateAnimation("Attack7", "JinHilla_Attack7_Chopping", 0.1f, -1, -1, false); // 기본 낫찍기

	MonsterRenderer->CreateAnimation("Skill1", "JinHilla_Skill1_TelePort", 0.1f, -1, -1, false); //텔레포트
	MonsterRenderer->CreateAnimation("Skill1After", "JinHilla_SKill1_TeleportAfter", 0.1f, -1, -1, false); //텔포이후
	MonsterRenderer->CreateAnimation("Skill2", "JinHilla_Skill2_Animation", 0.1f, -1, -1, false); // 낫베기 패턴때
	MonsterRenderer->CreateAnimation("Skill3", "JinHilla_Skill3_Craving", 0.1f, -1, -1, false); // Craving 소환
	MonsterRenderer->CreateAnimation("Skill4", "JinHilla_Skill4_Summon", 0.1f, -1, -1, false); // 스우 데미안 소환
	
	MonsterRenderer->ChangeAnimation("Stand");
	MonsterRenderer->AutoSpriteSizeOn();
	//MonsterRenderer->SetPivotType(PivotType::Center);
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
		JinHillaAttackRangeCol->Transform.SetLocalScale({ 600.0f, 400.0f });
		JinHillaAttackRangeCol->Transform.SetLocalPosition({ 0.0f, 100.0f });
		JinHillaAttackRangeCol->SetCollisionType(ColType::AABBBOX2D);
		JinHillaAttackRangeCol->Off();
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Stand");
	JinBossScale = Sprite->GetSpriteData(0).GetScale();
	Sprite = nullptr;

	SetMoveSpeed(MoveSpeed);
	// 걸어다닐때의 콜리전 위치
	SetColPos(-20.0f, 20.0f, 0.0f);
	GameEngineInput::AddInputObject(this);
	Dir = ActorDir::Right;
}

void JinHillaBoss::Update(float _Delta)
{
	GameEngineDebug::DrawBox2D(MonsterRenderer->GetImageTransform(), float4::GREEN);
	MonsterFunction::Update(_Delta);

	if (GameEngineInput::IsDown('5', this))
	{
		ChangeState(MonsterState::Stand);
		/*MonsterRenderer->ChangeAnimation("Move");
		MonsterRenderer->Transform.SetLocalPosition({ 0.0f, 100.0f });
		MonsterRenderer->On();
		MonsterCollision->On();*/
	}
	if (GameEngineInput::IsDown('6', this))
	{
		MonsterRenderer->ChangeAnimation("Attack");
		MonsterRenderer->Transform.SetLocalPosition({ -160.0f, 140.0f });
		MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
	}
	if (GameEngineInput::IsDown('7', this))
	{
		MonsterRenderer->ChangeAnimation("Attack2");
		MonsterRenderer->Transform.SetLocalPosition({ -160.0f, 140.0f });
		MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
	}
	if (GameEngineInput::IsDown('8', this))
	{
		MonsterRenderer->ChangeAnimation("Attack3");
		MonsterRenderer->Transform.SetLocalPosition({ -330.0f, 120.0f });
		MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
	}
	if (GameEngineInput::IsDown('9', this))
	{
		MonsterRenderer->ChangeAnimation("Attack4");
		MonsterRenderer->Transform.SetLocalPosition({ -260.0f, 100.0f });
		MonsterCollision->Transform.SetLocalPosition({ -40.0f, 100.0f });
	}
	if (GameEngineInput::IsDown('0', this))
	{
		MonsterRenderer->ChangeAnimation("Attack5");
		MonsterRenderer->Transform.SetLocalPosition({ -50.0f, 120.0f });
		MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
	}


	StateUpdate(_Delta);

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

	InsideLockMap();
	AttackEvent(_Delta);
}


void JinHillaBoss::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainBoss = this;
	JinHillaCurHp = 1760000000000;
}