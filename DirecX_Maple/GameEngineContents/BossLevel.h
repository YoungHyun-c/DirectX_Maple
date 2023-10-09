#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
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
	std::shared_ptr<class JinHillaAnime> JinHillaAttackAni;
	std::shared_ptr<class Player> NewPlayer;

	std::shared_ptr<class CravingMonster> CravingMob;
	std::shared_ptr<class GhostSwoo> GhostSwooMob;
	std::shared_ptr<class GhostDamien> GhostDamienMob;
	std::shared_ptr<class GhostSwoo> SwooBall;

	float CurTime = 29.44f;
	bool AniEnd = false;
};

