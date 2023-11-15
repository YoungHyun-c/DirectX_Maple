#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GrandisGoddess : public GameEngineActor
{
public:
	static GrandisGoddess* MainFormerNpc;
public:
	// constructer destructer
	GrandisGoddess();
	~GrandisGoddess();

	// delete Function
	GrandisGoddess(const GrandisGoddess& _Other) = delete;
	GrandisGoddess(GrandisGoddess&& _Other) noexcept = delete;
	GrandisGoddess& operator = (const GrandisGoddess& _Other) = delete;
	GrandisGoddess& operator = (GrandisGoddess&& _Other) noexcept = delete;

	void ChangeAnimation(std::string_view _AnimationName);

	void NpcCollisionOn()
	{
		NpcCol->On();
	}

	void NpcCollisionOff()
	{
		NpcCol->Off();
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PreveLevel) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FormerNpc = nullptr;
	std::shared_ptr<GameEngineCollision> NpcCol = nullptr;


	std::shared_ptr<class ChatManager> FormerChat;
	bool QuestStart = false;
};

