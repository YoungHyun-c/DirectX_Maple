#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HandAttack : public GameEngineActor
{
public:
	// constructer destructer
	HandAttack();
	~HandAttack();

	// delete Function
	HandAttack(const HandAttack& _Other) = delete;
	HandAttack(HandAttack&& _Other) noexcept = delete;
	HandAttack& operator = (const HandAttack& _Other) = delete;
	HandAttack& operator = (HandAttack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PreveLevel);
	void LevelEnd(GameEngineLevel* _NextLevel);

	void StringColEvent();

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Hand;
	std::shared_ptr<class GameEngineSpriteRenderer> HandEffect;
	
	std::shared_ptr<class GameEngineSpriteRenderer> StringAttack1;
	std::shared_ptr<class GameEngineSpriteRenderer> StringAttack2;
	std::shared_ptr<class GameEngineSpriteRenderer> StringAttack3;
	std::shared_ptr<class GameEngineSpriteRenderer> StringAttack4;
	std::shared_ptr<class GameEngineSpriteRenderer> StringAttack5;

	std::shared_ptr<class GameEngineCollision> StringCol1;
	std::shared_ptr<class GameEngineCollision> StringCol2;
	std::shared_ptr<class GameEngineCollision> StringCol3;
	std::shared_ptr<class GameEngineCollision> StringCol4;
	std::shared_ptr<class GameEngineCollision> StringCol5;


	EventParameter StringEvent;
	bool String = false;

	float HandAttackTime = 0.0f;
	float HandCoolTime = 7.0f;

	GameEngineRandom RanCoolTime;
};

