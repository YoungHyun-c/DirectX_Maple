#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MainUIActor : public GameEngineActor
{
	friend class GlobalValue;
public:
	static MainUIActor* PlayerUiActor;
public:
	// constructer destructer
	MainUIActor();
	~MainUIActor();

	// delete Function
	MainUIActor(const MainUIActor& _Other) = delete;
	MainUIActor(MainUIActor&& _Other) noexcept = delete;
	MainUIActor& operator = (const MainUIActor& _Other) = delete;
	MainUIActor& operator = (MainUIActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta)override;

private:
	float4 WindowHalfPos = float4::ZERO;
	std::shared_ptr<GameEngineUIRenderer> AtereGaugeBack;
	std::shared_ptr<GameEngineUIRenderer> AtereGauge;
	std::shared_ptr<GameEngineUIRenderer> AtereAnime;

	std::shared_ptr<GameEngineUIRenderer> ExpBarUi;
	std::shared_ptr<GameEngineUIRenderer> ExpBarMin;

	std::shared_ptr<GameEngineUIRenderer> MainBarStatus;
	std::shared_ptr<GameEngineUIRenderer> MainHpBar;
	std::shared_ptr<GameEngineUIRenderer> MainMpBar;

	void PlayerHpPerUiRenderer();
	void PlayerMpPerUiRenderer();

	int MainHpCal = 0;
	int CurHpCal = 0;
	int PercentFrontHp = 0;

	std::shared_ptr<GameEngineUIRenderer> PlayerHpNumberRender1;
	std::shared_ptr<GameEngineUIRenderer> PlayerHpNumberRender2;
	std::shared_ptr<GameEngineUIRenderer> PlayerHpNumberRender3;
	std::shared_ptr<GameEngineUIRenderer> PlayerHpNumberRender4; // %


	int MainMpCal = 0;
	int CurMpCal = 0;
	int PercentFrontMp = 0;

	std::shared_ptr<GameEngineUIRenderer> PlayerMpNumberRender1;
	std::shared_ptr<GameEngineUIRenderer> PlayerMpNumberRender2;
	std::shared_ptr<GameEngineUIRenderer> PlayerMpNumberRender3;
	std::shared_ptr<GameEngineUIRenderer> PlayerMpNumberRender4; // %

	float4 FontImageScale = { 11.0f, 11.0f };
};

