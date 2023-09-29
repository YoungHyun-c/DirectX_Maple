#include "PreCompile.h"
#include "Player.h"
#include "AdeleSkill.h"

AdeleSkill::AdeleSkill()
{

}

AdeleSkill::~AdeleSkill()
{

}


void AdeleSkill::Start()
{
	TimeCounting();

	// 점프
	{
		DoubleJumpRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
		DoubleJumpRenderer->AutoSpriteSizeOn();
		DoubleJumpRenderer->CreateAnimation("DobleJump", "JumpNormal", 0.03f, -1, -1, false);
		DoubleJumpRenderer->ChangeAnimation("DobleJump");
		DoubleJumpRenderer->Off();

		UpJumpRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
		UpJumpRenderer->AutoSpriteSizeOn();
		UpJumpRenderer->CreateAnimation("UpDobleJump", "JumpUp", 0.03f, -1, -1, true);
		UpJumpRenderer->ChangeAnimation("UpDobleJump");
		UpJumpRenderer->Off();
	}

	// 디바이드
	{
		Divide1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Divide1->AutoSpriteSizeOn();
		Divide1->CreateAnimation("Divide1", "Divide_1", 0.05f, -1, -1, false);
		Divide1->ChangeAnimation("Divide1");
		Divide1->Off();

		Divide2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Divide2->AutoSpriteSizeOn();
		Divide2->CreateAnimation("Divide2", "Divide_2", 0.05f, -1, -1, false);
		Divide2->ChangeAnimation("Divide2");
		Divide2->Off();

		Divide3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Divide3->AutoSpriteSizeOn();
		Divide3->CreateAnimation("Divide3", "Divide_3", 0.05f, -1, -1, false);
		Divide3->ChangeAnimation("Divide3");
		Divide3->Off();
	}


	// 크리에이션
	{
		Creation1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Creation1->AutoSpriteSizeOn();
		Creation1->CreateAnimation("Creation1", "Creation1_Special", 0.05f, -1, -1, false);
		Creation1->ChangeAnimation("Creation1");
		Creation1->Off();

		Creation2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Creation2->AutoSpriteSizeOn();
		Creation2->CreateAnimation("Creation2", "Creation2_Special", 0.05f, -1, -1, false);
		Creation2->ChangeAnimation("Creation2");
		Creation2->Off();

		Creation3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Creation3->AutoSpriteSizeOn();
		Creation3->CreateAnimation("Creation3", "Creation3_Special", 0.05f, -1, -1, false);
		Creation3->ChangeAnimation("Creation3");
		Creation3->Off();
	}

	// 
	{
		
	}
}


void AdeleSkill::Update(float _Delta)
{
	//PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	
	if (UpdateFunc != nullptr)
	{
		UpdateFunc(*this);
	}
}

void AdeleSkill::SetSkillActor(const std::string_view& _SkillName, bool _isRePlay)
{
	SkillName = _SkillName.data();
	isRePlay = _isRePlay;

	//AnimationRenderer = CreateComponent<GameEngineSpriteRenderer>();

	SetSkillAnimation();
	SetUpdateFunc();
}


