#include"PreCompile.h"
#include "BackGroundMap.h"
#include "PotalManager.h"

#pragma comment(lib, "msimg32.lib")

BackGroundMap* BackGroundMap::MainMap = nullptr;

BackGroundMap::BackGroundMap()
{
	
}

BackGroundMap::~BackGroundMap()
{

}

void BackGroundMap::Update(float _DeltaTime)
{
	// 임시 코드일뿐
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

	//Potal= GetLevel()->CreateActor<PotalManager>();
	//Potal->SetLinkedMap("BossEntranceLevel");
	//Potal->Transform.SetWorldPosition({ 180.0f, -855.0f});

}

void BackGroundMap::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	FileName = _FileName;
	DebugFileName = _DebugFileName;

	GameEngineSprite::CreateSingle(FileName);
	BackTexture = GameEngineTexture::Find(FileName);
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
	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(_DebugMapName);

	return Tex->GetColor(_Pos, _DefaultColor);
}

void BackGroundMap::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainMap = this;

	if (FileName == "PracticeMap.png")
	{
		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("BossEntranceLevel");
		Potal->Transform.SetWorldPosition({ 180.0f, -855.0f });
	}

	if (FileName == "EntranceMap.png")
	{
		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("PracticeLevel");
		Potal->Transform.SetWorldPosition({ 110.0f, -750.0f });

		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("BossLevel");
		Potal->Transform.SetWorldPosition({ 785.0f, -750.0f });
	}

}