#include "PreCompile.h"
#include "GameEngineParticleRenderer.h"

GameEngineParticleRenderer::GameEngineParticleRenderer()
{
}

GameEngineParticleRenderer::~GameEngineParticleRenderer()
{

}

void GameEngineParticleRenderer::Start()
{
	GameEngineRenderer::Start();

	UpdateUnit.GroupX = 128;

	std::vector<ParticleInfoData> Data;

	Data.resize(ParticleUpdateInfoValue.ParticleMaxCount);

	for (size_t i = 0; i < ParticleUpdateInfoValue.ParticleMaxCount; i++)
	{
		Data[i].CurTime = 0.0f;
		Data[i].MaxTime = ParticleUpdateInfoValue.MaxLife;
		Data[i].Dir = float4::ZERO;
		Data[i].RelativePos = float4::ZERO;
		Data[i].Speed = 100.0f;
		// 다 죽어있는 상태
		Data[i].iActive = 0;
	}

	UpdateUnit.SetComputeShader("ParticleUpdate_CS");

	// UpdateUnit.ShaderResHelper.SetConstantBufferLink("ParticleUpdateInfo", ParticleUpdateInfoValue);

	// 윈도우에 있는 함수입니다.
	// InterlockedAnd
	UpdateUnit.ShaderResHelper.SetStructedNew("ParticleinfoBuffer", StructuredBufferType::UAV_INC, Data);
	UpdateUnit.ShaderResHelper.SetStructedNew("ParticleShareBuffer", StructuredBufferType::UAV_INC, nullptr, sizeof(ParticleShareData), 1);

	// 랜더 유니트가 알아서 랜더링을 하는겁니다
	// GameEngineRenderer::SetMesh("Rect");
	// GameEngineRenderer::SetMaterial("2DTexture");
}

void GameEngineParticleRenderer::Update(float _DeltaTime)
{
	// 수백의 파티클 데이터를 컴퓨트쉐이더로 계산하고
	UpdateUnit.Excute();
}

void GameEngineParticleRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{

}