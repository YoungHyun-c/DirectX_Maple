#include"PreCompile.h"
#include "PlayMap.h"

PlayMap* PlayMap::MainMap;

PlayMap::PlayMap()
{
	MainMap = this;
}

PlayMap::~PlayMap()
{

}

void PlayMap::Update(float _DeltaTime)
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

void PlayMap::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(-30);
		Renderer->SetSprite("EntranceMap.png");

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("EntranceMap.png");

		float4 HScale = Tex->GetScale().Half();
		HScale.Y *= -1.0f;
		Renderer->Transform.SetLocalPosition(HScale);
	}
}

//GameEngineColor PlayMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
//{
//	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
//	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
//	//_Pos.Y *= -1.0f;
//
//	//std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("TestMap.png");
//
//	//return Tex->GetColor(_Pos, _DefaultColor);
//}