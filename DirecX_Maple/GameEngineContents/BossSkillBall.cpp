#include "PreCompile.h"
#include "BossSkillBall.h"

BossSkillBall::BossSkillBall()
{

}

BossSkillBall::~BossSkillBall()
{

}


void BossSkillBall::Start()
{
	SkillBall = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);

	// º¼
	SkillBall->CreateAnimation("Attack6_Ball", "JinHilla_Attack6_Ball", 0.1f);

	SkillBall->ChangeAnimation("Attack6_Ball");
	SkillBall->AutoSpriteSizeOn();

	SkillBallCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
	SkillBallCollision->Transform.SetLocalScale({ 100.0f, 70.0f });
	SkillBallCollision->SetCollisionType(ColType::AABBBOX2D);
	SkillBallCollision->On();
}

void BossSkillBall::Update(float _Delta)
{

	SkillBallCollision->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 40.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);

	if (Dir == ActorDir::Left)
	{
		SkillBall->RightFlip();
		Transform.AddLocalPosition({ -200.0f * _Delta, 0.0f });
		SkillBallCollision->Transform.SetLocalPosition({ -80.0f, 0.0f });
	}
	else if (Dir == ActorDir::Right)
	{
		SkillBall->LeftFlip();
		Transform.AddLocalPosition({ 200.0f * _Delta, 0.0f });
		SkillBallCollision->Transform.SetLocalPosition({ 80.0f, 0.0f });
	}

	LiveTime += _Delta;
	if (LiveTime >= LimitTime)
	{
		Death();
	}
}