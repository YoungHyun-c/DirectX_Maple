#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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
	std::shared_ptr<class GameEngineSpriteRenderer> Boss1HpBar;
	std::shared_ptr<class GameEngineSpriteRenderer> Boss2HpBar;
	std::shared_ptr<class GameEngineSpriteRenderer> Boss3HpBar;
	std::shared_ptr<class GameEngineSpriteRenderer> Boss4HpBar;

	double MainHpCal = 0;
	double CurHpCal = 0;
	int PercentFrontHp = 0;
	int PercentBackHp = 0;
	double percentBackHpCal = 0.0f;

	float4 IconPos = { -398.0f, 365.0f };
	float4 HpBarPos = {0.0f, 370.0f};
	float4 CurHpPos = { -375.0f, 370.0f };


	std::shared_ptr<GameEngineSpriteRenderer> BossHpNumberRender1;
	std::shared_ptr<GameEngineSpriteRenderer> BossHpNumberRender2;
	std::shared_ptr<GameEngineSpriteRenderer> BossHpNumberRender3;
	std::shared_ptr<GameEngineSpriteRenderer> BossHpNumberRender4;
	std::shared_ptr<GameEngineSpriteRenderer> BossHpNumberRender5;
	std::shared_ptr<GameEngineSpriteRenderer> BossHpNumberRenderDot;

	std::shared_ptr<GameEngineSpriteRenderer> BossHpNumberBack;
};

