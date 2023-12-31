#include "PreCompile.h"

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#include "Player.h"
#include "Monster.h"
#include "AdeleSkill.h"
#include "SkillManager.h"
#include "SkillFunction.h"

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


	// 크리에이션
	//{
	//	Creation1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
	//	Creation1->AutoSpriteSizeOn();
	//	Creation1->CreateAnimation("Creation1", "Creation1_Special", 0.05f, -1, -1, false);
	//	Creation1->ChangeAnimation("Creation1");
	//	Creation1->Off();

	//	Creation2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
	//	Creation2->AutoSpriteSizeOn();
	//	Creation2->CreateAnimation("Creation2", "Creation2_Special", 0.05f, -1, -1, false);
	//	Creation2->ChangeAnimation("Creation2");
	//	Creation2->Off();

	//	Creation3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
	//	Creation3->AutoSpriteSizeOn();
	//	Creation3->CreateAnimation("Creation3", "Creation3_Special", 0.05f, -1, -1, false);
	//	Creation3->ChangeAnimation("Creation3");
	//	Creation3->Off();
	//}

	//// 샤드
	//{
	//	ShardEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	ShardEffect->AutoSpriteSizeOn();
	//	ShardEffect->CreateAnimation("ShardEffect", "Shard_Effect", 0.05f, -1, -1, false);
	//	ShardEffect->ChangeAnimation("ShardEffect");
	//	ShardEffect->Off();

	//	// new 라서 릭 남음 없애야됨
	//	//std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* ShardVect = new std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();
	//	//ShardVect->reserve(5);
	//	//std::vector<std::shared_ptr<GameEngineCollision>>* ShardC = new std::vector<std::shared_ptr<GameEngineCollision>>();
	//	//ShardC->reserve(5);
	//	//for (int i = 0; i <5; i++)
	//	//{
	//	//	ShardImage = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	//	ShardImage->Transform.SetLocalRotation({ 0, 0, -90.0f });
	//	//	ShardImage->AutoSpriteSizeOn();
	//	//	ShardImage->CreateAnimation("Shard", "Shard_Start", 0.05f, -1, -1, false);
	//	//	ShardImage->ChangeAnimation("Shard");
	//	//	ShardImage->Off();
	//	//	ShardVect->push_back(ShardImage);
	//	//	
	//	//	ShardCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	//	//	ShardCol->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	//	//	ShardCol->Transform.SetLocalScale({ 75.0f, 75.0f });
	//	//	ShardCol->SetCollisionType(ColType::AABBBOX2D);
	//	//	ShardCol->Off();
	//	//	ShardC->push_back(ShardCol);
	//	//}
	//	//Shard.push_back(ShardVect);
	//	//ShardCollist.push_back(ShardC);

	//	//ShardCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	//	//ShardCol->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	//	//ShardCol->Transform.SetLocalScale({ 75.0f, 75.0f });
	//	//ShardCol->Off();
	//}

	//// 임페일
	//{
	//	ImpaleA = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	ImpaleA->AutoSpriteSizeOn();
	//	ImpaleA->CreateAnimation("ImpaleA", "Impale_LayerA", 0.02f, -1, -1, false);
	//	ImpaleA->ChangeAnimation("ImpaleA");
	//	ImpaleA->Off();

	//	ImpaleB = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	ImpaleB->AutoSpriteSizeOn();
	//	ImpaleB->CreateAnimation("ImpaleB", "Impale_LayerB", 0.05f, -1, -1, false);
	//	ImpaleB->ChangeAnimation("ImpaleB");
	//	ImpaleB->Off();

	//	ImpaleE = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	ImpaleE->AutoSpriteSizeOn();
	//	ImpaleE->CreateAnimation("ImpaleE", "Impale_LayerE", 0.05f, -1, -1, false);
	//	ImpaleE->ChangeAnimation("ImpaleE");
	//	ImpaleE->Off();
	//}

	//// 레조넌스
	//{
	//	LesonensPrePare = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	LesonensPrePare->AutoSpriteSizeOn();
	//	LesonensPrePare->CreateAnimation("LesonensPrePare", "Lesonens_PrePare", 0.03f, -1, -1, false);
	//	LesonensPrePare->ChangeAnimation("LesonensPrePare");
	//	LesonensPrePare->Off();

	//	LessonensBack = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	LessonensBack->AutoSpriteSizeOn();
	//	LessonensBack->CreateAnimation("LessonensBack", "Lesonens_Back", 0.1f, -1, -1, false);
	//	LessonensBack->ChangeAnimation("LessonensBack");
	//	LessonensBack->Off();
	//	//LesonensEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	//LessonensEnd = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//}

	//// 루인
	//{
	//	Ruin = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	//	Ruin->AutoSpriteSizeOn();
	//	Ruin->CreateAnimation("Ruin", "10_Ruin", 0.1f, -1, -1, false);
	//	Ruin->ChangeAnimation("Ruin");
	//	Ruin->Off();
	//}
}

