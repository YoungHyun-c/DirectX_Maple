#pragma once
#include "MonsterFunction.h"

// Ό³Έν :
class BossBoxReward : public MonsterFunction
{
public:
	// constructer destructer
	BossBoxReward();
	~BossBoxReward();

	// delete Function
	BossBoxReward(const BossBoxReward& _Other) = delete;
	BossBoxReward(BossBoxReward&& _Other) noexcept = delete;
	BossBoxReward& operator = (const BossBoxReward& _Other) = delete;
	BossBoxReward& operator = (BossBoxReward&& _Other) noexcept = delete;

	void Hit(long long _Damage, bool _Attack) override;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> BossBoxMob;
	std::shared_ptr<class GameEngineCollision> BossBoxCol;

	long long BoxHp = 0;
	void SetDropItemList();

	std::vector<std::pair<std::string, int>> DropItemList;
	bool BoxOpen = false;
	bool BoxReward = false;
};

