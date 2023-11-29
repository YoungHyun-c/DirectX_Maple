#include "PreCompile.h"
#include "BossSkillEffect.h"

BossSkillEffect::BossSkillEffect()
{

}

BossSkillEffect::~BossSkillEffect()
{

}


void BossSkillEffect::Start()
{
	SkillEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);

	SkillEffect->CreateAnimation("GreenTile0", "GreenFloorTile0", 0.1f);
	SkillEffect->CreateAnimation("GreenTile1", "GreenFloorTile1", 0.1f);
	SkillEffect->CreateAnimation("GreenTile2", "GreenFloorTile2", 0.1f);

	SkillEffect->CreateAnimation("PurpleTile0", "PurpleFloorTile0", 0.1f);
	SkillEffect->CreateAnimation("PurpleTile1", "PurpleFloorTile1", 0.1f);
	SkillEffect->CreateAnimation("PurpleTile2", "PurpleFloorTile2", 0.1f);

	// 볼
	SkillEffect->CreateAnimation("Attack6_Ball", "JinHilla_Attack6_Ball", 0.1f);

	SkillEffect->ChangeAnimation("GreenTile2");
	SkillEffect->AutoSpriteSizeOn();
	SkillEffect->SetPivotType(PivotType::Bottom);


	SkillEffectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
	SkillEffectCollision->SetCollisionType(ColType::AABBBOX2D);
	SkillEffectCollision->Off();

	SkillEffect->SetFrameEvent("GreenTile0", 1, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Transform.SetLocalPosition({ 0.0f, 100.0f });
			SkillEffectCollision->Transform.SetLocalScale({ 100.0f, 100.0f });
			SkillEffectCollision->On();
		}
	);
	SkillEffect->SetFrameEvent("GreenTile0", 15, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Off();
		}
	);

	SkillEffect->SetFrameEvent("GreenTile1", 1, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Transform.SetLocalPosition({ 0.0f, 200.0f });
			SkillEffectCollision->Transform.SetLocalScale({ 100.0f, 300.0f });
			SkillEffectCollision->On();
		}
	);
	SkillEffect->SetFrameEvent("GreenTile1", 15, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Off();
		}
	);

	SkillEffect->SetFrameEvent("GreenTile2", 1, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Transform.SetLocalPosition({ 0.0f, 350.0f });
			SkillEffectCollision->Transform.SetLocalScale({ 100.0f, 600.0f });
			SkillEffectCollision->On();
		}
	);
	SkillEffect->SetFrameEvent("GreenTile2", 15, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Off();
		}
	);

	SkillEffect->SetFrameEvent("PurpleTile0", 1, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Transform.SetLocalPosition({ 0.0f, 100.0f });
			SkillEffectCollision->Transform.SetLocalScale({ 100.0f, 100.0f });
			SkillEffectCollision->On();
		}
	);
	SkillEffect->SetFrameEvent("PurpleTile0", 15, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Off();
		}
	);

	SkillEffect->SetFrameEvent("PurpleTile1", 1, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Transform.SetLocalPosition({ 0.0f, 200.0f });
			SkillEffectCollision->Transform.SetLocalScale({ 100.0f, 300.0f });
			SkillEffectCollision->On();
		}
	);
	SkillEffect->SetFrameEvent("PurpleTile1", 15, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Off();
		}
	);

	SkillEffect->SetFrameEvent("PurpleTile2", 1, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Transform.SetLocalPosition({ 0.0f, 350.0f });
			SkillEffectCollision->Transform.SetLocalScale({ 100.0f, 600.0f });
			SkillEffectCollision->On();
		}
	);
	SkillEffect->SetFrameEvent("PurpleTile2", 15, [&](GameEngineSpriteRenderer*)
		{
			SkillEffectCollision->Off();
		}
	);
}

void BossSkillEffect::Update(float _Delta)
{
	// Collision->Collision();

	// 초앞 보뒤
	SkillEffectCollision->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			Player::GetMainPlayer()->PlayerHit((static_cast<float>(PlayerValue::GetValue()->GetMaxHp()) * 50.0f /
				static_cast<float>(PlayerValue::GetValue()->GetMaxHp())), true);
		}
	);

	if (true == SkillEffect->IsCurAnimationEnd())
	{
		Death();
	}
}