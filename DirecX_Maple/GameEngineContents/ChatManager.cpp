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
	Face->SetSprite("FormerNpc0.Png");
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
			ChatState['S']; // Start
			ChatState['I']; // Ing
			ChatState['C']; // Clear
			ChatState['F']; // Fail
		}

		{
			{
				Chat Chatting;
				Chatting.IsControl = false;

				for (int i = 0; i < 2; i++)
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
								FontRender->ChangeText("���� �� ��Ҹ��� �鸮�ó���...?");
								Face->SetSprite("FormerNpc0.Png");
							}
							if (i == 1)
							{
								FontRender->ChangeText("���� �� �����ּ����� �ؿ�.\n�����ִ� ������ ���ֽðھ��...?");
								Face->SetSprite("FormerNpc0.Png");
								NextRen->SetSprite("Accept.Png");
							}
						}
						});
				}

				Chatting.StateChat.CreateState(2, {
					.Start =
					[=](class GameEngineState* _Parent)
					{
							Player::GetMainPlayer()->PlayerEnterBindEnd();
							QuestStart = false;
							CurChat = nullptr;
							Off();
							GameEngineCore::ChangeLevel("4.FormerLevel");
					} });

				ChatState['S'] = Chatting;
			}
		}

		{
			{
				Chat Chatting;
				Chatting.IsControl = false;

				for (int i = 0; i < 4; i++)
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
								FontRender->ChangeText("���ôٽ��� �ƹ��͵� �� �� ����...\n������ ������ �ʿ��߾��.");
								Face->SetSprite("FormerNpc0.Png");
								NextRen->SetSprite("Ok.Png");
							}
							if (i == 1)
							{
								FontRender->ChangeText("���� �ִ� �������� ���̽ó���?");
								Face->SetSprite("FormerNpc0.Png");
								GlobalValue::GetNeedGlobalValue()->SetCurQuestValue(true);
							}

							if (i == 2)
							{
								FontRender->ChangeText("����� ���� �������� ���,\n260���� �޼��Ͽ� ������ �ٽ� ã�ƿ��ּ���.");
								Face->SetSprite("FormerNpc0.Png");
							}
							if (i == 3)
							{
								FontRender->ChangeText("�÷ÿ��� �ε� �����ϱ⸦....");
								Face->SetSprite("FormerNpc0.Png");
							}
						}
						});
				}

				Chatting.StateChat.CreateState(4, {
					.Start =
					[=](class GameEngineState* _Parent)
					{
							Player::GetMainPlayer()->PlayerEnterBindEnd();
							GrandisGoddess::MainFormerNpc->NpcCollisionOn();
							QuestIng = false;
							Off();
							CurChat = nullptr;
					} });

				ChatState['I'] = Chatting;
			}
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
								GlobalValue::GetNeedGlobalValue()->SetClearQuestValue(true);
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
									GlobalValue::GetNeedGlobalValue()->SetClearQuestValue(true);
								}
								_Parent->ChangeState(i + 1);
							}
						}

						if (i == 0)
						{
							FontRender->ChangeText("����... �÷��� �ߵ�� �� ���� ���־�����?");
							Face->SetSprite("FormerNpc1.Png");
						}
						if (i == 1)
						{
							FontRender->ChangeText("���� ���п� ���� ���� ��ã�� �� �ְ� �Ǿ����.");
							GrandisGoddess::MainFormerNpc->ChangeAnimation("FormerSay");
							Face->SetSprite("FormerNpc1.Png");
						}
						if (i == 2)
						{
							FontRender->ChangeText("������... \n���԰� �� ��ȭ�� ������ ������..");
							Face->SetSprite("FormerNpc1.Png");
						}

						if (i == 3)
						{
							FontRender->ChangeText("���� �� ���� �����ϴ� ���簡 �־��... \n�׳ฦ ����� �ѹ�¦ �� ���ư� �� �ֱ⸦ �ٷ���.");
							Face->SetSprite("FormerNpc3.Png");
						}
						if (i == 4)
						{
							FontRender->ChangeText("�� ���� ���� ������ �޾ҵ�\n���Բ� ������ �帮�� �;��.");
							Face->SetSprite("FormerNpc2.Png");
						}
						if (i == 5)
						{
							FontRender->ChangeText("����... �״븦 ���� �غ��� ���� �޾��ֽðھ��?");
							Face->SetSprite("FormerNpc1.Png");
							NextRen->SetSprite("Accept.Png");
						}
						if (i == 6)
						{
							FontRender->ChangeText("�״뿡�� ����� �ֱ⸦.....");
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
								FontRender->ChangeText("�״�� ���� �� �÷��� ������� ���߾��...");
								Face->SetSprite("FormerNpc0.Png");
							}
							if (i == 1)
							{
								FontRender->ChangeText("�� �÷��� ���� ���������?");
								Face->SetSprite("FormerNpc0.Png");
							}

							if (i == 2)
							{
								FontRender->ChangeText("�÷��� �غ��ϰ� �ٽ� ���ֱ� �ٷ���...\n��ٸ��� ��������..");
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
							GrandisGoddess::MainFormerNpc->NpcCollisionOn();
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
		if (QuestStart == true && Pair.first == 'S')
		{
			Chat& Catting = Pair.second;

			CurChat = &Catting;
			Catting.StateChat.ChangeState(0);
			return true;
		}

		if (QuestIng == true && Pair.first == 'I')
		{
			Chat& Catting = Pair.second;

			CurChat = &Catting;
			Catting.StateChat.ChangeState(0);
			return true;
		}

		if (QuestStart == false && QuestIng == false && QuestClear == true && Pair.first == 'C')
		{
			Chat& Catting = Pair.second;

			CurChat = &Catting;
			Catting.StateChat.ChangeState(0);
			return true;
		}

		if (QuestStart == false && QuestIng == false && QuestClear == false && Pair.first == 'F')
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
	if (_Value == 'S')
	{
		ChatState['S'];
		QuestStart = true;
		//GlobalValue::GetNeedGlobalValue()->SetCurQuestValue(true);
		ChatUseCheck();
	}

	if (_Value == 'I')
	{
		ChatState['I'];
		QuestIng = true;
		ChatUseCheck();
	}

	if (_Value == 'C')
	{
		ChatState['C'];
		QuestClear = true;
		GlobalValue::GetNeedGlobalValue()->SetClearQuestValue(true);
		ChatUseCheck();
	}

	if (_Value == 'F')
	{
		ChatState['F'];
		QuestClear = false;
		ChatUseCheck();
	}
}