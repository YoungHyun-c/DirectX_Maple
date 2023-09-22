#include "PreCompile.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineBlend.h"

GameEngineMaterial::GameEngineMaterial()
{
	RasterizerPtr = GameEngineRasterizer::Find("EngineRasterizer");
	BlendStatePtr = GameEngineBlend::Find("AlphaBlend");
}

GameEngineMaterial::~GameEngineMaterial()
{
}

void GameEngineMaterial::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{ 
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}

	VertexShaderPtr->Setting();
}

void GameEngineMaterial::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgBoxAssert("존재하지 않는 레스터 라이저를 사용하려고 했습니다.");
	}
}

void GameEngineMaterial::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 픽셀 쉐이더를 세팅하려고 했습니다.");
	}

	PixelShaderPtr->Setting();
}

void GameEngineMaterial::Blend()
{
	if (nullptr == BlendStatePtr)
	{
		MsgBoxAssert("존재하지 않는 블렌드를 세팅하려고 했습니다.");
	}

	BlendStatePtr->Setting();
}

void GameEngineMaterial::SetVertexShader(const std::string_view& _Value)
{
	VertexShaderPtr = GameEngineVertexShader::Find(_Value);

	if (nullptr == VertexShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}

void GameEngineMaterial::SetRasterizer(const std::string_view& _Value)
{
	RasterizerPtr = GameEngineRasterizer::Find(_Value);

	if (nullptr == RasterizerPtr)
	{
		MsgBoxAssert("존재하지 않는 레스터 라이저를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMaterial::SetPixelShader(const std::string_view& _Value)
{
	PixelShaderPtr = GameEnginePixelShader::Find(_Value);

	if (nullptr == PixelShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 픽셀쉐이더를 세팅하려고했습니다.");
		return;
	}
}

void GameEngineMaterial::SetBlendState(const std::string_view& _Value)
{
	BlendStatePtr = GameEngineBlend::Find(_Value);
	
	if (nullptr == BlendStatePtr)
	{
		MsgBoxAssert("존재하지 않는 블렌드를 세팅하려고했습니다.");
		return;
	}
}