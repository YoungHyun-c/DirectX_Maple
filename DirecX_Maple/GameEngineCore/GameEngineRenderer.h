#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"

// ���� : GameEngineRenderer���� Order�� ������ �Ǵ� ������ �ǹ��Ѵ�.
class GameEngineRenderer : public GameEngineComponent
{
public:
	// constructer destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator = (const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator = (GameEngineRenderer&& _Other) noexcept = delete;

	void SetCameraOreder(int _Order);

protected:
	void Start();

private:
	int CameraOrder = 0;
};

