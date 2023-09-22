#include"PreCompile.h"
#include "BackGroundMap.h"

#pragma comment(lib, "msimg32.lib")

BackGroundMap* BackGroundMap::MainMap;

BackGroundMap::BackGroundMap()
{
	MainMap = this;
}

BackGroundMap::~BackGroundMap()
{

}

void BackGroundMap::Update(float _DeltaTime)
{
	// �ӽ� �ڵ��ϻ�
	//static float Time = 5.0f;
	//Time -= _DeltaTime;

	//if (nullptr != Renderer && Time <= 0.0f)
	//{
	//	Renderer->Death();
	//	Renderer = nullptr;
	//}
}

void BackGroundMap::Start()
{
	//{
	//	Renderer = CreateComponent<GameEngineSpriteRenderer>(-30);
	//	Renderer->SetSprite("BossMap.png");

	//	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");

	//	float4 HScale = Tex->GetScale().Half();
	//	HScale.Y *= -1.0f;
	//	Renderer->Transform.SetLocalPosition(HScale);
	//}
	//Transform.AddLocalPosition({ 683, 384 });

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGround);
	DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGround);

	Renderer->On();
	DebugRenderer->Off();
}

void BackGroundMap::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	FileName = _FileName;
	DebugFileName = _DebugFileName;

	GameEngineSprite::CreateSingle(FileName);
	std::shared_ptr<GameEngineTexture> BackTexture = GameEngineTexture::Find(FileName);
	float4 RenderScale = BackTexture->GetScale().Half();
	RenderScale.Y *= -1.0f;

	Renderer->SetSprite(_FileName);
	DebugRenderer->SetSprite(_DebugFileName);
	Transform.AddLocalPosition({ RenderScale.X, RenderScale.Y });
}

void BackGroundMap::SwitchRenderer()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else
	{
		Renderer->Off();
		DebugRenderer->On();
	}
}

GameEngineColor BackGroundMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor, std::string_view _DebugMapName)
{
	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(_DebugMapName);

	return Tex->GetColor(_Pos, _DefaultColor);
}