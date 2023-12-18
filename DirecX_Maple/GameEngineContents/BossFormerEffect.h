#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BossFormerEffect : public GameEngineActor
{
public:
	// constructer destructer
	BossFormerEffect();
	~BossFormerEffect();

	// delete Function
	BossFormerEffect(const BossFormerEffect& _Other) = delete;
	BossFormerEffect(BossFormerEffect&& _Other) noexcept = delete;
	BossFormerEffect& operator = (const BossFormerEffect& _Other) = delete;
	BossFormerEffect& operator = (BossFormerEffect&& _Other) noexcept = delete;

	void GetStartFormerBindEffect()
	{
		FormBindEffect->On();
		FormBindEffect->ChangeAnimation("FormerBindStart");
	}

	void GetEndFormerBindEffect()
	{
		FormBindEffect->ChangeAnimation("FormerBindEnd");
	}


protected:
	void Start() override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> FormBindEffect;

	float FormerBinding = 0.0f;
	float FormerBindTime = 10.0f;
};

