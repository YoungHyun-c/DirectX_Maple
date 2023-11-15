#include "PreCompile.h"
#include "Mouse.h"
#include "ChatManager.h"
#include "Player.h"
#include "FormerEffect.h"
#include "GrandisGoddess.h"

#define FontSize 24.0f

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

	Face = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	Face->SetSprite("FormerNpc1.Png");
	Face->AutoSpriteSizeOn();
	Face->Transform.SetLocalPosition({ 310.0f, -100.0f });

	NameTag = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	NameTag->SetSprite("NameTag.Png");
	NameTag->AutoSpriteSizeOn();
	NameTag->Transform.SetLocalPosition({ 290.0f, -300.0f });
	

	NextRen = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	NextRen->SetSprite("OK.Png");
	NextRen->AutoSpriteSizeOn();
	NextRen->Transform.SetLocalPosition({ 270.0f, -350.0f });

	NextCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::NPC);
	NextCol->SetCollisionType(ColType::AABBBOX2D);
	NextCol->Transform.SetLocalPosition({ CameraPos.X + 270.0f, CameraPos.Y - 350.0f});
	NextCol->Transform.SetLocalScale({ 80.0f, 20.0f });

	ChatName = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	ChatName->SetText("�����ý��丮", "�׶��� ����", 25.0f, float4::WHITE);
	ChatName->Transform.SetLocalPosition({ 210.0f, -280.0f });


	FontRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	FontRender->SetText("�����ý��丮", " ", FontSize, float4::WHITE);
	FontRender->Transform.SetLocalPosition({ -390.0f, -200.0f });

	/*FontRender->On();
	ChatBack->On();
	Face->On();
	NameTag->On();
	NextRen->On();
	ChatName->On();
	NextCol->On();*/

	GameEngineInput::AddInputObject(this);

	{
		{
			ChatState['C']; // Clear
			ChatState['F']; // Fail
		}

		{
			Chat Chatting;
			Chatting.IsControl = false;

			for (int i = 0; i < 7; i++)
			{
				Chatting.StateChat.CreateState(i, {
					.Start =
					[=](class GameEngineState* _Parent)
					{
						On();
					},
					.Stay =
					[=](float DeltaTime, class GameEngineState* _Parent)
					{
						if (GameEngineInput::IsDown(VK_SPACE,this))
						{
							if (i == 5)
							{
								Former = GetLevel()->CreateActor<FormerEffect>();
								PlayerValue::GetValue()->SetGrade(6);
							}
							_Parent->ChangeState(i + 1);
						}
						if (NextCol->CollisionEvent(ContentsCollisionType::Mouse, ClickEvent))
						{
							if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()))
							{
								if (i == 5)
								{
									Former = GetLevel()->CreateActor<FormerEffect>();
									PlayerValue::GetValue()->SetGrade(6);
								}
								_Parent->ChangeState(i + 1);
							}
						}

						if (i == 0)
						{
							FontRender->SetText("�����ý��丮", "����... �÷��� �ߵ�� �� ���� ���־�����?", FontSize, float4::WHITE);
							GrandisGoddess::MainFormerNpc->ChangeAnimation("FormerSay");
							Face->SetSprite("FormerNpc1.Png");
						}
						if (i == 1)
						{
							FontRender->SetText("�����ý��丮", "���� ���п� ���� ���� ��ã�� �� �ְ� �Ǿ����.", FontSize, float4::WHITE);
							//GrandisGoddess::MainFormerNpc->ChangeAnimation("FormerSay");
							Face->SetSprite("FormerNpc1.Png");
						}
						if (i == 2)
						{
							FontRender->SetText("�����ý��丮", "������... \n���԰� �� ��ȭ�� ������ ������..", FontSize, float4::WHITE);
							Face->SetSprite("FormerNpc1.Png");
						}

						if (i == 3)
						{
							FontRender->SetText("�����ý��丮", "���� �� ���� �����ϴ� ���簡 �־��... \n�׳ฦ ����� �ѹ�¦ �� ���ư� �� �ֱ⸦ �ٷ���.", FontSize, float4::WHITE);
							Face->SetSprite("FormerNpc3.Png");
						}
						if (i == 4)
						{
							FontRender->SetText("�����ý��丮", "�� ���� ���� ������ �޾ҵ�\n���Բ� ������ �帮�� �;��.", FontSize, float4::WHITE);
							Face->SetSprite("FormerNpc2.Png");
						}
						if (i == 5)
						{
							FontRender->SetText("�����ý��丮", "����... �״븦 ���� �غ��� ���� �޾��ֽðھ��?", FontSize, float4::WHITE);
							Face->SetSprite("FormerNpc1.Png");
							NextRen->SetSprite("Accept.Png");
						}
						if (i == 6)
						{
							FontRender->SetText("�����ý��丮", "�״뿡�� ����� �ֱ⸦.....", FontSize, float4::WHITE);
							GrandisGoddess::MainFormerNpc->ChangeAnimation("FormerStand");
							Face->SetSprite("FormerNpc1.Png");
							NextRen->SetSprite("Ok.Png");
						}

					}
					});
			}

			Chatting.StateChat.CreateState(7, {
				.Start =
				[=](class GameEngineState* _Parent)
				{
						GrandisGoddess::MainFormerNpc->ChangeAnimation("FormerStand");
						Player::GetMainPlayer()->PlayerEnterBindEnd();
						Off();
						CurChat = nullptr;
				} });

			ChatState['C'] = Chatting;
		}

		{
			{
				Chat Chatting;
				Chatting.IsControl = false;

				for (int i = 0; i < 3; i++)
				{
					Chatting.StateChat.CreateState(i, {
						.Start =
						[=](class GameEngineState* _Parent)
						{
							On();
						},
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

							if (i == 0)
							{
								FontRender->SetText("�����ý��丮", "�״�� ���� �� �÷��� ������� ���߾��...", FontSize, float4::WHITE);
								Face->SetSprite("FormerNpc0.Png");
							}
							if (i == 1)
							{
								FontRender->SetText("�����ý��丮", "�� �÷��� ���� ���������?", FontSize, float4::WHITE);
								Face->SetSprite("FormerNpc0.Png");
							}

							if (i == 2)
							{
								FontRender->SetText("�����ý��丮", "�÷��� �غ��ϰ� �ٽ� ���ֱ� �ٷ���...\n��ٸ��� ��������..", FontSize, float4::WHITE);
								Face->SetSprite("FormerNpc0.Png");
							}
						}
						});
				}

				Chatting.StateChat.CreateState(3, {
					.Start =
					[=](class GameEngineState* _Parent)
					{
							Player::GetMainPlayer()->PlayerEnterBindEnd();
							Off();
							CurChat = nullptr;
					} });

				ChatState['F'] = Chatting;
			}
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
	//ClickEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
	//	{
	//		if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()))
	//		{
	//			//Former = GetLevel()->CreateActor<FormerEffect>();
	//			//Player::GetMainPlayer()->PlayerEnterBindEnd();
	//			//SkillUseKey(VK_SPACE);
	//			//Off();
	//		}
	//	};

	//NextCol->CollisionEvent(ContentsCollisionType::Mouse, ClickEvent);

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

	for (std::pair<const char, Chat>& Pair : ChatState)
	{
		//if (true == GameEngineInput::IsDown(VK_SPACE, this))
		if (QuestClear == true && Pair.first == 'C')
		{
			Chat& Catting = Pair.second;

			CurChat = &Catting;
			Catting.StateChat.ChangeState(0);
			return true;
		}

		if (QuestClear == false && Pair.first == 'F')
		{
			Chat& Catting = Pair.second;

			CurChat = &Catting;
			Catting.StateChat.ChangeState(0);
			return true;
		}
	}

	return false;
}

void ChatManager::ChatUseKey(const char& _Value)
{
	if (_Value == 'C')
	{
		ChatState['C'];
		QuestClear = true;
		ChatUseCheck();
	}

	if (_Value == 'F')
	{
		ChatState['F'];
		QuestClear = false;
		ChatUseCheck();
	}
}