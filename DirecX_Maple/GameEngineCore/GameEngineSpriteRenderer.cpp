#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

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

	// �뵵�� ���ؼ�
	// ���⿡�� ���õǴ°��� ������ ���Ⱑ �´�.
	std::shared_ptr<GameEngineTexture> TestTexture = GameEngineTexture::Find("nset.png");
	if (nullptr == TestTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ����Ϸ��� �߽��ϴ�.");
	}
	TestTexture->PSSetting(0);

	std::shared_ptr<GameEngineSampler> Sampler = GameEngineSampler::Find("EngineBaseSampler");
	if (nullptr == Sampler)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ����Ϸ��� �߽��ϴ�.");
	}
	Sampler->PSSetting(0);

	// ���� ���ݴ� �ְ�,
	GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name)
{

}