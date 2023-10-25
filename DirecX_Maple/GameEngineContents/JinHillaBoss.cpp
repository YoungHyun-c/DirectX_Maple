#include "PreCompile.h"
#include "JinHillaBoss.h"
#include "CravingMonster.h"
#include "Player.h"

#include "BossSkillEffect.h"

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

	// 공격스킬 충돌 콜리전
	{
		JinHillBindSkillCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterAttackRange);
		JinHillBindSkillCol->Transform.SetLocalPosition({ 0.0f, 100.0f });
		JinHillBindSkillCol->Transform.SetLocalScale({ 600.0f, 400.0f });
		JinHillBindSkillCol->SetCollisionType(ColType::AABBBOX2D);
		JinHillBindSkillCol->Off();

		JinHillKnockSkillCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterAttackRange);
		JinHillKnockSkillCol->Transform.SetLocalPosition({ 0.0f, 100.0f });
		JinHillKnockSkillCol->Transform.SetLocalScale({ 600.0f, 400.0f });
		JinHillKnockSkillCol->SetCollisionType(ColType::AABBBOX2D);
		JinHillKnockSkillCol->Off();

		JinHillFrontSlapSkillCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterAttackRange);
		JinHillFrontSlapSkillCol->Transform.SetLocalPosition({ 0.0f, 100.0f });
		JinHillFrontSlapSkillCol->Transform.SetLocalScale({ 400.0f, 200.0f });
		JinHillFrontSlapSkillCol->SetCollisionType(ColType::AABBBOX2D);
		JinHillFrontSlapSkillCol->Off();

		JinHillSideSlapSkillCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterAttackRange);
		JinHillSideSlapSkillCol->Transform.SetLocalPosition({ 0.0f, 0.0f });
		JinHillSideSlapSkillCol->Transform.SetLocalScale({ 750.0f, 300.0f });
		JinHillSideSlapSkillCol->SetCollisionType(ColType::AABBBOX2D);
		JinHillSideSlapSkillCol->Off();

		JinHillChoppingSkillCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterAttackRange);
		JinHillChoppingSkillCol->Transform.SetLocalPosition({ 0.0f, 100.0f });
		JinHillChoppingSkillCol->Transform.SetLocalScale({ 550.0f, 350.0f });
		JinHillChoppingSkillCol->SetCollisionType(ColType::AABBBOX2D);
		JinHillChoppingSkillCol->Off();
	}

	// 스킬 애니메이션
	SkillAnimation();

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
		JinHillaAttackRangeCol->Transform.SetLocalPosition({ 0.0f, 100.0f });
		JinHillaAttackRangeCol->Transform.SetLocalScale({ 600.0f, 400.0f });
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


	//BossEffect = GetLevel()->CreateActor<BossSkillEffect>();
	//BossEffect->Transform.SetLocalPosition({ 900.0f, -700.0f });
}

void JinHillaBoss::Update(float _Delta)
{
	GameEngineDebug::DrawBox2D(MonsterRenderer->GetImageTransform(), float4::GREEN);
	MonsterFunction::Update(_Delta);

	JinDirCheck();
	StateUpdate(_Delta);

	if (JinHillaCurHp <= 0)
	{
		ChangeState(MonsterState::Death);
		return;
	}

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
		ChangeState(MonsterState::Skill1);
	}
	if (GameEngineInput::IsDown('7', this))
	{
		ChangeState(MonsterState::Skill1After);
	}
	//if (GameEngineInput::IsDown('6', this))
	//{
	//	MonsterRenderer->ChangeAnimation("Attack");
	//	MonsterRenderer->Transform.SetLocalPosition({ -160.0f, 140.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
	//}
	//if (GameEngineInput::IsDown('7', this))
	//{
	//	MonsterRenderer->ChangeAnimation("Attack2");
	//	MonsterRenderer->Transform.SetLocalPosition({ -160.0f, 140.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
	//}
	//if (GameEngineInput::IsDown('8', this))
	//{
	//	MonsterRenderer->ChangeAnimation("Attack3");
	//	MonsterRenderer->Transform.SetLocalPosition({ -330.0f, 120.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
	//}
	//if (GameEngineInput::IsDown('9', this))
	//{
	//	MonsterRenderer->ChangeAnimation("Attack4");
	//	MonsterRenderer->Transform.SetLocalPosition({ -260.0f, 100.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ -40.0f, 100.0f });
	//}
	//if (GameEngineInput::IsDown('0', this))
	//{
	//	MonsterRenderer->ChangeAnimation("Attack5");
	//	MonsterRenderer->Transform.SetLocalPosition({ -50.0f, 120.0f });
	//	MonsterCollision->Transform.SetLocalPosition({ -40.0f, 120.0f });
	//}

	if (GameEngineInput::IsDown('-', this))
	{
		JinHillaCurHp -= 10000000000000;
	}


	//PlayerDirX = Player::GetMainPlayer()->Transform.GetWorldPosition().X;
	//MonsterDirX = MonsterRenderer->Transform.GetWorldPosition().X;
	//if (PlayerDirX > MonsterDirX)
	//{
	//	Dir = ActorDir::Right;
	//}
	//if (PlayerDirX < MonsterDirX)
	//{
	//	Dir = ActorDir::Left;
	//}

	InsideLockMap();
	//AttackEvent(_Delta);

	// 넉백 만들어보려했는데 이대로 만드는게 아니라 플레이어에 넉백함수를 만들어서 플레이어가 직접 넉백당하게만들어야 될꺼같음.
	// 방향, 거리, 시간영향, 힘? 필요할듯
	EventParameter KnockAttack;
	{
		KnockAttack.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Player)
			{
				//_Player->GetParentObject()->Transform.AddLocalPosition({300.0f});
				//float4 Dir = Player::GetMainPlayer()->Transform.GetWorldPosition() + float4{ 0, 100 } - Transform.GetWorldPosition();
				//Dir.Normalize();
				//_Player->GetParentObject()->GetDynamic_Cast_This<Player>()->KnockBack(Dir, 150.0f,300.0f, 1.0f);
				int a = 0;
			};
		JinHillKnockSkillCol->CollisionEvent(ContentsCollisionType::Player, KnockAttack);
	}

	JinHillKnockSkillCol->Collision(ContentsCollisionType::Player, std::bind(&JinHillaBoss::CollisionEvent, this, std::placeholders::_1));
	//if (JinHillKnockSkillCol == true)
	//{
	//	float4 Dir = Player::GetMainPlayer()->Transform.GetWorldPosition() + float4{ 0, 100 } - Transform.GetWorldPosition();
	//	Dir.Normalize();
	//	Player::GetMainPlayer()->KnockBack(Dir, 150.0f, 300.0f, 1.0f);
	//}
	//if (PlayerBind == true)
	//{
	//	Player::GetMainPlayer()->PlayerBind();
	//}
	//
	//EventParameter BindAttack;
	//{
	//	BindAttack.Enter = [](GameEngineCollision* _this, GameEngineCollision* _Player)
	//		{
	//			//Player::GetMainPlayer()->PlayerBind();
	//			//PlayerBind = true;
	//			_Player->GetParentObject()->GetDynamic_Cast_This<Player>()->GetMainPlayer()->PlayerBind();
	//		};
	//	BindAttack.Stay = [](GameEngineCollision* _this, GameEngineCollision* _Player)
	//		{
	//			//Player::GetMainPlayer()->PlayerBind();
	//			//PlayerBind = true;
	//			_Player->GetParentObject()->GetDynamic_Cast_This<Player>()->GetMainPlayer()->PlayerBind();
	//		};
	//	JinHillBindSkillCol->CollisionEvent(ContentsCollisionType::Player, BindAttack);
	//}

	//if (true == JinHillBindSkillCol->Collision(ContentsCollisionType::Player, std::bind(&JinHillaBoss::CollisionEvent, this, std::placeholders::_1)))
	//{
	//	Player::GetMainPlayer()->PlayerBind(1.5f);
	//}
}

