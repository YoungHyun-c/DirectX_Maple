#include "PreCompile.h"
#include "Mouse.h"
#include "ChatManager.h"
#include "Player.h"
#include "FormerEffect.h"
#include "GrandisGoddess.h"

ChatManager::ChatManager()
{

}

ChatManager::~ChatManager()
{

}

void ChatManager::Start()
{
	CameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();

	ChatBack = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	ChatBack->SetSprite("ChatBackBig.Png");
	ChatBack->AutoSpriteSizeOn();
	ChatBack->Transform.SetLocalPosition({ 0.0f, -280.0f });
	ChatBack->Off();

	Face = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	Face->SetSprite("FormerNpc1.Png");
	Face->AutoSpriteSizeOn();
	Face->Transform.SetLocalPosition({ 270.0f, -100.0f });

	NameTag = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	NameTag->SetSprite("NameTag.Png");
	NameTag->AutoSpriteSizeOn();
	NameTag->Transform.SetLocalPosition({ 270.0f, -300.0f });
	

	NextRen = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	NextRen->SetSprite("OK.Png");
	NextRen->AutoSpriteSizeOn();
	NextRen->Transform.SetLocalPosition({ 270.0f, -350.0f });
	NextRen->Off();

	NextCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::NPC);
	NextCol->SetCollisionType(ColType::AABBBOX2D);
	NextCol->Transform.SetLocalPosition({ CameraPos.X + 270.0f, CameraPos.Y - 350.0f});
	NextCol->Transform.SetLocalScale({ 80.0f, 20.0f });


	ChatName = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	ChatName->SetText("�����ý��丮", "�׶��� ����", 25.0f, float4::WHITE);
	ChatName->Transform.SetLocalPosition({ 190.0f, -280.0f });
	ChatName->On();

	FontRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	FontRender->SetText("�����ý��丮", " ���谡��... �״뿡�� ���� �ְ�;���� \n ���� �޾��ֽðھ�� ? ", 25.0f, float4::WHITE);
	FontRender->Transform.SetLocalPosition({ -350.0f, -230.0f });
	FontRender->On();
	ChatBack->On();
	NextRen->On();
	NextCol->On();

	GameEngineInput::AddInputObject(this);

	{
		{
			ChatState[VK_SPACE];
		}

		{
			Chat Chatting;
			Chatting.IsControll = false;

			for (int i = 0; i < 6; i++)
			{
				Chatting.StateTest.CreateState(i, {
					.Stay =
					[=](float DeltaTime, class GameEngineState* _Parent)
					{
						if (GameEngineInput::IsDown(VK_SPACE,this))
						{
								_Parent->ChangeState(i + 1);
						}
						if (NextCol->CollisionEvent(ContentsCollisionType::Mouse, ClickEvent))
						{
							if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()))
							{
								_Parent->ChangeState(i + 1);
							}
						}

						if (i == 1)
						{
							FontRender->SetText("�����ý��丮", " ���谡��... ? ", 25.0f, float4::WHITE);
							GrandisGoddess::MainFormerNpc->ChangeAnimation("FormerSay");

						}
						if (i == 2)
						{
							FontRender->SetText("�����ý��丮", " ���ϼ��� ", 25.0f, float4::WHITE);
							GrandisGoddess::MainFormerNpc->ChangeAnimation("FormerEye");
						}

						if (i == 3)
						{
							FontRender->SetText("�����ý��丮", " ������ڳ���... ? ", 25.0f, float4::WHITE);
							Face->SetSprite("FormerNpc0.Png");
						}
						if (i == 4)
						{
							FontRender->SetText("�����ý��丮", " �׸�... ? ", 25.0f, float4::WHITE);
							Face->SetSprite("FormerNpc2.Png");
						}
						if (i == 5)
						{
							FontRender->SetText("�����ý��丮", " ��... ? ", 25.0f, float4::WHITE);
							Face->SetSprite("FormerNpc3.Png");
						}

					}
					});
			}

			// 20���� ��� ����
			Chatting.StateTest.CreateState(6, {
				.Start =
				[=](class GameEngineState* _Parent)
				{
						Former = GetLevel()->CreateActor<FormerEffect>();
						Player::GetMainPlayer()->PlayerEnterBindEnd();
						PlayerValue::GetValue()->SetGrade(6);
						Off();
						CurChat = nullptr;
				} });

			ChatState[VK_SPACE] = Chatting;
		}
	}
}

void ChatManager::Update(float _Delta)
{
	PosUpdate();

	if (nullptr != CurChat)
	{
		CurChat->Update(_Delta);
	}

	//EventParameter ClickEvent;
	ClickEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()))
			{
				//Former = GetLevel()->CreateActor<FormerEffect>();
				//Player::GetMainPlayer()->PlayerEnterBindEnd();
				//SkillUseKey(VK_SPACE);
				//Off();
			}
		};

	NextCol->CollisionEvent(ContentsCollisionType::Mouse, ClickEvent);

}

void ChatManager::PosUpdate()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();

	NextCol->Transform.SetLocalPosition({ CameraPos.X + 270.0f, CameraPos.Y - 350.0f });
}

bool ChatManager::ChatUseCheck()
{
	if (nullptr != CurChat)
	{
		return false;
	}

	for (std::pair<const char, Chat>& pair : ChatState)
	{
		//if (true == GameEngineInput::IsDown(VK_SPACE, this))
		{
			Chat& UseSkill = pair.second;

			CurChat = &UseSkill;
			UseSkill.StateTest.ChangeState(0);
			return true;
		}
	}

	return false;
}

void ChatManager::ChatUseKey(const char& _Value)
{
	if (_Value == VK_SPACE)
	{
		ChatState[VK_SPACE];
		ChatUseCheck();
	}


}