#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CandleUi : public GameEngineActor
{
public:
	// constructer destructer
	CandleUi();
	~CandleUi();

	// delete Function
	CandleUi(const CandleUi& _Other) = delete;
	CandleUi(CandleUi&& _Other) noexcept = delete;
	CandleUi& operator = (const CandleUi& _Other) = delete;
	CandleUi& operator = (CandleUi&& _Other) noexcept = delete;

	void CandleChangeAni(std::string_view _AnimationName);
	void FrameChangeAni(std::string_view _AnimationName);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PreveLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


private:
	std::shared_ptr<GameEngineSpriteRenderer> Candle1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Candle2 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Candle3 = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> FireFrame1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> FireFrame2 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> FireFrame3 = nullptr;

	bool Fire1 = false;
	bool Fire2 = false;
	bool Fire3 = false;
};

