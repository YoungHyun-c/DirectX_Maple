#include "PreCompile.h"
#include "JinHillaBoss.h"
#include "Player.h"

#include "MonsterFunction.h"

#include "CravingMonster.h"
#include "GhostDamien.h"

#include "BossSkillEffect.h"
#include "BossSkillManager.h"
#include "GlobalValue.h"
#include "AchieveUI.h"
#include "BossChat.h"

#include "BossBindEffect.h"
#include "BossFormerEffect.h"

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
	MonsterRenderer->CreateAnimation("Attack2", "BossPurpleAttack", 0.1f, -1, -1, false); // 보뒤
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
		JinHillBindSkillCol->Transform.SetLocalPosition({ 0.0f, 90.0f });
		JinHillBindSkillCol->Transform.SetLocalScale({ 600.0f, 380.0f });
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

	//몸통
	{
		MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		MonsterCollision->Transform.SetLocalScale({ 100.0f, 200.0f });
		MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
		MonsterCollision->Off();
		MonsterCollision->SetName(std::string("Boss"));
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


	// 욕망의 헌신 몹
	if (nullptr == CravingMob1)
	{
		CravingMob1 = GetLevel()->CreateActor<CravingMonster>();
		CravingMob1->Transform.SetWorldPosition({ 700.0f, -760.0f, static_cast<float>(DeepBufferType::Monster) });
		CravingMob1->SetDebugMap("BossDebugMap.Png");
	}
	if (nullptr == CravingMob2)
	{
		CravingMob2 = GetLevel()->CreateActor<CravingMonster>();
		CravingMob2->Transform.SetWorldPosition({ 1200.0f, -760.0f, static_cast<float>(DeepBufferType::Monster) });
		CravingMob2->SetDebugMap("BossDebugMap.Png");
	}

	// 데미안 몹
	if (nullptr == DamienMob)
	{
		DamienMob = GetLevel()->CreateActor<GhostDamien>();
		DamienMob->Transform.SetWorldPosition({ 500.0f, -650.0f, static_cast<float>(DeepBufferType::Monster) });
		DamienMob->SetDebugMap("BossDebugMap.Png");
	}

	// 바인드 이펙트
	{
		SkillBindEffect = GetLevel()->CreateActor<BossBindEffect>(ContentsObjectType::FrontSkill);
		SkillBindEffect->Off();
	}
	{
		FormBindEffect = GetLevel()->CreateActor<BossFormerEffect>(ContentsObjectType::FrontSkill);
		FormBindEffect->Off();
	}
}

void JinHillaBoss::Update(float _Delta)
{

	if (DarkRenderer->GetColorData().MulColor.A >= 1)
	{
		GameEngineCore::ChangeLevel("9.BossRewardLevel");
		return;
	}

	if (JinHillaCurHp <= 0)
	{
		GlobalValue::GetNeedGlobalValue()->SetBossDeath(true);
		ChangeState(MonsterState::Death);

		ChangeTime += _Delta;
		if (ChangeTime >= ChangeLevelTime)
		{
			DarkRenderer->Transform.SetWorldPosition(0);
			DarkRenderer->GetColorData().MulColor.A += _Delta * 0.5f;
			DarkRenderer->On();
		}
		return;
	}

	if (SkillBind == true)
	{
		SkillBinding += _Delta;
		SkillBindEffect->Transform.SetLocalPosition(MonsterRenderer->Transform.GetWorldPosition());
		SkillBindEffect->GetStartBindEffect();
		SkillBindEffect->On();
		ChangeState(MonsterState::Stand);
		BossBind();
		return;
	}

	if (FormerBind == true)
	{
		FormerBinding += _Delta;
		FormBindEffect->Transform.SetLocalPosition(MonsterRenderer->Transform.GetWorldPosition());
		FormBindEffect->GetStartFormerBindEffect();
		FormBindEffect->On();
		ChangeState(MonsterState::Stand);
		BossFormerBind();
		return;
	}

	MonsterFunction::Update(_Delta);
	StateUpdate(_Delta);



	if (GameEngineInput::IsDown('9', this))
	{
		JinHillaCurHp -= 10000000000000;
	}

	InsideLockMap();
	AttackEvent(_Delta);

	JinHillBindSkillCol->Collision(ContentsCollisionType::Player, std::bind(&JinHillaBoss::BindCollisionEvent, this, std::placeholders::_1));
	JinHillBindSkillCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 10.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);

	JinHillKnockSkillCol->Collision(ContentsCollisionType::Player, std::bind(&JinHillaBoss::KnockBackCollisionEvent, this, std::placeholders::_1));
	JinHillKnockSkillCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 10.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);

	// 낫 찍기
	JinHillChoppingSkillCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 20.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);

	// 앞 방향 휘두르기
	JinHillFrontSlapSkillCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 10.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);

	// 양 방향 휘두르기
	JinHillSideSlapSkillCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 30.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);
}

