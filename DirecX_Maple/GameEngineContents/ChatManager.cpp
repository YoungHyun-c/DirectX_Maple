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
	ChatName->SetText("메이플스토리", "그란디스 여신", 25.0f, float4::WHITE);
	ChatName->Transform.SetLocalPosition({ 210.0f, -280.0f });


	FontRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	FontRender->SetText("메이플스토리", " ", FontSize, float4::WHITE);
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
								FontRender->ChangeText("용사님 제 목소리가 들리시나요...?");
								Face->SetSprite("FormerNpc0.Png");
							}
							if (i == 1)
							{
								FontRender->ChangeText("저를 좀 도와주셨으면 해요.\n제가있는 곳으로 와주시겠어요...?");
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
								FontRender->ChangeText("보시다시피 아무것도 할 수 없어...\n용사님의 도움이 필요했어요.");
								Face->SetSprite("FormerNpc0.Png");
								NextRen->SetSprite("Ok.Png");
							}
							if (i == 1)
							{
								FontRender->ChangeText("옆에 있는 게이지가 보이시나요?");
								Face->SetSprite("FormerNpc0.Png");
								GlobalValue::GetNeedGlobalValue()->SetCurQuestValue(true);
							}

							if (i == 2)
							{
								FontRender->ChangeText("사냥을 통해 게이지를 얻고,\n260렙을 달성하여 저에게 다시 찾아와주세요.");
								Face->SetSprite("FormerNpc0.Png");
							}
							if (i == 3)
							{
								FontRender->ChangeText("시련에도 부디 무사하기를....");
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
							FontRender->ChangeText("용사님... 시련을 견디고 이 곳에 와주었군요?");
							Face->SetSprite("FormerNpc1.Png");
						}
						if (i == 1)
						{
							FontRender->ChangeText("용사님 덕분에 저도 힘을 되찾을 수 있게 되었어요.");
							GrandisGoddess::MainFormerNpc->ChangeAnimation("FormerSay");
							Face->SetSprite("FormerNpc1.Png");
						}
						if (i == 2)
						{
							FontRender->ChangeText("고마워요... \n용사님과 더 대화를 나누고 싶지만..");
							Face->SetSprite("FormerNpc1.Png");
						}

						if (i == 3)
						{
							FontRender->ChangeText("아직 이 곳을 위협하는 존재가 있어요... \n그녀를 무찌르고 한발짝 더 나아갈 수 있기를 바래요.");
							Face->SetSprite("FormerNpc3.Png");
						}
						if (i == 4)
						{
							FontRender->ChangeText("그 전에 저도 도움을 받았듯\n용사님께 도움을 드리고 싶어요.");
							Face->SetSprite("FormerNpc2.Png");
						}
						if (i == 5)
						{
							FontRender->ChangeText("용사님... 그대를 위해 준비한 힘을 받아주시겠어요?");
							Face->SetSprite("FormerNpc1.Png");
							NextRen->SetSprite("Accept.Png");
						}
						if (i == 6)
						{
							FontRender->ChangeText("그대에게 행운이 있기를.....");
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
								FontRender->ChangeText("그대는 아직 제 시련을 통과하지 못했어요...");
								Face->SetSprite("FormerNpc0.Png");
							}
							if (i == 1)
							{
								FontRender->ChangeText("제 시련이 많이 어려웠나요?");
								Face->SetSprite("FormerNpc0.Png");
							}

							if (i == 2)
							{
								FontRender->ChangeText("시련을 극복하고 다시 와주길 바래요...\n기다리고 있을께요..");
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