#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

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

	std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex);
	if (nullptr != Buffer)
	{
		Buffer->ChangeData(CurSprite.SpritePivot);
		Buffer->Setting(1);
	}


	// �뵵�� ���ؼ�
	// ���⿡�� ���õǴ°��� ������ ���Ⱑ �´�.
	//std::shared_ptr<GameEngineTexture> TestTexture = GameEngineTexture::Find("nset.png");
	//if (nullptr == TestTexture)
	//{
	//	MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ����Ϸ��� �߽��ϴ�.");
	//}
	//TestTexture->PSSetting(0);
	CurSprite.Texture->PSSetting(0);

	std::shared_ptr<GameEngineSampler> Sampler = GameEngineSampler::Find("EngineBaseSampler");
	if (nullptr == Sampler)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ����Ϸ��� �߽��ϴ�.");
	}
	Sampler->PSSetting(0);

	// ���� ���ݴ� �ְ�,
	GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int index /*=0*/)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	CurSprite = Sprite->GetSpriteData(index);
	Transform.SetLocalScale(CurSprite.GetScale());
}