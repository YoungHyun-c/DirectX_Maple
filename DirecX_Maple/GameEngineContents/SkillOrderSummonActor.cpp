#include "PreCompile.h"

#include "SkillOrderSummonActor.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "SkillManager.h"

#define Detect_XRange 1200
#define Detect_YRange 800

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
}

void SkillOrderSummonActor::Update(float _Delta)
{
	//Order->GetColorData().MulColor.A = 1.0f;
	
	Order->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });
	HitCollision->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });

	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		ChangeState(OrderState::Death);
	}

	StateUpdate(_Delta);
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
}
void SkillOrderSummonActor::AttackUpdate(float _Delta)
{
	HitCollision->Collision(ContentsCollisionType::Monster, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			// 가장 먼저 충돌
			GameEngineCollision* _Other = _CollisionGroup[0];
			ChangeState(OrderState::Hit);

			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, OrderHitCount, SkillValue::GetValue()->GetShardSkillDam(), SkillValue::GetValue()->GetShardFinalDam());

			SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Order_Hit", OrderHitCount);

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

				RotationSpeed = 360.0f;

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
		ChangeState(OrderState::Attack);
		HitTime = 0.0f;
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
	//Order->ChangeAnimation("TelePort");
}
void SkillOrderSummonActor::TelePortUpdate(float _Delta)
{
}
void SkillOrderSummonActor::GedderingStart()
{
}
void SkillOrderSummonActor::GedderingUpdate(float _Delta)
{
}
void SkillOrderSummonActor::BlossomStart()
{
}
void SkillOrderSummonActor::BlossomUpdate(float _Delta)
{
}
void SkillOrderSummonActor::DeathStart()
{
	Order->ChangeAnimation("Death");
	HitCollision->Off();
	DetectCollision->Off();
	//AppearTime = 0.0f;
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
