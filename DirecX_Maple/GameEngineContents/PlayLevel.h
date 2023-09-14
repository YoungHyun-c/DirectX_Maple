#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class PlayLevel : public GameEngineLevel
{
public:
	// constructer destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator = (const PlayLevel& _Other) = delete;
	PlayLevel& operator = (PlayLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class PlayMap> Map;
	std::shared_ptr<class TileMap> TileMapObject;
};