void JinHillaBoss::CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
{
	//Player::GetMainPlayer()->PlayerBind(1.5f);
	float4 Dir = Player::GetMainPlayer()->Transform.GetWorldPosition() + float4{ 0, 100 } - Transform.GetWorldPosition();
	Dir.Normalize();
	Player::GetMainPlayer()->KnockBack(Dir, 150.0f, 300.0f, 1.0f);
}


void JinHillaBoss::JinDirCheck()
{
	PlayerDirX = Player::GetMainPlayer()->Transform.GetWorldPosition().X;
	MonsterDirX = MonsterRenderer->Transform.GetWorldPosition().X;
	if (PlayerDirX >= MonsterDirX)
	{
		Dir = ActorDir::Right;
	}
	if (PlayerDirX < MonsterDirX)
	{
		Dir = ActorDir::Left;
	}
}


void JinHillaBoss::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainBoss = this;
	//JinHillaCurHp = 176000000000000; // 1페
	//JinHillaCurHp = 133000000000000; // 2페
	//JinHillaCurHp = 89000000000000;  // 3페	
	JinHillaCurHp = 45000000000000;  // 4페
}

void JinHillaBoss::SkillAnimation()
{
	// 공격스킬 애니메이션
	{
		// Attack3
		MonsterRenderer->SetFrameEvent("Attack3", 14, [&](GameEngineSpriteRenderer*)
			{
				JinHillBindSkillCol->On();
			}
		);
		MonsterRenderer->SetFrameEvent("Attack3", 20, [&](GameEngineSpriteRenderer*)
			{
				JinHillBindSkillCol->Off();
			}
		);
		MonsterRenderer->SetFrameEvent("Attack3", 37, [&](GameEngineSpriteRenderer*)
			{
				JinHillKnockSkillCol->On();
			}
		);
		MonsterRenderer->SetFrameEvent("Attack3", 41, [&](GameEngineSpriteRenderer*)
			{
				JinHillKnockSkillCol->Off();
			}
		);

		// Attack4
		MonsterRenderer->SetFrameEvent("Attack4", 18, [&](GameEngineSpriteRenderer*)
			{
				JinHillFrontSlapSkillCol->On();
			}
		);
		MonsterRenderer->SetFrameEvent("Attack4", 23, [&](GameEngineSpriteRenderer*)
			{
				JinHillFrontSlapSkillCol->Off();
			}
		);

		// Attack5
		MonsterRenderer->SetFrameEvent("Attack5", 19, [&](GameEngineSpriteRenderer*)
			{
				JinHillSideSlapSkillCol->On();
			}
		);

		MonsterRenderer->SetFrameEvent("Attack5", 24, [&](GameEngineSpriteRenderer*)
			{
				JinHillSideSlapSkillCol->Off();
			}
		);

		// Attack7
		MonsterRenderer->SetFrameEvent("Attack7", 14, [&](GameEngineSpriteRenderer*)
			{
				JinHillChoppingSkillCol->On();
			}
		);

		MonsterRenderer->SetFrameEvent("Attack7", 17, [&](GameEngineSpriteRenderer*)
			{
				JinHillChoppingSkillCol->Off();
			}
		);
	}
}