#include "PreCompile.h"
#include "SkillManager.h"
#include "Player.h"

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}

void SkillManager::Start()
{
	{
		SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->CreateAnimation("DobleJump", "JumpNormal", 0.1f, -1, -1, true);
		SkillRenderer->ChangeAnimation("DobleJump");
		SkillRenderer->On();

	}
}

void SkillManager::Update(float _Delta)
{
	//SkillRenderer->Transform.SetLocalPosition(Player::MainPlayer->Transform.GetWorldPosition());
}