void AdeleSkill::LevelStart(GameEngineLevel* _PreveLevel)
{

}

void AdeleSkill::Update(float _Delta)
{
	//PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	
	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	
	if (UpdateFunc != nullptr)
	{
		UpdateFunc(*this);
	}
	
	if (true == ShradAppear)
	{
		Time += _Delta;
	}

	if (LimitTime <= Time)
	{
		std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = Shard.begin();
		std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = Shard.end();
		std::list<std::vector<std::shared_ptr<GameEngineCollision>>*>::iterator ShardColStart = ShardCollist.begin();
		std::list<std::vector<std::shared_ptr<GameEngineCollision>>*>::iterator ShardColEnd = ShardCollist.end();

		for (; Start != End; Start++, ShardColStart++)
		{
			std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* ShardVec = *Start;
			std::vector<std::shared_ptr<GameEngineCollision>>* ShardC = *ShardColStart;
			for (int i = 0; i < (*Start)->size(); i++)
			{
				float4 MonsterDir = Monster::Monsters->Transform.GetWorldPosition();
				float4 ShardDir = (*ShardVec)[i]->Transform.GetWorldPosition();
				float4 Dir = MonsterDir - ShardDir;
				Dir.Normalize();

				(*ShardVec)[i]->Transform.AddLocalPosition(Dir * _Delta * ShardSpeed);
				(*ShardC)[i]->Transform.AddLocalPosition(Dir * _Delta * ShardSpeed);

				float4 Angle = float4::Cross3D(MonsterDir, ShardDir);
				float Dot = float4::DotProduct3D(MonsterDir, ShardDir);
				float Result = acosf(Angle.Z);

				float ShardAngle = (- 60.0f - (15.0f * i));
				if (90.0f > Angle.Z && Angle.Z > 0.0f)
				{
					Angle.Z *= -1;
				}
				else
				{
					Angle.Z = Angle.Z;
				}

				if (MonsterDir.X - ShardDir.X <= 50.0f && ShardDir.X - MonsterDir.X <= 50.0f)
				{
					ShardAngle = -90.0f;
				}
				else if ((ShardAngle + Angle.Z) <= 0 && MonsterDir.X > ShardDir.X)
				{
					ShardAngle = -160.0f;
				}
				else
				{
					ShardAngle = -20.0f;
				}
				(*ShardVec)[i]->Transform.SetWorldRotation({ 0, 0, ShardAngle });
			}
		}
	}

	//{
	//	float4 MonsterDir = Monster::Monsters->Transform.GetWorldPosition();
	//	float4 ShardDir = ShardImage1->Transform.GetWorldPosition();
	//	float4 Dir = MonsterDir - ShardDir;
	//	//float4 ShardDir2 = ShardImage2->Transform.GetWorldPosition();
	//	//float4 Dir2 = MonsterDir - ShardDir2;
	//	Dir.Normalize();
	//	//Dir2.Normalize();
	//	
	//	ShardImage1->Transform.AddLocalPosition(Dir * _Delta * 600.0f);
	//	//ShardImage2->Transform.AddLocalPosition(Dir2 * _Delta * 600.0f);
	//	ShardCol->Transform.AddLocalPosition(Dir * _Delta * 600.0f);
	//	
	//	float4 Angle = float4::Cross3D(MonsterDir, ShardDir);
	//	float Dot = float4::DotProduct3D(MonsterDir, ShardDir);
	//	//float4 Result = DirectX::XMVector2AngleBetweenNormals(MonsterDir.DirectXVector, ShardDir.DirectXVector);
	//	float Result = acosf(Angle.Z);

	//	float ShardAngle = -90.0f ;
	//	if (90.0f> Angle.Z && Angle.Z > 0.0f)
	//	{
	//		Angle.Z *= -1;
	//	}
	//	else
	//	{
	//		Angle.Z = Angle.Z;
	//	}
	//	
	//	if (MonsterDir.X - ShardDir.X <= 50.0f && ShardDir.X - MonsterDir.X <= 50.0f)
	//	{
	//		ShardAngle = -90.0f;
	//	}
	//	else if ( (ShardAngle + Angle.Z) <= 0 && MonsterDir.X > ShardDir.X)
	//	{
	//		ShardAngle = -135.0f;
	//	}
	//	else if ((ShardAngle + Angle.Z) <= -180.0f && MonsterDir.X <= ShardDir.X)
	//	{
	//		ShardAngle = -45.0f;
	//	}
	//	ShardImage1->Transform.SetWorldRotation({0, 0, ShardAngle });
	//}

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
	PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	if (SkillName == "BoltJump")
	{
		UpJumpRenderer->Transform.SetWorldPosition({ PlayerPos.X, PlayerPos.Y - 50.0f, BackSkillPosZ });
		UpJumpRenderer->On();
	}
	else if (SkillName == "DoubleJump")
	{
		ActorDir Dir = Player::GetMainPlayer()->GetDir();
		switch (Dir)
		{
		case ActorDir::Left:
			DoubleJumpRenderer->Transform.SetWorldPosition({ PlayerPos.X + 100.0f, PlayerPos.Y, BackSkillPosZ });
			DoubleJumpRenderer->RightFlip();
			DoubleJumpRenderer->On();
			break;
		case ActorDir::Right:
			DoubleJumpRenderer->Transform.SetWorldPosition({ PlayerPos.X - 100.0f, PlayerPos.Y, BackSkillPosZ });
			DoubleJumpRenderer->LeftFlip();
			DoubleJumpRenderer->On();
			break;
		default:
			break;
		}
	}
	else if (SkillName == "Shard")
	{
		std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = Shard.begin();
		std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = Shard.end();

		std::list<std::vector<std::shared_ptr<GameEngineCollision>>*>::iterator ShardColStart = ShardCollist.begin();
		std::list<std::vector<std::shared_ptr<GameEngineCollision>>*>::iterator ShardColEnd = ShardCollist.end();

		for (; Start != End; Start++, ShardColStart++)
		{
			std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* ShardVec = *Start;
			std::vector<std::shared_ptr<GameEngineCollision>>* ShardC = *ShardColStart;
			int j = 0;
			for (int i = 0; i < (*Start)->size(); i++)
			{
				j = i;
				if (i >= 3)
				{
					j = 4 - i;
				}
				// j가 0 1 2 1 0
				(*ShardVec)[i]->Transform.SetLocalPosition({ (PlayerPos.X - 100.0f + i * 50.0f), (PlayerPos.Y + 60.0f + (j * 15.0f)) });
				(*ShardVec)[i]->Transform.SetLocalRotation({ 0.0f, 0.0f, -60.0f - (15.0f * i) });
				(*ShardVec)[i]->On();
				(*ShardC)[i]->Transform.SetWorldPosition({ (PlayerPos.X - 100.0f + i * 50.0f), (PlayerPos.Y + 60.0f + (j * 15.0f)) });
				(*ShardC)[i]->On();
			}
		}
		ShardEffect->Transform.SetWorldPosition({ PlayerPos.X, PlayerPos.Y + 75.0f });
		ShardEffect->On();

		//ShardCol->Transform.SetWorldPosition({ PlayerPos.X, PlayerPos.Y + 100.0f });
		//ShardCol->On();
		ShradAppear = true;
	}
	else if (SkillName == "Impale")
	{
		ActorDir Dir = Player::GetMainPlayer()->GetDir();
		switch (Dir)
		{
		case ActorDir::Left:
			ImpaleA->Transform.SetWorldPosition({ PlayerPos.X - 350.0f, PlayerPos.Y });
			ImpaleA->RightFlip();
			ImpaleA->On();
			ImpaleB->Transform.SetWorldPosition({ PlayerPos.X - 200.0f, PlayerPos.Y });
			ImpaleB->RightFlip();
			ImpaleB->On();
			ImpaleE->Transform.SetWorldPosition({ PlayerPos.X - 350.0f, PlayerPos.Y });
			ImpaleE->RightFlip();
			ImpaleE->On();
			break;
		case ActorDir::Right:
			ImpaleA->Transform.SetWorldPosition({ PlayerPos.X + 350.0f, PlayerPos.Y });
			ImpaleA->LeftFlip();
			ImpaleA->On();
			ImpaleB->Transform.SetWorldPosition({ PlayerPos.X + 300.0f, PlayerPos.Y });
			ImpaleB->LeftFlip();
			ImpaleB->On();
			ImpaleE->Transform.SetWorldPosition({ PlayerPos.X + 350.0f, PlayerPos.Y });
			ImpaleE->LeftFlip();
			ImpaleE->On();
			break;
		default:
			break;
		}
	}
	else if (SkillName == "Lesonens")
	{
		ActorDir Dir = Player::GetMainPlayer()->GetDir();
		switch (Dir)
		{
		case ActorDir::Left:
			/*LesonensPrePare->Transform.SetWorldPosition({ CurPlayerPos.X - 100.0f, PlayerPos.Y });
			LesonensPrePare->RightFlip();
			LesonensPrePare->On();*/
			LessonensBack->Transform.SetWorldPosition({ PlayerPos.X - 200.0f, PlayerPos.Y });
			LessonensBack->RightFlip();
			LessonensBack->On();
			break;
		case ActorDir::Right:
			/*LesonensPrePare->Transform.SetWorldPosition({ CurPlayerPos.X + 100.0f, PlayerPos.Y });
			LesonensPrePare->LeftFlip();
			LesonensPrePare->On();*/
			LessonensBack->Transform.SetWorldPosition({ PlayerPos.X + 200.0f, PlayerPos.Y });
			LessonensBack->LeftFlip();
			LessonensBack->On();
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
	else if (SkillName == "Shard")
	{
		UpdateFunc = &AdeleSkill::ShardSkill;
	}
	else if (SkillName == "Impale")
	{
		UpdateFunc = &AdeleSkill::ImpaleSkill;
	}
	else if (SkillName == "Lesonens")
	{
		UpdateFunc = &AdeleSkill::LesonensSkill;
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

void AdeleSkill::ShardSkill()
{
	if (ShardEffect->IsCurAnimationEnd())
	{
		ShardEffect->Off();
	}

	if (ShardImage->IsCurAnimationEnd())
	{
		//Shard->Off();
	}
}

void AdeleSkill::ImpaleSkill()
{
	if (ImpaleA->IsCurAnimationEnd())
	{
		ImpaleA->Off();
		ImpaleB->Off();
		ImpaleE->Off();
	}
}

void AdeleSkill::LesonensSkill()
{
	ActorDir Dir = Player::GetMainPlayer()->GetDir();
	switch (Dir)
	{
	case ActorDir::Left:
		LesonensPrePare->Transform.SetWorldPosition({ CurPlayerPos.X - 100.0f, PlayerPos.Y });
		LesonensPrePare->RightFlip();
		LesonensPrePare->On();
		break;
	case ActorDir::Right:
		LesonensPrePare->Transform.SetWorldPosition({ CurPlayerPos.X + 100.0f, PlayerPos.Y });
		LesonensPrePare->LeftFlip();
		LesonensPrePare->On();
		break;
	default:
		break;
	}

	if (LesonensPrePare->IsCurAnimationEnd())
	{
		LesonensPrePare->Off();
		LessonensBack->Off();
	}
}

//
//void AdeleSkill::AttackEvent()
//{
//	EventParameter HitEvent;
//
//	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
//		{
//			std::shared_ptr<DamageRenderer> NewDR = GetLevel()->CreateActor<DamageRenderer>();
//			NewDR->PushDamage(_Other, 6, 480, 220);
//		};
//	HitEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* _Other)
//		{
//			int a = 0;
//		};
//	AttackCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
//	AttackCol->CollisionEvent(ContentsCollisionType::Craving, HitEvent);
//}