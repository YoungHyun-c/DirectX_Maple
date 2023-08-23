#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{

}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{

}

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	// 렌더러는 뭐든지 그릴 수 있다. 세팅만 잘 해준다면,

	// 부모쪽에서 대부분의 일은 해주고,
	GameEngineRenderer::ResSetting();

	// 내꺼 조금더 넣고,
	GameEngineRenderer::Draw();
}