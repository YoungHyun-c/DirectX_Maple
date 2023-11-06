#include "PreCompile.h"
#include "BossBoxReward.h"

#include "DropItem.h"

BossBoxReward::BossBoxReward()
{

}

BossBoxReward::~BossBoxReward()
{

}

void BossBoxReward::Start()
{
	GameEngineInput::AddInputObject(this);
}

void BossBoxReward::Update(float _Delta)
{
	if (BoxOpen == true && BoxReward == false)
	{
		size_t Size = DropItemList.size();
		for (size_t i = 0; i < Size; i++)
		{
			std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
			NewItem->Transform.SetLocalScale({ 2, 2 });
			NewItem->SetQuadraticFunction(-500.0f + (i * 100) + 5.0f, Transform.GetWorldPosition() + float4{ 0.0f, 200.0f });
			NewItem->SetDropItemInfo(DropItemList[i].first, static_cast<int>(ItemType::Etc));
		}
		BoxOpen = false;
		BoxReward = true;
		return;
	}

	if (BoxHp <= 0 && false == BossBoxMob->IsDeath())
	{
		if (true == BossBoxMob->IsCurAnimationEnd())
		{
			BossBoxMob->Death();
		}
	}

}

void BossBoxReward::Hit(long long _Damage, bool _Attack)
{
	BoxHp -= _Damage;

	if (BoxHp <= 0)
	{
		BossBoxMob->ChangeAnimation("BossBoxDie");
		BossBoxCol->Death();

		BoxOpen = true;
	}

}

void BossBoxReward::SetDropItemList()
{
	DropItemList.reserve(11);

	DropItemList.push_back({ "GoTong", 75 });
	DropItemList.push_back({ "GoTong", 75 });
	DropItemList.push_back({ "GoTong", 75 });
	DropItemList.push_back({ "GoTong", 75 });
	DropItemList.push_back({ "GoTong", 75 });
	DropItemList.push_back({ "Jenesis", 75 });
	DropItemList.push_back({ "DayBreak", 75 });
	DropItemList.push_back({ "DayBreak", 75 });
	DropItemList.push_back({ "DayBreak", 75 });
	DropItemList.push_back({ "DayBreak", 75 });
	DropItemList.push_back({ "DayBreak", 75 });
}

void BossBoxReward::LevelStart(GameEngineLevel* _PrevLevel)
{
	BossBoxMob = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Monster);
	BossBoxMob->SetSprite("BossBoxStand.Png");
	BossBoxMob->CreateAnimation("BossBoxDie", "BossBoxDie", 0.15f, -1, -1, false);
	BossBoxMob->AutoSpriteSizeOn();
	BossBoxMob->SetPivotType(PivotType::Bottom);
	BossBoxMob->On();


	BoxHp = 10000;
	BossBoxCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
	BossBoxCol->Transform.SetLocalScale({ 100.0f, 80.0f });
	BossBoxCol->Transform.SetLocalPosition({ 0.0f, 120.0f });
	BossBoxCol->SetCollisionType(ColType::AABBBOX2D);
	BossBoxCol->On();

	SetDropItemList();
}

void BossBoxReward::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (BossBoxMob != nullptr)
	{
		BossBoxMob->Death();
		BossBoxMob = nullptr;
	}
}