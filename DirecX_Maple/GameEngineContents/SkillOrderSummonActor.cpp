#include "PreCompile.h"

#include "SkillOrderSummonActor.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "SkillManager.h"

#define Detect_XRange 1200
#define Detect_YRange 1000

SkillOrderSummonActor::SkillOrderSummonActor()
{
}
SkillOrderSummonActor::~SkillOrderSummonActor()
{
}

void SkillOrderSummonActor::Start()
{
	if (nullptr == Order)
	{
		Order = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Order->Transform.SetLocalPosition({ 0, 0, 1 });
		Order->AutoSpriteSizeOn();
	}

	if (nullptr == HitCollision)
	{
		HitCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		HitCollision->SetCollisionType(ColType::OBBBOX2D);
	}

	if (nullptr == DetectCollision)
	{
		DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::SkillRange);
		DetectCollision->SetCollisionType(ColType::OBBBOX2D);
	}

	if (nullptr == GedderingHitCollision)
	{
		GedderingHitCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::SkillRange);
		GedderingHitCollision->SetCollisionType(ColType::OBBBOX2D);
	}

	if (nullptr == BlossomHitCollision)
	{
		BlossomHitCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::SkillRange);
		BlossomHitCollision->SetCollisionType(ColType::OBBBOX2D);
	}

	GameEngineInput::AddInputObject(this);
}

void SkillOrderSummonActor::Update(float _Delta)
{
	//Order->GetColorData().MulColor.A = 1.0f;

	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	
	Order->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });
	HitCollision->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });

	StateUpdate(_Delta);

	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		ChangeState(OrderState::Death);
		return;
	}

	if (GameEngineInput::IsDown('S', this) == true)
	{
		ChangeState(OrderState::Geddering);
		return;
	}

	if (GameEngineInput::IsDown(VK_END, this) == true)
	{
		ChangeState(OrderState::Blossom);
		return;
	}

}

void SkillOrderSummonActor::ChangeState(OrderState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case OrderState::Start:
			ReadyStart();
			break;
		case OrderState::Attack:
			AttackStart();
			break;
		case OrderState::Hit:
			HitStart();
			break;
		case OrderState::Loop:
			LoopStart();
			break;
		case OrderState::TelePort:
			TelePortStart();
			break;
		case OrderState::Geddering:
			GedderingStart();
			break;
		case OrderState::Blossom:
			BlossomStart();
			break;
		case OrderState::Death:
			DeathStart();
			break;
		case OrderState::Max:
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 Order를 시작하려 했습니다.");
			break;
		}
	}

	State = _State;
}

void SkillOrderSummonActor::StateUpdate(float _Delta)
{
	switch (State)
	{
	case OrderState::Start:
		return ReadyUpdate(_Delta);
	case OrderState::Attack:
		return AttackUpdate(_Delta);
	case OrderState::Hit:
		return HitUpdate(_Delta);
	case OrderState::Loop:
		return LoopUpdate(_Delta);
	case OrderState::TelePort:
		return TelePortUpdate(_Delta);
	case OrderState::Geddering:
		return GedderingUpdate(_Delta);
	case OrderState::Blossom:
		return BlossomUpdate(_Delta);
	case OrderState::Death:
		return DeathUpdate(_Delta);
	case OrderState::Max:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Order Update를 하려했습니다.");
		break;
	}
}

void SkillOrderSummonActor::ReadyStart()
{
	Order->ChangeAnimation("Start");
	BlossomHitCollision->Off();
	GedderingHitCollision->Off();
}
void SkillOrderSummonActor::ReadyUpdate(float _Delta)
{
	if (Order->IsCurAnimationEnd() == true)
	{
		AttackUpdate(_Delta);
	}
}

void SkillOrderSummonActor::AttackStart()
{
	Order->ChangeAnimation("Attack");
	HitCollision->On();
	DetectCollision->On();
	BlossomHitCollision->Off();
	GedderingHitCollision->Off();
}
void SkillOrderSummonActor::AttackUpdate(float _Delta)
{
	TelePortTime += _Delta;
	if (TelePortLimitTime < TelePortTime)
	{
		ChangeState(OrderState::TelePort);
		return;
	}

	HitCollision->Collision(ContentsCollisionType::Monster, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			// 가장 먼저 충돌
			GameEngineCollision* _Other = _CollisionGroup[0];
			ChangeState(OrderState::Hit);

			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, OrderHitCount, SkillValue::GetValue()->GetShardSkillDam(), SkillValue::GetValue()->GetShardFinalDam());

			SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Order_Hit", OrderHitCount);

			TelePortTime = 0.0f;
			//Order->Transform.AddLocalPosition(Speed * _Delta);
		});

	{
		DetectCollision->Collision(ContentsCollisionType::Monster, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
			{
				// 타겟
				float4 CloseTargetPos = float4::ZERO;
				float4 CurPos = Transform.GetWorldPosition();

				for (size_t i = 0; i < _CollisionGroup.size(); i++)
				{
					GameEngineCollision* _Other = _CollisionGroup[i];
					float4 OtherPos = _Other->GetParentObject()->Transform.GetWorldPosition();

					if ((CloseTargetPos - CurPos).Size() > (OtherPos - CurPos).Size() || CloseTargetPos == float4::ZERO)
					{
						CloseTargetPos = OtherPos;
					}
				}

				float4 DirVector = (CloseTargetPos - CurPos).NormalizeReturn();

				float4 Angle = DirectX::XMVector2AngleBetweenNormals(DirVector.DirectXVector, MoveVector.DirectXVector);

				float PlusAngle = Angle.X * GameEngineMath::R2D;

				float4 RotationDir = DirectX::XMVector2Cross(DirVector.DirectXVector, MoveVector.DirectXVector);

				if (0.0f <= RotationDir.X)
				{
					DirAngle -= PlusAngle * RotationSpeed * _Delta;
				}
				else
				{
					DirAngle += PlusAngle * RotationSpeed * _Delta;
				}

				RotationSpeed = 60.0f;

				MoveVector = float4::GetUnitVectorFromDeg(DirAngle);

				Transform.AddLocalPosition(MoveVector * Speed * _Delta);

			});
	}
}

