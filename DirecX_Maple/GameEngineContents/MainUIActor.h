#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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

	void LevelStart(GameEngineLevel* _PrevLevel) override;

private:
	float4 WindowHalfPos = float4::ZERO;

/////////////// Atere Gauge
	void AtereUpdate(float _Delta);
	std::shared_ptr<GameEngineSpriteRenderer> AtereGaugeBack;
	std::shared_ptr<GameEngineSpriteRenderer> AtereGauge;
	std::shared_ptr<GameEngineSpriteRenderer> AtereBar;
	std::shared_ptr<GameEngineUIRenderer> AtereAnime;
	float CurGauge = 0.0f;
	float Speed = 100.0f;
////////////// 에테르 모을시 검
	//std::shared_ptr<GameEngineSpriteRenderer> ;
	std::shared_ptr<class AtereSword> Sword1;
	std::shared_ptr<class AtereSword> Sword2;
	std::shared_ptr<class AtereSword> Sword3;

	std::shared_ptr<GameEngineUIRenderer> ExpBarUi;
	std::shared_ptr<GameEngineUIRenderer> ExpBarMin;

	std::shared_ptr<GameEngineUIRenderer> LevelUpMsgBack;
	std::shared_ptr<GameEngineUIRenderer> LevelUpFontRender;
	std::shared_ptr<GameEngineUIRenderer> LevelUpCongratuFont;
	std::string LevelText = "";

//////////// Hp, Mp, Lv
	std::shared_ptr<GameEngineUIRenderer> MainBarStatus;
	std::shared_ptr<GameEngineUIRenderer> MainLvRender;
	std::shared_ptr<GameEngineUIRenderer> MainHpBar;
	std::shared_ptr<GameEngineUIRenderer> MainMpBar;

	void PlayerLvUiRenderer();
	int MainLv = 0;
	std::shared_ptr<GameEngineUIRenderer> PlayerLvNumberRender1;
	std::shared_ptr<GameEngineUIRenderer> PlayerLvNumberRender2;
	std::shared_ptr<GameEngineUIRenderer> PlayerLvNumberRender3;

	void PlayerHpPerUiRenderer();
	void PlayerMpPerUiRenderer();
	int MainHpCal = 0;
	int CurHpCal = 0;
	int PercentFrontHp = 0;
	std::shared_ptr<GameEngineUIRenderer> PlayerHpNumberRender1;
	std::shared_ptr<GameEngineUIRenderer> PlayerHpNumberRender2;
	std::shared_ptr<GameEngineUIRenderer> PlayerHpNumberRender3;
	std::shared_ptr<GameEngineUIRenderer> PlayerHpNumberRender4; // %
	float CurHpScale = 0.0f;
	void HpUpdate(float _Delta);

	int MainMpCal = 0;
	int CurMpCal = 0;
	int PercentFrontMp = 0;
	std::shared_ptr<GameEngineUIRenderer> PlayerMpNumberRender1;
	std::shared_ptr<GameEngineUIRenderer> PlayerMpNumberRender2;
	std::shared_ptr<GameEngineUIRenderer> PlayerMpNumberRender3;
	std::shared_ptr<GameEngineUIRenderer> PlayerMpNumberRender4; // %
	void MpUpdate(float _Delta);
	float CurMpScale = 0.0f;
	float ScaleSpeed = 100.0f;

	float4 FontImageScale = { 11.0f, 11.0f };


///// QuickSlot
	std::shared_ptr<GameEngineUIRenderer> QuickSlotback;
	std::shared_ptr<GameEngineUIRenderer> QuickSlotCover;
};

