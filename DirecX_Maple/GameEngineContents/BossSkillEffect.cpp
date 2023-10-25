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

	SkillEffect->ChangeAnimation("GreenTile2");
	SkillEffect->AutoSpriteSizeOn();
	SkillEffect->SetPivotType(PivotType::Bottom);

}

void BossSkillEffect::Update(float _Delta)
{
	// Collision->Collision();

	if (true == SkillEffect->IsCurAnimationEnd())
	{
		Death();
	}
}