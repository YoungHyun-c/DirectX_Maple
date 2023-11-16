#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TimerFrame
{
	friend class ContentsTimer;

private:
	std::shared_ptr<GameEngineUIRenderer> TimerBack;

	std::shared_ptr<GameEngineUIRenderer> TimerNum1;
	std::shared_ptr<GameEngineUIRenderer> TimerNum2;
	std::shared_ptr<GameEngineUIRenderer> TimerNum3;
	std::shared_ptr<GameEngineUIRenderer> TimerNum4;
};

// Ό³Έν :
class ContentsTimer : public GameEngineActor
{
public:
	static float TimeValue;
public:
	// constructer destructer
	ContentsTimer();
	~ContentsTimer();

	// delete Function
	ContentsTimer(const ContentsTimer& _Other) = delete;
	ContentsTimer(ContentsTimer&& _Other) noexcept = delete;
	ContentsTimer& operator = (const ContentsTimer& _Other) = delete;
	ContentsTimer& operator = (ContentsTimer&& _Other) noexcept = delete;

	static void SetTimeValue(float _Value)
	{
		TimeValue = _Value;
	}

	void SubTimeValue(float _Value)
	{
		TimeValue -= _Value;
	}

	float static GetTimeValue()
	{
		return TimeValue;
	}

	void CalculateTime();

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	int PrevTenMinute = 0;
	int PrevOneMinute = 0;
	int PrevTenSecond = 0;

	TimerFrame TimeFrame;
};