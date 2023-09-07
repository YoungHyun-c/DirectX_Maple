#include "PreCompile.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineResources.h>

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

void BackGround::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetSprite("PracticeTest.png");

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("PracticeTest.png");
	
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	Renderer->Transform.SetLocalPosition(HScale);

}
//
//void BackGround::Init(const std::string& _FileName, const std::string& _DebugFileName)
//{
//	FileName = _FileName;
//
//	if (false == GameEngineResources::IsLoadTexture(_)
//
//}