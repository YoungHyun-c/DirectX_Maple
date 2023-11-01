#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class TestLevel : public GameEngineLevel
{
public:
	// constructer destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator = (const TestLevel& _Other) = delete;
	TestLevel& operator = (TestLevel&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;


private:
	std::shared_ptr<class BackGroundMap> Map;
	std::shared_ptr<class Player> NewPlayer;
	std::shared_ptr<class GhostDamien> GhostDamienMob;
};

