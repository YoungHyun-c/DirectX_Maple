#include "PreCompile.h"
#include "GhostDamien.h"

GhostDamien* GhostDamien::SummonDamien;

GhostDamien::GhostDamien()
{
	MonsterName = static_cast<int>(MonstersName::GhostDamien);
	SummonDamien = this;
}

GhostDamien::~GhostDamien()
{

}



void GhostDamien::Start()
{
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	MonsterRenderer->CreateAnimation("Regen", "GhostDamien_Regen", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Stand", "GhostDamien_Stand", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Attack", "GhostDamien_Attack", 0.1f, -1, -1, false); // 슬라이드 공격(밀격)
	MonsterRenderer->CreateAnimation("Skill1", "GhostDamien_Skill1", 0.1f, -1, -1, false); // 걸어서 움직이지 않음 플레이어 주변에 순간이동
	MonsterRenderer->CreateAnimation("Skill1After", "GhostDamien_Skill1After", 0.1f, -1, -1, false); // 순간이동 후
	MonsterRenderer->CreateAnimation("Skill2", "GhostDamien_Skill2", 0.1f, -1, -1, false); // 
	MonsterRenderer->CreateAnimation("Skill2After", "GhostDamien_Skill2After", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Death", "GhostDamien_Death", 0.1f, -1, -1, false);

	MonsterRenderer->ChangeAnimation("Stand");
	MonsterRenderer->AutoSpriteSizeOn();
	MonsterRenderer->SetPivotType(PivotType::Bottom);
	MonsterRenderer->Off();

	MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
	MonsterCollision->Transform.SetLocalScale({ 75.0f, 130.0f });
	MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
	MonsterCollision->Off();

	HitEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::MonsterSkill);
	HitEffect->CreateAnimation("BackEffect", "GhostDamien_Attack1_BackEffect", 0.1f, -1, -1, false); // 
	HitEffect->CreateAnimation("Skill2Hit", "GhostDamien_Skill2Hit", 0.1f, -1, -1, false);

	HitEffect->ChangeAnimation("BackEffect");
	HitEffect->AutoSpriteSizeOn();
	HitEffect->SetPivotType(PivotType::Bottom);
	HitEffect->Off();

	SetMoveSpeed(MoveSpeed);
}

void GhostDamien::Update(float _Delta)
{
	MonsterFunction::Update(_Delta);

	TimeCounting();
	StateUpdate(_Delta);

	if (GameEngineInput::IsDown('5'))
	{
		MonsterRenderer->On();
		MonsterCollision->On();
		//BallSprite->On();
		MonsterRenderer->LeftFlip();
		Dir = ActorDir::Right;
		ChangeState(MonsterState::Regen);
	}
	if (GameEngineInput::IsDown('6'))
	{
		ChangeState(MonsterState::Attack);
		HitEffect->On();
		HitEffect->ChangeAnimation("BackEffect");
		//HitEffect->Transform.SetLocalPosition({ -50.0f });
	}
	if (GameEngineInput::IsDown('7'))
	{
		//ChangeState(MonsterState::Die);
		MonsterRenderer->ChangeAnimation("Skill1After");
		MonsterRenderer->RightFlip();
		Dir = ActorDir::Left;
	}
	if (GameEngineInput::IsDown('8'))
	{
		ChangeState(MonsterState::Skill1);
	}
	if (GameEngineInput::IsDown('9'))
	{
		ChangeState(MonsterState::Skill2);
	}

	if (GameEngineInput::IsDown('0'))
	{
		ChangeState(MonsterState::Death);
	}

	if (GameEngineInput::IsDown('-'))
	{
		MonsterRenderer->ChangeAnimation("Skill2After");
		HitEffect->ChangeAnimation("Skill2Hit");
	}


	if (Dir == ActorDir::Left)
	{
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X - 50.0f,
			MonsterRenderer->Transform.GetLocalPosition().Y + 150.0f});
	}
	else if (Dir == ActorDir::Right)
	{
		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X + 50.0f,
	MonsterRenderer->Transform.GetLocalPosition().Y + 150.0f });
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
}

void GhostDamien::StandUpdate(float _Delta)
{
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Skill1);
	}
}

void GhostDamien::DeathUpdate(float _Delat)
{

}
