#include "PreCompile.h"
//#include "GhostSwoo.h"
//
//GhostSwoo* GhostSwoo::SummonSwoo;
//
//GhostSwoo::GhostSwoo()
//{
//	MonsterName = static_cast<int>(MonstersName::GhostSwoo);
//	SummonSwoo = this;
//}
//
//GhostSwoo::~GhostSwoo()
//{
//
//}
//
//void GhostSwoo::Start()
//{
//	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
//	MonsterRenderer->CreateAnimation("Regen", "GhostSwoo_Regen", 0.1f, -1, -1, false);
//	MonsterRenderer->CreateAnimation("Stand", "GhostSwoo_Stand", 0.1f, -1, -1, true);
//	MonsterRenderer->CreateAnimation("Move", "GhostSwoo_Move", 0.1f, -1, -1, true);
//	MonsterRenderer->CreateAnimation("Attack", "GhostSwoo_Attack", 0.1f, -1, -1, false);
//	MonsterRenderer->CreateAnimation("Skill1", "GhostSwoo_Skill1", 0.1f, -1, -1, false); // 순간이동
//	MonsterRenderer->CreateAnimation("Skill1After", "GhostSwoo_Skill1After", 0.1f, -1, -1, false); // 순간이동 후
//	MonsterRenderer->CreateAnimation("Skill2", "GhostSwoo_Skill2", 0.1f, -1, -1, false);
//	MonsterRenderer->CreateAnimation("Death", "GhostSwoo_Death", 0.1f, -1, -1, false);
//	
//	// 볼은 따로 클래스 만드는게 나을까 생각듬
//	//BallSprite = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
//	//BallSprite->CreateAnimation("Ball_Regen", "BounceBall_Regen", 0.1f, -1, -1, false);
//	//BallSprite->CreateAnimation("Ball_Loop", "BounceBall_Loop", 0.1f, -1, -1, true);
//	//BallSprite->ChangeAnimation("Ball_Regen");
//	//BallSprite->AutoSpriteSizeOn();
//	//BallSprite->Off();
//
//	MonsterRenderer->ChangeAnimation("Stand");
//	MonsterRenderer->AutoSpriteSizeOn();
//	MonsterRenderer->SetPivotType(PivotType::Bottom);
//	MonsterRenderer->Off();
//
//	MonsterCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
//	MonsterCollision->Transform.SetLocalScale({ 75.0f, 130.0f });
//	MonsterCollision->SetCollisionType(ColType::AABBBOX2D);
//	MonsterCollision->Off();
//
//	SetMoveSpeed(MoveSpeed);
//
//	SetColPos(0, 0, 150.0f);
//}
//
//void GhostSwoo::Update(float _Delta)
//{
//	MonsterFunction::Update(_Delta);
//
//	TimeCounting();
//	StateUpdate(_Delta);
//
//	if (GameEngineInput::IsDown('5'))
//	{
//		MonsterRenderer->On();
//		MonsterCollision->On();
//		//BallSprite->On();
//		ChangeState(MonsterState::Regen);
//	}
//	if (GameEngineInput::IsDown('6'))
//	{
//		ChangeState(MonsterState::Attack);
//	}
//	if (GameEngineInput::IsDown('7'))
//	{
//		//ChangeState(MonsterState::Die);
//		MonsterRenderer->ChangeAnimation("Skill1After");
//	}
//	if (GameEngineInput::IsDown('8'))
//	{
//		ChangeState(MonsterState::Skill1);
//	}
//	if (GameEngineInput::IsDown('9'))
//	{
//		ChangeState(MonsterState::Skill2);
//	}
//
//	if (GameEngineInput::IsDown('0'))
//	{
//		ChangeState(MonsterState::Death);
//	}
//
//	DirCheck();
//	InsideLockMap();
//}
//
//void GhostSwoo::DeathUpdate(float _Delta)
//{
//
//}
//
////void GhostSwoo::InsideLockMap()
////{
////	if (Dir == ActorDir::Left)
////	{
////		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X,
////			MonsterRenderer->Transform.GetLocalPosition().Y + 150.0f });
////	}
////	else if (Dir == ActorDir::Right)
////	{
////		MonsterCollision->Transform.SetLocalPosition({ MonsterRenderer->Transform.GetLocalPosition().X ,
////	MonsterRenderer->Transform.GetLocalPosition().Y + 150.0f });
////	}
////}