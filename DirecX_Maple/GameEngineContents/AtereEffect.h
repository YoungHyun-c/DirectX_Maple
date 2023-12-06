#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

// Ό³Έν :
class AtereEffect : public Effect
{
public:
	// constrcuter destructer
	AtereEffect();
	~AtereEffect();

	// delete Function
	AtereEffect(const AtereEffect& _Other) = delete;
	AtereEffect(AtereEffect&& _Other) noexcept = delete;
	AtereEffect& operator=(const AtereEffect& _Other) = delete;
	AtereEffect& operator=(AtereEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;
};

