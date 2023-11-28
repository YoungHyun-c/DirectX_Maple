#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BossChat : public GameEngineActor
{
public:
	// constructer destructer
	BossChat();
	~BossChat();

	// delete Function
	BossChat(const BossChat& _Other) = delete;
	BossChat(BossChat&& _Other) noexcept = delete;
	BossChat& operator = (const BossChat& _Other) = delete;
	BossChat& operator = (BossChat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PreveLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:

	std::shared_ptr<GameEngineUIRenderer> BossChatUI = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> Face;
	std::shared_ptr<class GameEngineUIRenderer> FontRender;

	int FontAlpha = 1;

	double CurHp = 0;
	bool EnterBossLevel = false;
	bool ChatSetting = false;
};

