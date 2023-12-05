#include "PreCompile.h"
#include "GameEngineParticleRenderer.h"
#include "GameEngineStructuredBuffer.h"

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

	UpdateUnit.ShaderResHelper.SetTexture("EngineNoise", "noise_03.jpg");
	UpdateUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	UpdateUnit.ShaderResHelper.SetConstantBufferLink("ParticleUpdateInfo", ParticleUpdateInfoValue);


	ParticleUpdateInfoValue.SpawnRange = 300.0f;

	// 윈도우에 있는 함수입니다.
	// InterlockedAnd
	// 파티클정보에 대한 버퍼는 각 파티클 랜더러마다 가지고 있어야 한다고 봐서
	// New로 만들어집니다.
	std::list<std::shared_ptr<GameEngineStructuredBuffer>> Buffer
		= UpdateUnit.ShaderResHelper.SetStructedNew("ParticleinfoBuffer", StructuredBufferType::UAV_INC, Data);
	//	UpdateUnit.ShaderResHelper.SetStructedNew("ParticleShareBuffer", StructuredBufferType::UAV_INC, nullptr, sizeof(ParticleShareData), 1);

		// 

		// 랜더 유니트가 알아서 랜더링을 하는겁니다
	GameEngineRenderer::SetMesh("PointMesh");
	GameEngineRenderer::SetMaterial("ParticleRender");

	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);

	Unit->SetRenderMode(RenderMode::Instancing);
	Unit->SetInstancingCount(ParticleUpdateInfoValue.ParticleMaxCount);
	// Unit->ShaderResHelper.SetConstantBufferLink("ParticleUpdateInfo", ParticleUpdateInfoValue);

	// 기존의 채워져있는 빈 스트럭처드 버퍼 대신 컴퓨트 쉐이더의 스트럭처드 버퍼를 공유해야 한다.
	Unit->ShaderResHelper.SetStructedBufferChange("ParticleinfoRenderBuffer", Buffer.front());

}

void GameEngineParticleRenderer::Update(float _DeltaTime)
{
	RenderBaseInfoValue;

	ParticleUpdateInfoValue.ObjectWorldPos = Transform.GetWorldPosition();

	GameEngineRenderer::Update(_DeltaTime);
	// 수백의 파티클 데이터를 컴퓨트쉐이더로 계산하고
	UpdateUnit.Excute();
}

void GameEngineParticleRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	GameEngineRenderer::Render(_Camera, _Delta);
}