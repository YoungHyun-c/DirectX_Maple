#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MainUIActor : public GameEngineActor
{
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
	std::shared_ptr<GameEngineUIRenderer> AtereGage;
	std::shared_ptr<GameEngineUIRenderer> AtereAnime;
};

