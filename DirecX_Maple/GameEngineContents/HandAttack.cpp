#include "PreCompile.h"
#include "HandAttack.h"

HandAttack::HandAttack()
{

}

HandAttack::~HandAttack()
{

}

void HandAttack::Start()
{
	if (nullptr == GameEngineSprite::Find("HandAttack"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaUI");
		Dir.MoveChild("HandAttack");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	//Hand = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//Hand->CreateAnimation("HandAppear", "HandAppear", 0.1f, -1, -1, false);
	//Hand->CreateAnimation("HandAttackBall", "HandAttackBall", 0.1f, -1, -1, false);
	//Hand->CreateAnimation("HandEnd", "HandEnd", 0.1f, -1, -1, false);
	//Hand->CreateAnimation("HandLoop", "HandLoop", 0.1f, -1, -1, false);
	//Hand->Transform.SetWorldPosition({ 900.0f, -200.0f });
	//Hand->AutoSpriteSizeOn();
	//Hand->ChangeAnimation("HandAppear");

	//HandEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//HandEffect->CreateAnimation("HandShooting", "HandShooting", 0.1f, -1, -1, true);
	//HandEffect->Transform.SetWorldPosition({ 900.0f, -250.0f });
	//HandEffect->AutoSpriteSizeOn();
	//HandEffect->ChangeAnimation("HandShooting");
	//HandEffect->Off();

	//StringAttack = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//StringAttack->CreateAnimation("StringAttack", "StringAttack", 0.1f, -1, -1, true);
	//StringAttack->CreateAnimation("StringEffect", "StringEffect", 0.1f, -1, -1, false);
	//StringAttack->Transform.SetWorldPosition({ 900.0f, -500.0f });
	//StringAttack->Transform.SetWorldRotation({ 0.0f, 0.0f, 30.0f });
	//StringAttack->AutoSpriteSizeOn();
	//StringAttack->ChangeAnimation("StringAttack");
	//StringAttack->Off();

	//StringCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::MonsterSkill);
	//StringCol->SetCollisionType(ColType::AABBBOX2D);
	//StringCol->Transform.SetLocalScale({ 24.0f, 760.0f });
	//StringCol->Transform.SetWorldPosition(StringAttack->Transform.GetWorldPosition());
	//StringCol->Transform.SetWorldRotation({ 0.0f, 0.0f, 30.0f });
	//StringCol->Off();

	Hand = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	Hand->CreateAnimation("HandAppear", "HandAppear", 0.1f, -1, -1, false);
	Hand->CreateAnimation("HandAttackBall", "HandAttackBall", 0.1f, -1, -1, false);
	Hand->CreateAnimation("HandEnd", "HandEnd", 0.1f, -1, -1, false);
	Hand->CreateAnimation("HandLoop", "HandLoop", 0.1f, -1, -1, false);
	Hand->AutoSpriteSizeOn();
	Hand->ChangeAnimation("HandAppear");

	HandEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	HandEffect->CreateAnimation("HandShooting", "HandShooting", 0.1f, -1, -1, true);
	HandEffect->Transform.SetLocalPosition({ 0.0f, -50.0f });
	HandEffect->AutoSpriteSizeOn();
	HandEffect->ChangeAnimation("HandShooting");
	HandEffect->Off();

	StringAttack = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	StringAttack->CreateAnimation("StringAttack", "StringAttack", 0.1f, -1, -1, true);
	StringAttack->CreateAnimation("StringEffect", "StringEffect", 0.1f, -1, -1, true);
	StringAttack->AutoSpriteSizeOn();
	StringAttack->Transform.SetLocalPosition({ 130.0f, -400.0f, 1.0f });
	StringAttack->Transform.SetLocalRotation({ 0.0f, 0.0f, 20.0f });
	StringAttack->ChangeAnimation("StringAttack");
	StringAttack->Off();
	//StringAttack->On();

	StringCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
	StringCol->SetCollisionType(ColType::OBBBOX2D);
	StringCol->Transform.SetLocalScale({ 26.0f, 760.0f, 1.0f});
	StringCol->Transform.SetLocalPosition({ 130.0f, -400.0f, 1.0f });
	StringCol->Transform.SetLocalRotation({ 0.0f, 0.0f, 20.0f });
	StringCol->Off();
	//StringCol->On();


	Hand->SetEndEvent("HandAppear", [&](GameEngineSpriteRenderer*)
		{
			Hand->ChangeAnimation("HandLoop");
		});

	Hand->SetFrameEvent("HandLoop", 9, [&](GameEngineSpriteRenderer*)
		{
			StringAttack->ChangeAnimation("StringAttack");
			StringAttack->On();
		});
	Hand->SetFrameEvent("HandLoop", 16, [&](GameEngineSpriteRenderer*)
		{
			HandEffect->ChangeAnimation("HandShooting");
			HandEffect->On();
		});
	Hand->SetFrameEvent("HandLoop", 17, [&](GameEngineSpriteRenderer*)
		{
			StringCol->On();
		});
	Hand->SetFrameEvent("HandLoop", 19, [&](GameEngineSpriteRenderer*)
		{
			StringCol->Off();
			String = false;
		});
	Hand->SetEndEvent("HandLoop", [&](GameEngineSpriteRenderer*)
		{
			Hand->ChangeAnimation("HandEnd");
		});

	HandEffect->SetEndEvent("HandShooting", [&](GameEngineSpriteRenderer*)
		{
			HandEffect->Off();
		});

	StringAttack->SetEndEvent("StringAttack", [&](GameEngineSpriteRenderer*)
		{
			StringAttack->Off();
		});

	GameEngineInput::AddInputObject(this);
}

void HandAttack::Update(float _Delta)
{
	if (GameEngineInput::IsDown('4', this))
	{
		Hand->ChangeAnimation("HandAppear");
	}
	if (GameEngineInput::IsDown('5', this))
	{
		Hand->ChangeAnimation("HandAttackBall");
	}
	if (GameEngineInput::IsDown('6', this))
	{
		Hand->ChangeAnimation("HandEnd");
	}
	if (GameEngineInput::IsDown('7', this))
	{
		Hand->ChangeAnimation("HandLoop");
		StringAttack->ChangeAnimation("StringAttack");
	}
	//if (GameEngineInput::IsDown('8', this))
	//{
	//	Hand->ChangeAnimation("HandLoop");
	//	HandEffect->ChangeAnimation("HandShooting");
	//	StringAttack->ChangeAnimation("StringEffect");
	//}

	if (String == false)
	{
		StringColEvent();
	}

	//StringCol->Collision(ContentsCollisionType::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
	//	{
	//		PlayerValue::GetValue()->AddRedDeathCount(1);
	//	}
	//);

	//if (Player::GetMainPlayer()->PlayerBind() ==)
}

void HandAttack::StringColEvent()
{
	StringEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			String = true;
			Player::GetMainPlayer()->PlayerBind();
			PlayerValue::GetValue()->AddRedDeathCount(1);
		};
	StringEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			String = true;
			Player::GetMainPlayer()->PlayerBind();
			PlayerValue::GetValue()->AddRedDeathCount(1);
		};
	StringCol->CollisionEvent(ContentsCollisionType::Player, StringEvent);
}

void HandAttack::LevelStart(GameEngineLevel* _PreveLevel)
{

}

void HandAttack::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}