void SkillOrderSummonActor::HitStart()
{
	HitCollision->Off();
	DetectCollision->Off();
}

void SkillOrderSummonActor::HitUpdate(float _Delta)
{
	HitTime += _Delta;

	DirAngle += 280 *_Delta;
	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);
	Transform.AddLocalPosition(MoveVector * _Delta * 1400.0f);
	if (HitTime >= 0.5f)
	{
		HitTime = 0.0f;
		ChangeState(OrderState::Attack);
		return;
	}
}

void SkillOrderSummonActor::LoopStart()
{
}
void SkillOrderSummonActor::LoopUpdate(float _Delta)
{
}
void SkillOrderSummonActor::TelePortStart()
{
	Order->ChangeAnimation("TelePort");
	TelePortTime = 0.0f;
	TelePort_X = static_cast<float>(Random_XRange.RandomInt(-4, 4));
	TelePort_Y = static_cast<float>(Random_YRange.RandomInt(-3, 3));
}
void SkillOrderSummonActor::TelePortUpdate(float _Delta)
{
	Transform.SetWorldPosition({ CurPlayerPos.X + TelePort_X * 100.0f, CurPlayerPos.Y + TelePort_Y * 100.0f });
	if (Order->IsCurAnimationEnd() == true)
	{
		ChangeState(OrderState::Attack);
		return;
	}
}
void SkillOrderSummonActor::GedderingStart()
{
	Order->ChangeAnimation("Geddering");
	DirAngle -= DirAngle;

	HitCollision->Off();
	DetectCollision->Off();

	GedderingHitCollision->On();

	GedderingPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
}
void SkillOrderSummonActor::GedderingUpdate(float _Delta)
{
	GedderingDir = GedderingPos - Transform.GetWorldPosition();
	GedderingDir.Normalize();
	if (GedderingDir.X < 0)
	{
		Order->RightFlip();
	}
	else
	{
		Order->LeftFlip();
	}
	Transform.AddLocalPosition(GedderingDir * 2500.0f * _Delta);
	
	if (Order->IsCurAnimationEnd() == true)
	{
		Order->LeftFlip();
		GedderingHitCollision->Off();
		ChangeState(OrderState::Attack);
		return;
	}

	AttackEvent();
}
void SkillOrderSummonActor::BlossomStart()
{
	Order->ChangeAnimation("Blossom");
	GedderingHitCollision->Off();
}
void SkillOrderSummonActor::BlossomUpdate(float _Delta)
{
	if (Order->IsCurAnimationEnd() == true)
	{
		BlossomHit = false;
		BlossomHitCollision->Off();
		ChangeState(OrderState::Attack);
		return;
	}

	AttackEvent();
}
void SkillOrderSummonActor::AttackEvent()
{
	GedderingHitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, GedderingHitCount, SkillValue::GetValue()->GetGedderingSkillDam(), SkillValue::GetValue()->GetGedderingFinalDam());

			SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Geddering_Hit", GedderingHitCount);

			TelePortTime = 0.0f;
		};
	GedderingHitCollision->CollisionEvent(ContentsCollisionType::Monster, GedderingHitEvent);


	BlossomHitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, BlossomHitCount, SkillValue::GetValue()->GetBlossomSkillDam(), SkillValue::GetValue()->GetBlossomFinalDam());

			SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Blossom_Hit", BlossomHitCount);

			TelePortTime = 0.0f;
		};
	BlossomHitEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			if (BlossomHit == true)
			{
				return;
			}
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, BlossomHitCount, SkillValue::GetValue()->GetBlossomSkillDam(), SkillValue::GetValue()->GetBlossomFinalDam());

			SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Blossom_Hit", BlossomHitCount);

			TelePortTime = 0.0f;
			BlossomHit = true;
		};
	BlossomHitCollision->CollisionEvent(ContentsCollisionType::Monster, BlossomHitEvent);

}
void SkillOrderSummonActor::DeathStart()
{
	Order->ChangeAnimation("Death");
	HitCollision->Off();
	DetectCollision->Off();

}
void SkillOrderSummonActor::DeathUpdate(float _Delta)
{
}

void SkillOrderSummonActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void SkillOrderSummonActor::Release()
{
	if (nullptr != Order)
	{
		Order->Death();
		Order = nullptr;
	}

	if (nullptr != HitCollision)
	{
		HitCollision->Death();
		HitCollision = nullptr;
	}

	if (nullptr != DetectCollision)
	{
		DetectCollision->Death();
		DetectCollision = nullptr;
	}
}
