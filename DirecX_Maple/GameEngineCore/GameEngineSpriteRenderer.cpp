#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

void GameEngineFrameAnimation::Reset()
{
	CurTime = 0.0f;
	CurIndex = 0;
}

SpriteData GameEngineFrameAnimation::Update(float _DeltaTime)
{
	CurTime += _DeltaTime;

	if (Inter <= CurTime)
	{
		++CurIndex;
		CurTime -= Inter;

		if (CurIndex > End - Start)
		{
			if (true == Loop)
			{
				CurIndex = 0;
			}
			else
			{
				--CurIndex;
			}
		}
	}

	return Sprite->GetSpriteData(Index[CurIndex]);
}

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{

}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{

}

void GameEngineSpriteRenderer::Update(float _Delta)
{
	if (nullptr != CurFrameAnimations)
	{
		CurSprite = CurFrameAnimations->Update(_Delta);
	}

	if (true == IsImageSize)
	{
		float4 Scale = float4(CurSprite.GetScale());
		Scale.Z = 1.0f;
		Scale.W = 0.0f;
		Transform.SetLocalScale(Scale * AutoScaleRatio);
	}
}

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	// 렌더러는 뭐든지 그릴 수 있다. 세팅만 잘 해준다면,

	// 부모쪽에서 대부분의 일은 해주고,
	GameEngineRenderer::ResSetting();

	std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex);
	if (nullptr != Buffer)
	{
		Buffer->ChangeData(CurSprite.SpritePivot);
		Buffer->Setting(1);
	}


	// 용도에 의해서
	// 여기에서 세팅되는것이 순서상 여기가 맞다.
	//std::shared_ptr<GameEngineTexture> TestTexture = GameEngineTexture::Find("nset.png");
	//if (nullptr == TestTexture)
	//{
	//	MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
	//}
	//TestTexture->PSSetting(0);
	CurSprite.Texture->PSSetting(0);

	std::shared_ptr<GameEngineSampler> Sampler = GameEngineSampler::Find("EngineBaseSampler");
	if (nullptr == Sampler)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
	}
	Sampler->PSSetting(0);

	// 내꺼 조금더 넣고,
	GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int index /*=0*/)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}

	CurSprite = Sprite->GetSpriteData(index);
	Transform.SetLocalScale(CurSprite.GetScale() * AutoScaleRatio);
}

void GameEngineSpriteRenderer::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	unsigned int _Start /*= -1*/,
	unsigned int _End /*= -1*/,
	bool _Loop /* = true*/
)
{
	std::string SpriteName = GameEngineString::ToUpperReturn(_SpriteName);

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(_SpriteName);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만드려고 했습니다.");
	}

	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	if (true == FrameAnimations.contains(UpperName))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만드려고 했습니다.");
		return;
	}

	std::shared_ptr<GameEngineFrameAnimation> NewAnimation = std::make_shared<GameEngineFrameAnimation>();
	FrameAnimations[UpperName] = NewAnimation;
	NewAnimation->AnimationName = _AnimationName;
	NewAnimation->SpriteName = _SpriteName;
	NewAnimation->Sprite = Sprite;
	NewAnimation->Loop = _Loop;
	NewAnimation->Inter = _Inter;
	if (_Start != -1)
	{
		NewAnimation->Start = _Start;
	}
	else
	{
		NewAnimation->Start = 0;
	}
	if (_End != -1)
	{
		NewAnimation->End = _End;
	}
	else
	{
		NewAnimation->End = Sprite->GetSpriteCount() - 1;
	}

	for (unsigned int i = NewAnimation->Start; i <= NewAnimation->End; i++)
	{
		NewAnimation->Index.push_back(i);
	}

	NewAnimation->CurIndex = 0;
}

void GameEngineSpriteRenderer::ChangeAnimation(std::string_view _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	
	if (false == FrameAnimations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}

	CurFrameAnimations = FrameAnimations[UpperName];
}

void GameEngineSpriteRenderer::AutoSpriteSizeOn()
{
	IsImageSize = true;
}

void GameEngineSpriteRenderer::AutoSpriteSizeOff()
{
	IsImageSize = false;
}