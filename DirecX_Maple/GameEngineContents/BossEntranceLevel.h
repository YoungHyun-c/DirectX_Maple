#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class BossEntranceLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BossEntranceLevel();
	~BossEntranceLevel();

	// delete Function
	BossEntranceLevel(const BossEntranceLevel& _Other) = delete;
	BossEntranceLevel(BossEntranceLevel&& _Other) noexcept = delete;
	BossEntranceLevel& operator = (const BossEntranceLevel& _Other) = delete;
	BossEntranceLevel& operator = (BossEntranceLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class BackGroundMap> Map;

	std::shared_ptr<class Player> NewPlayer = nullptr;

};

