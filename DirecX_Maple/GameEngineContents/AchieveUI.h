#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class AchieveUI : public GameEngineActor
{
public:
	// constructer destructer
	AchieveUI();
	~AchieveUI();

	// delete Function
	AchieveUI(const AchieveUI& _Other) = delete;
	AchieveUI(AchieveUI&& _Other) noexcept = delete;
	AchieveUI& operator = (const AchieveUI& _Other) = delete;
	AchieveUI& operator = (AchieveUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class GameEngineUIRenderer> AchieveEffect;
	std::shared_ptr<class GameEngineUIRenderer> AchieveMent;

	std::shared_ptr<class GameEngineUIRenderer> FontRender;

	double CurHp = 0;
	bool Appear = false;
};

