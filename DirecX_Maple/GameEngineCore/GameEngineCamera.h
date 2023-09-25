#pragma once
#include "GameEngineActor.h"
#include <map>
#include <list>
#include <memory>

enum EPROJECTIONTYPE
{
	Perspective,
	Orthographic,
};

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

	inline void SetProjectionType(EPROJECTIONTYPE _ProjectionType)
	{
		ProjectionType = _ProjectionType;
	}

	float4 GetWorldMousePos2D();

	void SetZoomValue(float _Value)
	{
		ZoomValue = _Value;
	}

	void AddZoomValue(float _Value)
	{
		ZoomValue += _Value;
	}

protected:
	void Start() override;

	void Update(float _Delta);

	void Render(float _DeltaTime);

	void AllReleaseCheck() override;

private:
	EPROJECTIONTYPE ProjectionType = EPROJECTIONTYPE::Orthographic;
	float Far = 1000.0f;
	float Near = 0.1f;
	float FOV = 60.0f;
	float ZoomValue = 0.0f;

	int CameraOrder = 0;

	// 전과 똑같이 카메라가 렌더러를 관리한다.
	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> Renderers;
};