void AdeleSkill::SetSkillAnimation()
{
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	if (SkillName == "BoltJump")
	{
		UpJumpRenderer->Transform.SetWorldPosition({ PlayerPos.X, PlayerPos.Y - 50.0f });
		UpJumpRenderer->On();
	}
	else if (SkillName == "DoubleJump")
	{
		ActorDir Dir = Player::MainPlayer->GetDir();
		switch (Dir)
		{
		case ActorDir::Left:
			DoubleJumpRenderer->Transform.SetWorldPosition({ PlayerPos.X + 100.0f, PlayerPos.Y });
			DoubleJumpRenderer->RightFlip();
			DoubleJumpRenderer->On();
			break;
		case ActorDir::Right:
			DoubleJumpRenderer->Transform.SetWorldPosition({ PlayerPos.X - 100.0f, PlayerPos.Y });
			DoubleJumpRenderer->LeftFlip();
			DoubleJumpRenderer->On();
			break;
		default:
			break;
		}
	}
	else if (SkillName == "Divide1")
	{
		ActorDir Dir = Player::MainPlayer->GetDir();
		switch (Dir)
		{
		case ActorDir::Left:
			Divide1->Transform.SetWorldPosition({ PlayerPos.X - 300.0f, PlayerPos.Y - 25.0f });
			Divide1->RightFlip();
			Divide1->On();
			Creation1->Transform.SetWorldPosition({ PlayerPos.X - 300.0f, PlayerPos.Y - 25.0f });
			Creation1->RightFlip();
			Creation1->On();
			break;
		case ActorDir::Right:
			Divide1->Transform.SetWorldPosition({ PlayerPos.X + 300.0f, PlayerPos.Y});
			Divide1->LeftFlip();
			Divide1->On();
			Creation1->Transform.SetWorldPosition({ PlayerPos.X + 300.0f, PlayerPos.Y});
			Creation1->LeftFlip();
			Creation1->On();
			break;
		default:
			break;
		}
	}
	else if (SkillName == "Divide2")
	{
		ActorDir Dir = Player::MainPlayer->GetDir();
		switch (Dir)
		{
		case ActorDir::Left:
			Divide2->Transform.SetWorldPosition({ PlayerPos.X - 200.0f, PlayerPos.Y});
			Divide2->RightFlip();
			Divide2->On();
			Creation2->Transform.SetWorldPosition({ PlayerPos.X - 200.0f, PlayerPos.Y });
			Creation2->RightFlip();
			Creation2->On();
			break;
		case ActorDir::Right:
			Divide2->Transform.SetWorldPosition({ PlayerPos.X + 300.0f, PlayerPos.Y});
			Divide2->LeftFlip();
			Divide2->On();
			Creation2->Transform.SetWorldPosition({ PlayerPos.X + 300.0f, PlayerPos.Y });
			Creation2->LeftFlip();
			Creation2->On();
			break;
		default:
			break;
		}
	}
	else if (SkillName == "Divide3")
	{
		ActorDir Dir = Player::MainPlayer->GetDir();
		switch (Dir)
		{
		case ActorDir::Left:
			Divide3->Transform.SetWorldPosition({ PlayerPos.X - 200.0f, PlayerPos.Y});
			Divide3->RightFlip();
			Divide3->On();
			Creation3->Transform.SetWorldPosition({ PlayerPos.X - 300.0f, PlayerPos.Y });
			Creation3->RightFlip();
			Creation3->On();
			break;
		case ActorDir::Right:
			Divide3->Transform.SetWorldPosition({ PlayerPos.X + 200.0f, PlayerPos.Y});
			Divide3->LeftFlip();
			Divide3->On();
			Creation3->Transform.SetWorldPosition({ PlayerPos.X + 300.0f, PlayerPos.Y });
			Creation3->LeftFlip();
			Creation3->On();
			break;
		default:
			break;
		}
	}
}

void AdeleSkill::SetUpdateFunc()
{
	if (SkillName == "BoltJump")
	{
		UpdateFunc = &AdeleSkill::BoltJump;
	}
	else if (SkillName == "DoubleJump")
	{
		UpdateFunc = &AdeleSkill::DoubleJump;
	}
	else if (SkillName == "Divide1")
	{
		UpdateFunc = &AdeleSkill::DivideSkill;
	}
	else if (SkillName == "Divide2")
	{
		UpdateFunc = &AdeleSkill::DivideSkill;
	}
	else if (SkillName == "Divide3")
	{
		UpdateFunc = &AdeleSkill::DivideSkill;
	}
}

void AdeleSkill::DoubleJump()
{
	if (DoubleJumpRenderer->IsCurAnimationEnd())
	{
		DoubleJumpRenderer->Off();
	}
}

void AdeleSkill::BoltJump()
{
	if (UpJumpRenderer->IsCurAnimationEnd())
	{
		UpJumpRenderer->Off();
	}
}

void AdeleSkill::DivideSkill()
{

	if (Divide1->IsCurAnimationEnd())
	{
		Divide1->Off();
		Creation1->Off();
	}

	if (Divide2->IsCurAnimationEnd())
	{
		Divide2->Off();
		Creation2->Off();
	}

	if (Divide3->IsCurAnimationEnd())
	{
		Divide3->Off();
		Creation3->Off();
	}
}