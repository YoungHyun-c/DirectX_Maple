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
	// �������� ������ �׸� �� �ִ�. ���ø� �� ���شٸ�,

	// �θ��ʿ��� ��κ��� ���� ���ְ�,
	GameEngineRenderer::ResSetting();

	// ���� ���ݴ� �ְ�,
	GameEngineRenderer::Draw();
}