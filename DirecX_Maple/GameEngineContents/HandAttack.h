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
	
	std::shared_ptr<class GameEngineSpriteRenderer> StringAttack;
	std::shared_ptr<class GameEngineCollision> StringCol;


	EventParameter StringEvent;
	bool String = false;
};

