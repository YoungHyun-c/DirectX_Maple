#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class InvinCibilityEffect : public GameEngineActor
{
public:
	// constructer destructer
	InvinCibilityEffect();
	~InvinCibilityEffect();

	// delete Function
	InvinCibilityEffect(const InvinCibilityEffect& _Other) = delete;
	InvinCibilityEffect(InvinCibilityEffect&& _Other) noexcept = delete;
	InvinCibilityEffect& operator = (const InvinCibilityEffect& _Other) = delete;
	InvinCibilityEffect& operator = (InvinCibilityEffect&& _Other) noexcept = delete;

	void GetStartInvincible()
	{
		InvinCibility->ChangeAnimation("IonStart");
		InvinCibility->On();
	}

	void GetEndInvincible()
	{
		InvinCibility->ChangeAnimation("IonEnd");
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> InvinCibility = nullptr;

};

