#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class BossEnterAniLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BossEnterAniLevel();
	~BossEnterAniLevel();

	// delete Function
	BossEnterAniLevel(const BossEnterAniLevel& _Other) = delete;
	BossEnterAniLevel(BossEnterAniLevel&& _Other) noexcept = delete;
	BossEnterAniLevel& operator = (const BossEnterAniLevel& _Other) = delete;
	BossEnterAniLevel& operator = (BossEnterAniLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class JinHillaEnterAnime> EnterAni = nullptr;

};

