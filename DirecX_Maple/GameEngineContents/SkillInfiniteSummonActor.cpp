#include "PreCompile.h"

#include "SkillInfiniteSummonActor.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "SkillManager.h"

#define Detect_XRange 1500
#define Detect_YRange 1500

SkillInfiniteSummonActor::SkillInfiniteSummonActor()
{

}

SkillInfiniteSummonActor::~SkillInfiniteSummonActor()
{

}

void SkillInfiniteSummonActor::Start()
{
	if (nullptr == InfiOrder)
	{
		InfiOrder = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		InfiOrder->Transform.SetLocalPosition({ 0, 0, 1 });
		InfiOrder->AutoSpriteSizeOn();
	}

	if (nullptr == DetectCollision)
	{
		DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::SkillRange);
		DetectCollision->SetCollisionType(ColType::OBBBOX2D);
	}

	if (nullptr == HitCollision)
	{
		HitCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		HitCollision->SetCollisionType(ColType::OBBBOX2D);
	}

}

void SkillInfiniteSummonActor::Update(float _Delta)
{

	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();

	InfiOrder->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });

	HitCollision->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });

	StateUpdate(_Delta);

	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		ChangeState(InfiOrderState::Death);
		return;
	}
}

void SkillInfiniteSummonActor::ChangeState(InfiOrderState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case InfiOrderState::Start:
			ReadyStart();
			break;
		case InfiOrderState::Attack:
			AttackStart();
			break;
		case InfiOrderState::Hit:
			HitStart();
			break;
		case InfiOrderState::TelePort:
			TelePortStart();
			break;
		case InfiOrderState::Death:
			DeathStart();
			break;
		case InfiOrderState::Max:
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 Order를 시작하려 했습니다.");
			break;
		}
	}

	State = _State;
}

void SkillInfiniteSummonActor::StateUpdate(float _Delta)
{
	switch (State)
	{
	case InfiOrderState::Start:
		return ReadyUpdate(_Delta);
	case InfiOrderState::Attack:
		return AttackUpdate(_Delta);
	case InfiOrderState::Hit:
		return HitUpdate(_Delta);
	case InfiOrderState::TelePort:
		return TelePortUpdate(_Delta);
	case InfiOrderState::Death:
		return DeathUpdate(_Delta);
	case InfiOrderState::Max:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Order Update를 하려했습니다.");
		break;
	}
}


void SkillInfiniteSummonActor::ReadyStart()
{
	InfiOrder->ChangeAnimation("Start");
}

void SkillInfiniteSummonActor::ReadyUpdate(float _Delta)
{
	if (InfiOrder->IsCurAnimationEnd() == true)
	{
		AttackUpdate(_Delta);
	}
}

void SkillInfiniteSummonActor::AttackStart()
{
	InfiOrder->ChangeAnimation("Attack");
	HitCollision->On();
	DetectCollision->On();
}

void SkillInfiniteSummonActor::AttackUpdate(float _Delta)
{
	TelePortTime += _Delta;
	if (TelePortLimitTime < TelePortTime)
	{
		ChangeState(InfiOrderState::TelePort);
		return;
	}

	HitCollision->Collision(ContentsCollisionType::Monster, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			// 가장 먼저 충돌
			GameEngineCollision* _Other = _CollisionGroup[0];
			ChangeState(InfiOrderState::Hit);

			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, InfiOrderHitCount, 770, 220);

			SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Infinite_Hit", InfiOrderHitCount);

			TelePortTime = 0.0f;
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

void SkillInfiniteSummonActor::HitStart()
{
	HitCollision->Off();
	DetectCollision->Off();
}

void SkillInfiniteSummonActor::HitUpdate(float _Delta)
{
	HitTime += _Delta;

	DirAngle += 280 * _Delta;
	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);
	Transform.AddLocalPosition(MoveVector * _Delta * 1400.0f);
	if (HitTime >= 0.5f)
	{
		HitTime = 0.0f;
		ChangeState(InfiOrderState::Attack);
		return;
	}
}

void SkillInfiniteSummonActor::TelePortStart()
{
	InfiOrder->ChangeAnimation("TelePort");
	TelePortTime = 0.0f;
	TelePort_X = static_cast<float>(Random_XRange.RandomInt(-4, 4));
	TelePort_Y = static_cast<float>(Random_YRange.RandomInt(-3, 3));
}
void SkillInfiniteSummonActor::TelePortUpdate(float _Delta)
{
	Transform.SetWorldPosition({ CurPlayerPos.X + TelePort_X * 100.0f, CurPlayerPos.Y + TelePort_Y * 100.0f });
	if (InfiOrder->IsCurAnimationEnd() == true)
	{
		ChangeState(InfiOrderState::Attack);
		return;
	}
}

void SkillInfiniteSummonActor::DeathStart()
{
	InfiOrder->ChangeAnimation("Death");
	HitCollision->Off();
	DetectCollision->Off();
	SkillValue::GetValue()->SubOrderCount(1);
}
void SkillInfiniteSummonActor::DeathUpdate(float _Delta)
{
}

void SkillInfiniteSummonActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void SkillInfiniteSummonActor::Release()
{
	if (nullptr != InfiOrder)
	{
		InfiOrder->Death();
		InfiOrder = nullptr;
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
