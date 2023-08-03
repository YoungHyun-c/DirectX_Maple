#pragma once
#include "GameEngineActor.h"
#include <map>
#include <list>
#include <memory>

// 카메라는 이제는 엑터의 계열이다.

// 설명 :
class GameEngineCamera : public GameEngineActor
{
	friend class GameEngineRenderer;
	friend class GameEngineActor;
	friend class GameEngineLevel;

public:
	// constructer destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator = (const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator = (GameEngineCamera&& _Other) noexcept = delete;

	void SetCameraOrder(int _Order);

protected:
	void Start() override;

private:
	int CameraOrder = 0;

	// 전과 똑같이 카메라가 렌더러를 관리한다.
	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> Renderers;
};

