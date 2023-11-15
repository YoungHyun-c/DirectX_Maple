#include "PreCompile.h"
#include "GrandisGoddess.h"
#include "Mouse.h"
#include "ChatManager.h"


GrandisGoddess* GrandisGoddess::MainFormerNpc = nullptr;

GrandisGoddess::GrandisGoddess()
{

}

GrandisGoddess::~GrandisGoddess()
{

}

void GrandisGoddess::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainFormerNpc = this;
}

void GrandisGoddess::Start()
{
	FormerNpc = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::NPC);
	FormerNpc->CreateAnimation("Special1", "Special1", 0.1f);
	FormerNpc->CreateAnimation("Special2", "Special2", 0.1f, -1, -1, false);
	FormerNpc->CreateAnimation("FormerStand", "FormerStand", 0.1f);
	FormerNpc->CreateAnimation("FormerEye", "FormerEye", 0.1f);
	FormerNpc->CreateAnimation("FormerSay", "FormerSay", 0.1f);
	//FormerNpc->Transform.SetWorldPosition({ 1275.0f, -535.0f });
	FormerNpc->ChangeAnimation("Special1");
	FormerNpc->AutoSpriteSizeOn();
	FormerNpc->On();

	NpcCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::NPC);
	NpcCol->SetCollisionType(ColType::AABBBOX2D);
	//NpcCol->Transform.SetWorldPosition({ 1275.0f, -535.0f });
	NpcCol->Transform.SetLocalPosition({ -10.0f, 10.0f });
	NpcCol->Transform.SetLocalScale({ 50.0f, 80.0f });

	GameEngineInput::AddInputObject(this);
}

void GrandisGoddess::Update(float _Delta)
{
	//if (GameEngineInput::IsDown('9', this))
	//{
	//	FormerNpc->ChangeAnimation("Special2");
	//}
	//if (GameEngineInput::IsDown('0', this))
	//{
	//	FormerNpc->ChangeAnimation("FormerStand");
	//}
	//if (GameEngineInput::IsDown('-', this))
	//{
	//	FormerNpc->ChangeAnimation("FormerEye");
	//}
	//if (GameEngineInput::IsDown('=', this))
	//{
	//	FormerNpc->ChangeAnimation("FormerSay");
	//}

	EventParameter ClickEvent;
	ClickEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			if (GlobalValue::GetNeedGlobalValue()->GetDropItemValue() >= 100 && PlayerValue::GetValue()->GetLevel() >= 260)
			{
				if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()))
				{
					FormerChat = GetLevel()->CreateActor<ChatManager>();
					FormerChat->ChatUseKey('C');
					Player::GetMainPlayer()->PlayerBind();
					FormerNpc->ChangeAnimation("Special2");
					NpcCol->Off();
				}
				
			}
			else if (GlobalValue::GetNeedGlobalValue()->GetClearQuestValue() == false)
			{
				if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()) && QuestStart == true)
				{
					FormerChat = GetLevel()->CreateActor<ChatManager>();
					FormerChat->ChatUseKey('F');
					Player::GetMainPlayer()->PlayerBind();
					NpcCol->Off();
				}
			}
			//if (GlobalValue::GetNeedGlobalValue()->GetCurQuestValue() == true)
			if (false == GlobalValue::GetNeedGlobalValue()->GetClearQuestValue())
			{
				if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()) && QuestStart == false)
				{
					FormerChat = GetLevel()->CreateActor<ChatManager>();
					FormerChat->ChatUseKey('I');
					Player::GetMainPlayer()->PlayerBind();
					QuestStart = true;
					NpcCol->Off();
				}
			}
		};

	NpcCol->CollisionEvent(ContentsCollisionType::Mouse, ClickEvent);
}

void GrandisGoddess::ChangeAnimation(std::string_view _AnimationName)
{
	FormerNpc->ChangeAnimation(_AnimationName);
}