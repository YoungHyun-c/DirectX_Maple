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

protected:

private:

};

