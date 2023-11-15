#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class ChatManager : public GameEngineActor
{
public:
	// constructer destructer
	ChatManager();
	~ChatManager();

	// delete Function
	ChatManager(const ChatManager& _Other) = delete;
	ChatManager(ChatManager&& _Other) noexcept = delete;
	ChatManager& operator = (const ChatManager& _Other) = delete;
	ChatManager& operator = (ChatManager&& _Other) noexcept = delete;

	bool ChatUseCheck();
	void ChatUseKey(const char& _Value);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void PosUpdate();

private:
	float4 CameraPos = float4::ZERO;

	std::shared_ptr<class GameEngineUIRenderer> ChatBack;
	std::shared_ptr<class GameEngineUIRenderer> FontRender;
	std::shared_ptr<class GameEngineUIRenderer> ChatName;

	std::shared_ptr<class GameEngineUIRenderer> Face;
	std::shared_ptr<class GameEngineUIRenderer> NameTag;
	std::shared_ptr<class GameEngineUIRenderer> NextRen;
	std::shared_ptr<GameEngineCollision> NextCol = nullptr;


	std::shared_ptr<class FormerEffect> Former;
	std::shared_ptr<class GrandisGoddess> FormerNpc;

	EventParameter ClickEvent;


	class Chat
	{
	public:
		bool IsControll;
		float MaxCoolTime;

		float4 SkillUsePos;

		int TargetCollisionOrder;
		GameEngineState StateTest;


		void Update(float _Delta)
		{
			StateTest.Update(_Delta);
		}
	};

	Chat* CurChat = nullptr;
	std::map<const char, Chat> ChatState;

	bool GreenAttack = false;
	bool PurpleAttack = false;
};

