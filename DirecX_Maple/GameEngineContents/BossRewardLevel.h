#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class BossRewardLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BossRewardLevel();
	~BossRewardLevel();

	// delete Function
	BossRewardLevel(const BossRewardLevel& _Other) = delete;
	BossRewardLevel(BossRewardLevel&& _Other) noexcept = delete;
	BossRewardLevel& operator = (const BossRewardLevel& _Other) = delete;
	BossRewardLevel& operator = (BossRewardLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class BackGroundMap> Map;

};

