#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class AltarUi : public GameEngineActor
{
public:
	// constructer destructer
	AltarUi();
	~AltarUi();

	// delete Function
	AltarUi(const AltarUi& _Other) = delete;
	AltarUi(AltarUi&& _Other) noexcept = delete;
	AltarUi& operator = (const AltarUi& _Other) = delete;
	AltarUi& operator = (AltarUi&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PreveLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Altar = nullptr;

};

