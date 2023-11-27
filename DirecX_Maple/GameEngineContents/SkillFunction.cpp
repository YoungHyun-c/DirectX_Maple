#include "PreCompile.h"
#include "SkillFunction.h"
#include "Player.h"

SkillFunction::SkillFunction()
{

}

SkillFunction::~SkillFunction()
{

}

void SkillFunction::Start()
{
	// 앞스킬
	if (nullptr == SkillRender1)
	{
		SkillRender1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		SkillRender1->AutoSpriteSizeOn();
		SkillRender1->Off();
	}
	// 백스킬
	if (nullptr == SkillRender2)
	{
		SkillRender2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
		SkillRender2->AutoSpriteSizeOn();
		SkillRender2->Off();
	}

	if (nullptr == SkillRender3)
	{
		SkillRender3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		SkillRender3->AutoSpriteSizeOn();
		SkillRender3->Off();
	}

	if (nullptr == AfterSkillImage)
	{
		AfterSkillImage = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		AfterSkillImage->AutoSpriteSizeOn();
		AfterSkillImage->Off();
	}
}

void SkillFunction::Update(float _Delta)
{
	PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
}

void SkillFunction::UseSkill()
{
	IsSkillStart = true;
	IsSkillEnd = false;
	PlayerDir = Player::GetMainPlayer()->GetDir();
	PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	PlayerScale = Player::GetMainPlayer()->GetPlayerScale();
}


void SkillFunction::Release()
{
	if (nullptr != SkillRender1)
	{
		SkillRender1->Death();
		SkillRender1 = nullptr;
	}

	if (nullptr != SkillRender2)
	{
		SkillRender2->Death();
		SkillRender2 = nullptr;
	}

	if (nullptr != SkillRender3)
	{
		SkillRender3->Death();
		SkillRender3 = nullptr;
	}

	if (nullptr != AfterSkillImage)
	{
		AfterSkillImage->Death();
		AfterSkillImage = nullptr;
	}
}

void SkillFunction::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}