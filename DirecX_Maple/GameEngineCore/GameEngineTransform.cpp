#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
{

}

GameEngineTransform::~GameEngineTransform()
{

}

void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;

	if (nullptr != Parent)
	{
		TransData.ParentMatirx = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.LocalWorldMatrix * TransData.ParentMatirx;
	}

	// 여기까지 하게 되면
}