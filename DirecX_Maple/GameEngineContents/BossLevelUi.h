#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class BossLevelUi : public GameEngineActor
{
public:
	// constructer destructer
	BossLevelUi();
	~BossLevelUi();

	// delete Function
	BossLevelUi(const BossLevelUi& _Other) = delete;
	BossLevelUi(BossLevelUi&& _Other) noexcept = delete;
	BossLevelUi& operator = (const BossLevelUi& _Other) = delete;
	BossLevelUi& operator = (BossLevelUi&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;

private:
	void UiPosUpdate(float _Delta);


	std::shared_ptr<class GameEngineSpriteRenderer> BossIcon;
	std::shared_ptr<class GameEngineSpriteRenderer> BossHpBarRender;

	std::vector<std::shared_ptr<GameEngineUIRenderer>>* BossHpUiBar = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> BossHpBar;

	double MainHpCal = 0;
	double CurHpCal = 0;
	int PercentFrontHp = 0; // float과 double은 % 연산이 안됨
	int PercentBackHp = 0;
	double percentBackHpCal = 0.0f;
	int CurPerHp = 0;

	float4 IconPos = { -398.0f, 365.0f };
	float4 HpBarPos = {0.0f, 370.0f};
	float4 CurHpPos = { -375.0f, 370.0f };


	std::shared_ptr<GameEngineUIRenderer> BossHpNumberRender1;
	std::shared_ptr<GameEngineUIRenderer> BossHpNumberRender2;
	std::shared_ptr<GameEngineUIRenderer> BossHpNumberRender3;
	std::shared_ptr<GameEngineUIRenderer> BossHpNumberRender4;
	std::shared_ptr<GameEngineUIRenderer> BossHpNumberRender5;
	std::shared_ptr<GameEngineUIRenderer> BossHpNumberRenderDot;

	std::shared_ptr<GameEngineUIRenderer> BossHpNumberBack;

	void BossHpPerUiRenderer();
	void BossHpBarUiRenderer();



};

