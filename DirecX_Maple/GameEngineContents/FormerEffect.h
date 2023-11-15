#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FormerEffect : public GameEngineActor
{
public:
	// constructer destructer
	FormerEffect();
	~FormerEffect();

	// delete Function
	FormerEffect(const FormerEffect& _Other) = delete;
	FormerEffect(FormerEffect&& _Other) noexcept = delete;
	FormerEffect& operator = (const FormerEffect& _Other) = delete;
	FormerEffect& operator = (FormerEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta)override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Former6thEffect;
};