void JinHillaBoss::BossBind()
{
	SkillBind = true;
	if (SkillBinding >= SkillBindTime)
	{
		SkillBindEffect->GetEndBindEffect();
		SkillBind = false;
		SkillBinding = 0.0f;
		return;
	}
}

void JinHillaBoss::BossFormerBind()
{
	FormerBind = true;
	if (FormerBinding >= FormerBindTime)
	{
		FormBindEffect->GetEndFormerBindEffect();
		FormerBind = false;
		FormerBinding = 0.0f;
		return;
	}
}

void JinHillaBoss::BindCollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	Player::GetMainPlayer()->PlayerBind(2.0f);
}

void JinHillaBoss::KnockBackCollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	float4 Dir = Player::GetMainPlayer()->Transform.GetWorldPosition().X - Transform.GetWorldPosition().X;
	Dir.Y = Player::GetMainPlayer()->Transform.GetWorldPosition().Y - Transform.GetWorldPosition().Y + 500.0f;
	Dir.Normalize();
	Player::GetMainPlayer()->KnockBack(Dir, 600.0f, 900.0f, 1.5f);
}


void JinHillaBoss::JinDirCheck()
{
	PlayerDirX = Player::GetMainPlayer()->Transform.GetWorldPosition().X;
	MonsterDirX = MonsterRenderer->Transform.GetWorldPosition().X;
	if (PlayerDirX >= MonsterDirX)
	{
		Dir = ActorDir::Right;
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + RightColPos,
			MonsterRenderer->Transform.GetLocalPosition().Y + YColPos });
		MonsterRenderer->LeftFlip();
		return;
	}
	if (PlayerDirX < MonsterDirX)
	{
		Dir = ActorDir::Left;
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + LeftColPos,
			MonsterRenderer->Transform.GetLocalPosition().Y + YColPos });
		MonsterRenderer->RightFlip();
		return;
	}
}


void JinHillaBoss::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainBoss = this;
	JinHillaCurHp = 176000000000000; // 1페
	//JinHillaCurHp = 133000000000000; // 2페
	//JinHillaCurHp = 89000000000000;  // 3페	
	//JinHillaCurHp = 45000000000000;  // 4페

	if (DarkRenderer == nullptr)
	{
		DarkRenderer = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::Mouse);
		DarkRenderer->SetSprite("Dark.Png");
		DarkRenderer->GetColorData().MulColor.A = 0;
		DarkRenderer->Transform.SetWorldPosition(0);
		DarkRenderer->Off();
	}

	if (Chat == nullptr)
	{
		Chat = GetLevel()->CreateActor<BossChat>(ContentsObjectType::UI);
	}
	if (Achieve == nullptr)
	{
		Achieve = GetLevel()->CreateActor<AchieveUI>(ContentsObjectType::UI);
	}
}

void JinHillaBoss::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != DarkRenderer)
	{
		DarkRenderer->Death();
		DarkRenderer = nullptr;
	}

	DarkRenderer->GetColorData().MulColor.A = 0;
	ChangeTime = 0.0f;
	Death();
}


///////////////////// 공격스킬 애니메이션 관련////////////////////
void JinHillaBoss::SkillAnimation()
{
	{
		MonsterRenderer->SetFrameEvent("Attack", 14, [&](GameEngineSpriteRenderer*)
			{
				BossSkillManager::BossSkillEffectManager->SkillUseKey('G');
			}
		);
	}

	{
		MonsterRenderer->SetFrameEvent("Attack2", 14, [&](GameEngineSpriteRenderer*)
			{
				BossSkillManager::BossSkillEffectManager->SkillUseKey('P');
			}
		);
	}

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

	{
		MonsterRenderer->SetEndEvent("Death", [&](GameEngineSpriteRenderer*)
			{
				MonsterRenderer->Off();
			}
		);
	}
}


/////// 확인 해보던 것

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



////////// 넉백
// 넉백 만들어보려했는데 이대로 만드는게 아니라 플레이어에 넉백함수를 만들어서 플레이어가 직접 넉백당하게만들어야 될꺼같음.
	// 방향, 거리, 시간영향, 힘? 필요할듯
//EventParameter KnockAttack;
//{
//	KnockAttack.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Player)
//		{
//			//_Player->GetParentObject()->Transform.AddLocalPosition({300.0f});
//			//float4 Dir = Player::GetMainPlayer()->Transform.GetWorldPosition() + float4{ 0, 100 } - Transform.GetWorldPosition();
//			//Dir.Normalize();
//			//_Player->GetParentObject()->GetDynamic_Cast_This<Player>()->KnockBack(Dir, 150.0f,300.0f, 1.0f);
//			int a = 0;
//		};
//	JinHillKnockSkillCol->CollisionEvent(ContentsCollisionType::Player, KnockAttack);
//}
//
//JinHillKnockSkillCol->Collision(ContentsCollisionType::Player, std::bind(&JinHillaBoss::CollisionEvent, this, std::placeholders::_1));
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