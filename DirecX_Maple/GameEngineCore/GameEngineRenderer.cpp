#include "PreCompile.h"
#include "GameEngineRenderer.h"

GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::Start()
{
	GameEngineLevel* Level = GetLevel();

	GameEngineActor* Actor = GetActor();


	// ī�޶� ã�Ƽ� ���� �Ѵ�.
	// ī�޶� ã������? GameEngineLevel
	// Level���� ã�ƾ� �ȴ�.
	// Level���� ��� ����? ���� ��� �ִ� Actor�� ��� �ִ�.
	
	// Level�� ���� �� �ۿ� ����.
}

void GameEngineRenderer::SetCameraOreder(int _Order)
{

}