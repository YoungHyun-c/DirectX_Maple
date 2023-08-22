#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVertex.h"

#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineConstantBuffer.h"

GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::Start()
{
	// 메인카메라에 들어갔다.
	SetViewCameraSelect(0);

	// 카메라를 찾아서 들어가야 한다.
	// 카메라를 찾으려면 GameEngineLevel
	// Level 부터 찾아야한다.
	// Leel 누가 들고 있지? 나를 들고 있는 Actor가 들고 있다.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 존재하지 않는데 렌더러를 넣으려고 했습니다.");
		return;
	}

	Camera->Renderers[_Order].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	ViewInfo[Camera.get()] = _Order;
}

int A = 0;

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	{
		float4x4 WorldViewProjection = Transform.GetWorldViewProjectionMatrix();

		// 인풋어셈블러1 버텍스 버퍼 세팅
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("FullRect");
		if (nullptr != VertexBuffer)
		{
			VertexBuffer->Setting();
		}


		std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Find("ColorShader_VS");
		if (nullptr != VertexShader && nullptr != VertexBuffer && nullptr == LayOut)
		{
			LayOut = std::make_shared<GameEngineInputLayOut>();
			LayOut->ResCreate(VertexBuffer, VertexShader);
		}

		std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex, 0);

		const TransformData& Data = Transform.GetConstTransformDataRef();

		Buffer->Setting();

		if (nullptr != LayOut)
		{
			LayOut->Setting();

			// 레이아웃
		}

		// 버텍스 쉐이더 세팅
		if (nullptr != VertexShader)
		{
			VertexShader->Setting();
		}

		std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("FullRect");
		if (nullptr != IndexBuffer)
		{
			IndexBuffer->Setting();
		}

		// 인덱스버퍼를 어떻게 사용할 것이냐에 대한 옵션이다.
		// 삼각형의 배열로 보고 그려라
		// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		// 선의 배열로 보고 그려라.
		// D3D11_PRIMITIVE_TOPOLOGY_LINELIST
		GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 나중에 아웃풋머저 떄문에 그렇다.
		D3D11_VIEWPORT ViewPort = {};

		// 좀 더 식이 있어야 하는데 그건 다이렉트가 알아서 한다.
		// ViewPort 만들었던거 들어감
		ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
		ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
		ViewPort.MinDepth = 0.0f;
		ViewPort.MaxDepth = 1.0f;
		ViewPort.TopLeftX = 0.0f;
		ViewPort.TopLeftY = 0.0f;

		GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);

		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
		if (nullptr != Rasterizer)
		{
			Rasterizer->Setting();
		}

		std::shared_ptr<GameEnginePixelShader> PixelShader = GameEnginePixelShader::Find("ColorShader_PS");
		if (nullptr != PixelShader)
		{
			PixelShader->Setting();
		}

		std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
		if (nullptr != BackBufferRenderTarget)
		{
			BackBufferRenderTarget->Setting();
		}

		// 다음 남은 것 (그린다)

		// 세팅된 버텍스 버퍼를 그려라.
		// 그린다 라는 버턴을 누르지는 않은 것.
		// 이게 찍는 버튼이다.
		// 그걸 다시 옵션을 줄 수 있는데.
		// 인덱스 버퍼를 사용하는 경우 호출하는 Draw함수이다.
		GameEngineCore::GetContext()->DrawIndexed(6, 0, 0);

	}
}