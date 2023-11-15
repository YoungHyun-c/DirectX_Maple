#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class QuestIcon : public GameEngineActor
{
public:
	static QuestIcon* MainQuest;
public:
	// constructer destructer
	QuestIcon();
	~QuestIcon();

	// delete Function
	QuestIcon(const QuestIcon& _Other) = delete;
	QuestIcon(QuestIcon&& _Other) noexcept = delete;
	QuestIcon& operator = (const QuestIcon& _Other) = delete;
	QuestIcon& operator = (QuestIcon&& _Other) noexcept = delete;


	void ChangeAnimation(std::string_view _AnimationName);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PreveLevel) override;

	void PosUpdate();

private:
	std::shared_ptr<class GameEngineSpriteRenderer> QuestNpc = nullptr;
	std::shared_ptr<GameEngineCollision> QuestCol = nullptr;

	std::shared_ptr<class ChatManager> FormerChat;
};

