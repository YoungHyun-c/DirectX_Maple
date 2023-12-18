#include "PreCompile.h"

#include "BaseSummonActor.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "SkillManager.h"

#define Detect_XRange 1000
#define Detect_YRange 700

BaseSummonActor::BaseSummonActor()
{

}

BaseSummonActor::~BaseSummonActor()
{

}

void BaseSummonActor::Start()
{
	if (nullptr == Wonder)
	{
		Wonder = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
		Wonder->Transform.SetLocalPosition({ 0, 0, 1 });
		Wonder->AutoSpriteSizeOn();
	}

	if (nullptr == HitCollision)
	{
		HitCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		HitCollision->SetCollisionType(ColType::OBBBOX2D);
	}

	if (nullptr == DetectCollision)
	{
		DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::SkillRange);
	}
}

void BaseSummonActor::Update(float _Delta)
{
	
	Wonder->GetColorData().MulColor.A = 1.0f;


	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		ChangeState(WonderState::Death);
	}

	StateUpdate(_Delta);
}


void BaseSummonActor::ChangeState(WonderState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case WonderState::Start:
			ReadyStart();
			break;
		case WonderState::Attack:
			AttackStart();
			break;
		case WonderState::Hit:
			HitStart();
			break;
		case WonderState::Death:
			DeathStart();
			break;
		case WonderState::Max:
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 Wonder를 시작하려 했습니다.");
			break;
		}
	}

	State = _State;
}


void BaseSummonActor::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WonderState::Start:
		return ReadyUpdate(_Delta);
	case WonderState::Attack:
		return AttackUpdate(_Delta);
	case WonderState::Hit:
		return HitUpdate(_Delta);
	case WonderState::Death:
		return DeathUpdate(_Delta);
	case WonderState::Max:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Wonder Update를 하려했습니다.");
		break;
	}
}


void BaseSummonActor::ReadyStart()
{
	Wonder->ChangeAnimation("Start");

}

void BaseSummonActor::ReadyUpdate(float _Delta)
{
	AttackUpdate(_Delta);
}

void BaseSummonActor::AttackStart()
{
	Wonder->ChangeAnimation("Attack");
}

void BaseSummonActor::AttackUpdate(float _Delta)
{
	Wonder->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });
	HitCollision->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });

	HitCollision->Collision(ContentsCollisionType::Monster, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			// 가장 먼저 충돌
			GameEngineCollision* _Other = _CollisionGroup[0];
			ChangeState(WonderState::Death);

			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, WonderHitCount, SkillValue::GetValue()->GetShardSkillDam(), SkillValue::GetValue()->GetShardFinalDam());

			SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Shard_Hit", WonderHitCount);

			PlayerValue::GetValue()->AddAtere(10);
		});
	
	AppearTime += _Delta;
	if (AttackTime <= AppearTime)
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

				RotationSpeed += 40.0f * _Delta;

				MoveVector = float4::GetUnitVectorFromDeg(DirAngle);

				Transform.AddLocalPosition(MoveVector * Speed * _Delta);

			});
	}
}

void BaseSummonActor::DeathStart()
{
	Wonder->ChangeAnimation("Death");
	HitCollision->Off();
	DetectCollision->Off();
	AppearTime = 0.0f;
}

void BaseSummonActor::DeathUpdate(float _Delta)
{
}

void BaseSummonActor::HitStart()
{
	HitCollision->Off();
	DetectCollision->Off();
}

void BaseSummonActor::HitUpdate(float _Delta)
{
}

void BaseSummonActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BaseSummonActor::Release()
{
	if (nullptr != Wonder)
	{
		Wonder->Death();
		Wonder = nullptr;
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