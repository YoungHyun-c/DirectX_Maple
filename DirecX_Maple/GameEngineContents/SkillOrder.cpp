#include "PreCompile.h"
#include "SkillOrder.h"

#include "SkillOrderSummonActor.h"
#include "SkillOrderActor.h"

#include "Player.h"

SkillOrder::SkillOrder()
{

}

SkillOrder::~SkillOrder()
{

}

void SkillOrder::Start()
{
	SkillFunction::Start();
	{
		SkillRender2->CreateAnimation("OrederEffect", "Order_Back", 0.03f);

		SkillRender2->SetFrameEvent("OrederEffect", 1, std::bind(&SkillOrder::RenderEvent, this, std::placeholders::_1));
		SkillRender2->Transform.SetLocalPosition({ 0.0f, 75.0f });
		SkillRender2->SetEndEvent("OrederEffect", [&](GameEngineRenderer* _Renderer)
			{
				EndSkill();
			});

		AllOrderActor.reserve(2);
		for (int i = 0; i < 2; i++)
		{
			SkillRender2->SetFrameEvent("OrederEffect", i, [&](GameEngineSpriteRenderer* _Renderer)
				{
					CreateOrder();
				});
		}

		SkillRender2->SetFrameEvent("OrederEffect", 4, [&](GameEngineSpriteRenderer* _Renderer)
			{
				OrderPosCal();
			});

		SkillRender2->LeftFlip();
	}

	{
		SkillRender3->CreateAnimation("OrederEffect", "Order_Back", 0.03f);

		SkillRender3->SetFrameEvent("OrederEffect", 1, std::bind(&SkillOrder::RenderEvent, this, std::placeholders::_1));
		SkillRender3->Transform.SetLocalPosition({ 0.0f, 75.0f });
		SkillRender3->SetEndEvent("OrederEffect", [&](GameEngineRenderer* _Renderer)
			{
				EndSkill();
			});

		SkillRender3->LeftFlip();
	}
}

void SkillOrder::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;
	On();


	SkillRender2->ChangeAnimation("OrederEffect", true, 0);
	SkillRender2->On();


	SkillRender3->ChangeAnimation("OrederEffect", true, 0);
	SkillRender3->On();


	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	PlayerValue::GetValue()->SubAtere(100);
}

void SkillOrder::EndSkill()
{
	SkillFunction::EndSkill();
	Off();
}

void SkillOrder::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void SkillOrder::Update(float _Delta)
{
	//CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	SkillRender2->Transform.SetWorldPosition({ CurPlayerPos.X - 50.0f, CurPlayerPos.Y - 80.0f});
	SkillRender2->Transform.SetLocalRotation({ 0.0f, 0.0f, 240.0f });
	SkillRender3->Transform.SetWorldPosition({ CurPlayerPos.X + 50.0f, CurPlayerPos.Y - 80.0f });
	SkillRender3->Transform.SetLocalRotation({ 0.0f, 0.0f, 300.0f });
	//Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
}

void SkillOrder::OrderPosCal()
{
	for (size_t i = OrderCount; i < AllOrderActor.size(); i++)
	{
		AllOrderActor[i]->Transform.SetWorldPosition({ CurPlayerPos.X - 50 + ((i%2) * 100.0f),
			CurPlayerPos.Y - 30.0f });
		AllOrderActor[i]->Transform.SetLocalRotation({ 0.0f, 0.0f,  -(30.0f) + ((i%2) * 60.0f) });
		AllOrderActor[i]->On();
		OrderCount++;

		// 총 6개만 리스토어 이후엔 8개
		OrderCalCount++;
		if (OrderLimitCount < OrderCalCount)
		{
			for (int j = OrderOffCount; j < OrderCal; j++)
			{
				AllOrderActor[j]->Off();
				OrderCalCount--;
			}
			OrderCal += 2;
			OrderOffCount += 2;
		}

	}
}

void SkillOrder::CreateOrder()
{
	std::shared_ptr<SkillOrderActor> _OrderActor = GetLevel()->CreateActor<SkillOrderActor>(ContentsObjectType::FrontSkill);
	CurOrderPos = _OrderActor->GetOrderPos();
	AllOrderActor.push_back(_OrderActor);
}

void SkillOrder::Release()
{
	SkillFunction::Release();
}

void SkillOrder::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;
}