#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class PracticeLevel : public GameEngineLevel
{
public:
	// constructer destructer
	PracticeLevel();
	~PracticeLevel();

	// delete Function
	PracticeLevel(const PracticeLevel& _Other) = delete;
	PracticeLevel(PracticeLevel&& _Other) noexcept = delete;
	PracticeLevel& operator = (const PracticeLevel& _Other) = delete;
	PracticeLevel& operator = (PracticeLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class BackGroundMap> Map;
	std::shared_ptr<class Player> PlayerObject;
	std::shared_ptr<class TileMap> TileMapObject;
};

