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


	// 카메라를 찾아서 들어가야 한다.
	// 카메라를 찾으려면? GameEngineLevel
	// Level부터 찾아야 된다.
	// Level누가 들고 있지? 나를 들고 있는 Actor가 들고 있다.
	
	// Level을 만들 수 밖에 없다.
}

void GameEngineRenderer::SetCameraOreder(int _Order)
{

}