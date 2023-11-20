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

	StringAttack1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	StringAttack1->CreateAnimation("StringAttack", "StringAttack", 0.1f, -1, -1, true);
	StringAttack1->CreateAnimation("StringEffect", "StringEffect", 0.1f, -1, -1, true);
	StringAttack1->AutoSpriteSizeOn();
	StringAttack1->Transform.SetLocalPosition({ -100.0f, -400.0f, 1.0f });
	StringAttack1->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
	StringAttack1->ChangeAnimation("StringAttack");
	StringAttack1->Off();

	StringAttack2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	StringAttack2->CreateAnimation("StringAttack", "StringAttack", 0.1f, -1, -1, true);
	StringAttack2->CreateAnimation("StringEffect", "StringEffect", 0.1f, -1, -1, true);
	StringAttack2->AutoSpriteSizeOn();
	StringAttack2->Transform.SetLocalPosition({ -90.0f, -300.0f, 1.0f });
	StringAttack2->Transform.SetLocalRotation({ 0.0f, 0.0f, -10.0f });
	StringAttack2->ChangeAnimation("StringAttack");
	StringAttack2->Off();

	StringAttack3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	StringAttack3->CreateAnimation("StringAttack", "StringAttack", 0.1f, -1, -1, true);
	StringAttack3->CreateAnimation("StringEffect", "StringEffect", 0.1f, -1, -1, true);
	StringAttack3->AutoSpriteSizeOn();
	StringAttack3->Transform.SetLocalPosition({ 40.0f, -300.0f, 1.0f });
	StringAttack3->Transform.SetLocalRotation({ 0.0f, 0.0f, 10.0f });
	StringAttack3->ChangeAnimation("StringAttack");
	StringAttack3->Off();

	StringAttack4 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	StringAttack4->CreateAnimation("StringAttack", "StringAttack", 0.1f, -1, -1, true);
	StringAttack4->CreateAnimation("StringEffect", "StringEffect", 0.1f, -1, -1, true);
	StringAttack4->AutoSpriteSizeOn();
	StringAttack4->Transform.SetLocalPosition({ 40.0f, -390.0f, 1.0f });
	StringAttack4->Transform.SetLocalRotation({ 0.0f, 0.0f, -3.0f });
	StringAttack4->ChangeAnimation("StringAttack");
	StringAttack4->Off();

	StringAttack5 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	StringAttack5->CreateAnimation("StringAttack", "StringAttack", 0.1f, -1, -1, true);
	StringAttack5->CreateAnimation("StringEffect", "StringEffect", 0.1f, -1, -1, true);
	StringAttack5->AutoSpriteSizeOn();
	StringAttack5->Transform.SetLocalPosition({ 120.0f, -300.0f, 1.0f });
	StringAttack5->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
	StringAttack5->ChangeAnimation("StringAttack");
	StringAttack5->Off();


	StringCol1 = CreateComponent<GameEngineCollision>(ContentsCollisionType::String);
	StringCol1->SetCollisionType(ColType::OBBBOX2D);
	StringCol1->Transform.SetLocalScale({ 26.0f, 760.0f, 1.0f});
	StringCol1->Transform.SetLocalPosition({ -100.0f, -400.0f, 1.0f });
	StringCol1->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
	StringCol1->Off();

	StringCol2 = CreateComponent<GameEngineCollision>(ContentsCollisionType::String);
	StringCol2->SetCollisionType(ColType::OBBBOX2D);
	StringCol2->Transform.SetLocalScale({ 26.0f, 760.0f, 1.0f });
	StringCol2->Transform.SetLocalPosition({ -90.0f, -300.0f, 1.0f });
	StringCol2->Transform.SetLocalRotation({ 0.0f, 0.0f, -10.0f });
	StringCol2->Off();

	StringCol3 = CreateComponent<GameEngineCollision>(ContentsCollisionType::String);
	StringCol3->SetCollisionType(ColType::OBBBOX2D);
	StringCol3->Transform.SetLocalScale({ 26.0f, 760.0f, 1.0f });
	StringCol3->Transform.SetLocalPosition({ 40.0f, -300.0f, 1.0f });
	StringCol3->Transform.SetLocalRotation({ 0.0f, 0.0f, 10.0f });
	StringCol3->Off();

	StringCol4 = CreateComponent<GameEngineCollision>(ContentsCollisionType::String);
	StringCol4->SetCollisionType(ColType::OBBBOX2D);
	StringCol4->Transform.SetLocalScale({ 26.0f, 760.0f, 1.0f });
	StringCol4->Transform.SetLocalPosition({ 40.0f, -390.0f, 1.0f  });
	StringCol4->Transform.SetLocalRotation({ 0.0f, 0.0f, -3.0f });
	StringCol4->Off();

	StringCol5 = CreateComponent<GameEngineCollision>(ContentsCollisionType::String);
	StringCol5->SetCollisionType(ColType::OBBBOX2D);
	StringCol5->Transform.SetLocalScale({ 26.0f, 760.0f, 1.0f });
	StringCol5->Transform.SetLocalPosition({ 120.0f, -300.0f, 1.0f });
	StringCol5->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
	StringCol5->Off();



	Hand->SetEndEvent("HandAppear", [&](GameEngineSpriteRenderer*)
		{
			Hand->ChangeAnimation("HandLoop");
		});

	Hand->SetFrameEvent("HandLoop", 9, [&](GameEngineSpriteRenderer*)
		{
			StringAttack1->ChangeAnimation("StringAttack");
			StringAttack1->On();
			StringAttack2->ChangeAnimation("StringAttack");
			StringAttack2->On();
			StringAttack3->ChangeAnimation("StringAttack");
			StringAttack3->On();
			StringAttack4->ChangeAnimation("StringAttack");
			StringAttack4->On();
			StringAttack5->ChangeAnimation("StringAttack");
			StringAttack5->On();
		});
	Hand->SetFrameEvent("HandLoop", 16, [&](GameEngineSpriteRenderer*)
		{
			HandEffect->ChangeAnimation("HandShooting");
			HandEffect->On();
		});
	Hand->SetFrameEvent("HandLoop", 17, [&](GameEngineSpriteRenderer*)
		{
			StringCol1->On();
			StringCol2->On();
			StringCol3->On();
			StringCol4->On();
			StringCol5->On();
		});
	Hand->SetFrameEvent("HandLoop", 19, [&](GameEngineSpriteRenderer*)
		{
			StringCol1->Off();
			StringCol2->Off();
			StringCol3->Off();
			StringCol4->Off();
			StringCol5->Off();
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

	StringAttack1->SetEndEvent("StringAttack", [&](GameEngineSpriteRenderer*)
		{
			StringAttack1->Off();
			StringAttack2->Off();
			StringAttack3->Off();
			StringAttack4->Off();
			StringAttack5->Off();
		});

	HandCoolTime = RanCoolTime.RandomFloat(7.0f, 14.0f);

}

void HandAttack::Update(float _Delta)
{
	HandAttackTime += _Delta;
	if (HandAttackTime >= HandCoolTime)
	{
		Hand->ChangeAnimation("HandAppear");
		HandCoolTime = RanCoolTime.RandomFloat(7.0f, 12.0f);
		HandAttackTime = 0.0f;
	}


	//if (Player::GetMainPlayer()->GetBindValue() == false && GlobalValue::GetNeedGlobalValue()->GetSickleCutValue() == false)
	if (GlobalValue::GetNeedGlobalValue()->GetSickleCutValue() == false)
	{
		if (String == false)
		{
			StringColEvent();
		}
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
	if (String == false)
	{
		StringCol1->CollisionEvent(ContentsCollisionType::Player, StringEvent);
	}
	if (String == false)
	{
		StringCol2->CollisionEvent(ContentsCollisionType::Player, StringEvent);
	}
	if (String == false)
	{
		StringCol3->CollisionEvent(ContentsCollisionType::Player, StringEvent);
	}
	if (String == false)
	{
		StringCol4->CollisionEvent(ContentsCollisionType::Player, StringEvent);
	}
	if (String == false)
	{
		StringCol5->CollisionEvent(ContentsCollisionType::Player, StringEvent);
	}
}

void HandAttack::LevelStart(GameEngineLevel* _PreveLevel)
{

}

void HandAttack::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}