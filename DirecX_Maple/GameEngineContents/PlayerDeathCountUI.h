#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerDeathCountUI : public GameEngineActor
{
public:
	// constructer destructer
	PlayerDeathCountUI();
	~PlayerDeathCountUI();

	// delete Function
	PlayerDeathCountUI(const PlayerDeathCountUI& _Other) = delete;
	PlayerDeathCountUI(PlayerDeathCountUI&& _Other) noexcept = delete;
	PlayerDeathCountUI& operator = (const PlayerDeathCountUI& _Other) = delete;
	PlayerDeathCountUI& operator = (PlayerDeathCountUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PreveLevel) override;

private:
	std::shared_ptr<GameEngineUIRenderer> DeathUIBack = nullptr;

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* DeathUI = nullptr;
	std::shared_ptr<GameEngineUIRenderer> DeathCountUI;

	int GreenDeathUI = 0;
	int RedDeathUI = 0;

	float FailTime = 0.0f;
	float ChangeTime = 2.0f;
};

