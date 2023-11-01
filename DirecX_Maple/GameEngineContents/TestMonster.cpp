#include "PreCompile.h"
#include "TestMonster.h"

TestMonster::TestMonster()
{

}

TestMonster::~TestMonster()
{

}

void TestMonster::Start()
{
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	MonsterRenderer->CreateAnimation("Regen", "GhostDamien_Regen", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Stand", "GhostDamien_Stand", 0.1f, -1, -1, true);
	MonsterRenderer->CreateAnimation("Attack", "GhostDamien_Attack", 0.1f, -1, -1, false); // 슬라이드 공격(밀격)
	MonsterRenderer->CreateAnimation("Skill1", "GhostDamien_Skill1", 0.1f, -1, -1, false); // 걸어서 움직이지 않음 플레이어 주변에 순간이동
	MonsterRenderer->CreateAnimation("Skill1After", "GhostDamien_Skill1After", 0.1f, -1, -1, false); // 순간이동 후
	MonsterRenderer->CreateAnimation("Skill2", "GhostDamien_Skill2", 0.1f, -1, -1, false); // 
	MonsterRenderer->CreateAnimation("Skill2After", "GhostDamien_Skill2After", 0.1f, -1, -1, false);
	MonsterRenderer->CreateAnimation("Death", "GhostDamien_Death", 0.1f, -1, -1, false);

	MonsterRenderer->ChangeAnimation("Stand");
	MonsterRenderer->AutoSpriteSizeOn();
	MonsterRenderer->SetPivotType(PivotType::Bottom);
	MonsterRenderer->Off();
}

void TestMonster::Update(float _Delta)
{
	MonsterFunction::Update(_Delta);

	//TimeCounting();
	//StateUpdate(_Delta);

	if (GameEngineInput::IsDown('5', this))
	{
		MonsterRenderer->On();
	//	MonsterCollision->On();
	//	//BallSprite->On();
		MonsterRenderer->LeftFlip();
		Dir = ActorDir::Right;
		ChangeState(MonsterState::Regen);
	}
	//if (GameEngineInput::IsDown('6', this))
	//{
	//	ChangeState(MonsterState::Attack);
	//	HitEffect->On();
	//	HitEffect->ChangeAnimation("BackEffect");
	//	//HitEffect->Transform.SetLocalPosition({ -50.0f });
	//}
	//if (GameEngineInput::IsDown('7', this))
	//{
	//	//ChangeState(MonsterState::Die);
	//	MonsterRenderer->ChangeAnimation("Skill1After");
	//	MonsterRenderer->RightFlip();
	//	Dir = ActorDir::Left;
	//}
	//if (GameEngineInput::IsDown('8', this))
	//{
	//	ChangeState(MonsterState::Skill1);
	//}
	//if (GameEngineInput::IsDown('9', this))
	//{
	//	ChangeState(MonsterState::Skill2);
	//}

	//if (GameEngineInput::IsDown('0', this))
	//{
	//	ChangeState(MonsterState::Death);
	//}

	//if (GameEngineInput::IsDown('-', this))
	//{
	//	MonsterRenderer->ChangeAnimation("Skill2After");
	//	HitEffect->ChangeAnimation("Skill2Hit");
	//}

	//DirCheck();
	//InsideLockMap();
}

void TestMonster::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TestMonster::Hit(long long _Damage, bool _Attack)
{
	if (_Attack == false)
	{
		return;
	}


}