#include "PreCompile.h"
#include "SummonUi.h"
#include "Monster.h"
#include "Player.h"

SummonUi::SummonUi()
{

}

SummonUi::~SummonUi()
{

}

void SummonUi::Start()
{
	{
	GameEngineSprite::CreateSingle("SummonButton1.Png");
	GameEngineSprite::CreateSingle("SummonButton2.Png");
	GameEngineSprite::CreateSingle("SummonButton3.Png");
	GameEngineSprite::CreateSingle("SummonButton4.Png");

	GameEngineSprite::CreateSingle("ClearButton1.Png");
	GameEngineSprite::CreateSingle("ClearButton2.Png");
	GameEngineSprite::CreateSingle("ClearButton3.Png");
	GameEngineSprite::CreateSingle("ClearButton4.Png");
	}

	SummonButton = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	SummonButton->SetSprite("SummonButton1.png");
	SummonButton->Transform.SetLocalScale({ 1.5f, 1.5f });
	SummonButton->Transform.SetLocalPosition(SummonPos);

	{
		SummonCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::UI);
		SummonCol->SetCollisionType(ColType::AABBBOX2D);
		SummonCol->Transform.SetLocalScale({ 100.0f, 30.0f });
	}

	ClearButton = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	ClearButton->SetSprite("ClearButton4.png");
	ClearButton->AutoSpriteSizeOn();
	ClearButton->SetAutoScaleRatio(1.5f);
	ClearButton->Transform.SetLocalPosition(ClearPos);

	{
		ClearCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::UI);
		ClearCol->SetCollisionType(ColType::AABBBOX2D);
		ClearCol->Transform.SetLocalScale({ 100.0f, 30.0f, 1.0f });
	}

	TransformData Data = SummonCol->Transform.GetConstTransformDataRef();


}

void SummonUi::Update(float _Delta)
{
	PosUpdate();

	if (MonsterSummon == true)
	{
		SummonButton->SetSprite("SummonButton4.Png");
		Monster::Monsters->RendererOn();
	}
	else if (MonsterSummon == false)
	{
		Monster::Monsters->RendererOff();
		ClearButton->SetSprite("ClearButton4.Png");
	}

	// 소환
	if (MonsterSummon == false)
	{
		EventParameter SummonEvent;
		SummonEvent.Enter = [&](GameEngineCollision* _Mouse, GameEngineCollision* _This)
			{
				SummonButton->SetSprite("SummonButton2.Png");
			};
		SummonEvent.Stay = [&](GameEngineCollision* _Mouse, GameEngineCollision* _This)
			{
				if (GameEngineInput::IsPress(VK_LBUTTON))
				{
					SummonButton->SetSprite("SummonButton3.Png");
					ClearButton->SetSprite("ClearButton1.png");
					MonsterSummon = true;
				}
			};
		//SummonEvent.Exit = [&](GameEngineCollision* _Mouse, GameEngineCollision* _This)
		//	{
		//		if (MonsterSummon == true)
		//		{
		//			SummonButton->SetSprite("SummonButton4.Png");
		//		}
		//	};
	SummonCol->CollisionEvent(ContentsCollisionType::Mouse, SummonEvent);
	}

	// 소환해제
	if (MonsterSummon == true)
	{
		EventParameter ClearEvent;
		ClearEvent.Enter = [&](GameEngineCollision* _Mouse, GameEngineCollision* _This)
			{
				ClearButton->SetSprite("ClearButton2.Png");
			};
		ClearEvent.Stay = [&](GameEngineCollision* _Mouse, GameEngineCollision* _This)
			{
				if (GameEngineInput::IsPress(VK_LBUTTON))
				{
					ClearButton->SetSprite("ClearButton3.png");
					SummonButton->SetSprite("SummonButton1.Png");
					MonsterSummon = false;
				}
			};
		/*ClearEvent.Exit = [&](GameEngineCollision* _Mouse, GameEngineCollision* _This)
			{
				if (MonsterSummon == false)
				{
					ClearButton->SetSprite("ClearButton4.Png");
				}
			};*/
	ClearCol->CollisionEvent(ContentsCollisionType::Mouse, ClearEvent);
	}
}

void SummonUi::PosUpdate()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();

	SummonCol->Transform.SetLocalPosition({CameraPos.X + SummonPos.X, CameraPos.Y + SummonPos.Y });
	ClearCol->Transform.SetLocalPosition({ CameraPos.X + ClearPos.X, CameraPos.Y + ClearPos.Y });
}
