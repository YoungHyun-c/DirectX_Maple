#include "PreCompile.h"
#include "AtereEffect.h"
#include <GameEngineCore/GAMEENGINECORE.H>

AtereEffect::AtereEffect()
{
}

AtereEffect::~AtereEffect()
{
}

void AtereEffect::Start()
{
	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();

	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("AtereEffect");

	EffectUnit.ShaderResHelper.SetTexture("Tex0", Target->GetTexture(1));
	EffectUnit.ShaderResHelper.SetTexture("Tex1", Target->GetTexture(2));

	EffectUnit.ShaderResHelper.SetSampler("Tex0Sampler", "POINT");
	EffectUnit.ShaderResHelper.SetSampler("Tex1Sampler", "POINT");


}

void AtereEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	GameEngineRenderTarget::RenderTargetReset();
}