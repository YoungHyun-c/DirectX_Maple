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
		DoubleJumpRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
		DoubleJumpRenderer->AutoSpriteSizeOn();
		DoubleJumpRenderer->CreateAnimation("DobleJump", "JumpNormal", 0.03f, -1, -1, true);
		DoubleJumpRenderer->ChangeAnimation("DobleJump");
		DoubleJumpRenderer->Off();


		UpJumpRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
		UpJumpRenderer->AutoSpriteSizeOn();
		UpJumpRenderer->CreateAnimation("UpDobleJump", "JumpUp", 0.03f, -1, -1, true);
		UpJumpRenderer->ChangeAnimation("UpDobleJump");
		UpJumpRenderer->Off();
	}
}

void SkillManager::Update(float _Delta)
{
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	if (GameEngineInput::IsDown('X'))
	{
		UpJumpRenderer->Off();
		DoubleJumpRenderer->Transform.SetLocalPosition(PlayerPos);
		DoubleJumpRenderer->On();
	}
	if (GameEngineInput::IsDown('H'))
	{
		DoubleJumpRenderer->Off();
		UpJumpRenderer->Transform.SetLocalPosition(PlayerPos);
		UpJumpRenderer->On();
	}
}