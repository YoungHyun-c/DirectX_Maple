#include "PreCompile.h"
#include "QuestIcon.h"
#include "Mouse.h"
#include "ChatManager.h"

QuestIcon::QuestIcon()
{

}

QuestIcon::~QuestIcon()
{

}

QuestIcon* QuestIcon::MainQuest = nullptr;

void QuestIcon::LevelStart(GameEngineLevel* _PreveLevel)
{
	MainQuest = this;
}

void QuestIcon::Start()
{
	QuestNpc = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::NPC);
	QuestNpc->CreateAnimation("QuestAlarmIcon", "QuestAlarmIcon", 0.2f);
	QuestNpc->CreateAnimation("QuestClearIcon", "QuestClearIcon", 0.2f);
	QuestNpc->AutoSpriteSizeOn();
	QuestNpc->ChangeAnimation("QuestAlarmIcon");
	QuestNpc->On();


	QuestCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::NPC);
	QuestCol->Transform.SetLocalScale({ 50.0f, 50.0f });

}

void QuestIcon::Update(float _Delta)
{
	PosUpdate();

	if (false == GlobalValue::GetNeedGlobalValue()->GetCurQuestValue())
	{
		On();
	}
	else
	{
		Off();
	}

	EventParameter ClickEvent;
	ClickEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			{
				if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()))
				{
					FormerChat = GetLevel()->CreateActor<ChatManager>();
					FormerChat->ChatUseKey('S');
					Player::GetMainPlayer()->PlayerBind();
					Off();
				}
			}
		};
	QuestCol->CollisionEvent(ContentsCollisionType::Mouse, ClickEvent);
}


void QuestIcon::PosUpdate()
{
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	QuestNpc->Transform.SetLocalPosition({ PlayerPos.X + 10.0f , PlayerPos.Y + 55.0f });
	QuestCol->Transform.SetLocalPosition({ PlayerPos.X + 10.0f , PlayerPos.Y + 55.0f});
}