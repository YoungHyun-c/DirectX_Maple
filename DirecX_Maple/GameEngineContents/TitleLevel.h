#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class TitleLevel : public GameEngineLevel
{
public:
	// constructer destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator = (const TitleLevel& _Other) = delete;
	TitleLevel& operator = (TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> TitleRenderer;
	std::shared_ptr<class BackGround> Map;
};

