#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class BossLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BossLevel();
	~BossLevel();

	// delete Function
	BossLevel(const BossLevel& _Other) = delete;
	BossLevel(BossLevel&& _Other) noexcept = delete;
	BossLevel& operator = (const BossLevel& _Other) = delete;
	BossLevel& operator = (BossLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class BackGroundMap> Map;
};

