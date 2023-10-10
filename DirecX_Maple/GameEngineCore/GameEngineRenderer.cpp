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
#include "GameEngineBlend.h"
#include "GameEngineConstantBuffer.h"

GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

// 카메라 내부에서의 순서 변경
void GameEngineRenderer::SetRenderOrder(int _Order)
{
	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 존재하지 않는 렌더러 입니다. 카메라부터 지정해주세요");
		return;
	}

	Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	GameEngineObject::SetOrder(_Order);
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
}

// 날 바라보는 카메라 변경
void GameEngineRenderer::SetCameraOrder(int _Order)
{
	SetViewCameraSelect(_Order);
}

void GameEngineRenderer::Start()
{

	// 메인카메라에 들어갔다.
	SetCameraOrder(ECAMERAORDER::Main);

	// 카메라를 찾아서 들어가야 한다.
	// 카메라를 찾으려면 GameEngineLevel
	// Level 부터 찾아야한다.
	// Leel 누가 들고 있지? 나를 들고 있는 Actor가 들고 있다.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> FindCamera = Level->GetCamera(_Order);

	if (nullptr == FindCamera)
	{
		Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	}

	Camera = FindCamera.get();
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	
}

int A = 0;

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	for (size_t i = 0; i < Units.size(); i++)
	{
		Units[i]->ResSetting();
		Units[i]->Draw();
	}
}

std::shared_ptr<GameEngineRenderUnit> GameEngineRenderer::CreateAndFindRenderUnit(int _Index)
{
	Units.resize(_Index + 1);

	// 있으면
	if (nullptr != Units[_Index])
	{
		// 리턴
		return Units[_Index];
	}

	// 없으면 만든다.
	Units[_Index] = std::make_shared<GameEngineRenderUnit>();
	Units[_Index]->SetParentRenderer(this);
	return Units[_Index];
}

void GameEngineRenderer::SetMesh(std::string_view _Name, int _Index /*=0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMesh(_Name);
}

void GameEngineRenderer::SetMaterial(std::string_view _Name, int _Index /*=0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMaterial(_Name);

	SetMaterialEvent(_Name, _Index);
}

GameEngineShaderResHelper& GameEngineRenderer::GetShaderResHelper(int _Index /*=0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	return Unit->ShaderResHelper;
}

void GameEngineRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{

}