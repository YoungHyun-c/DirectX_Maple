#include"PreCompile.h"
#include "BackGroundMap.h"
#include "PotalManager.h"
#include "RingPotalManager.h"

#include "Player.h"

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

	// Fade in Fade Out 테스트
	{
		//DarkRenderer->GetColorData().MulColor.A -= _DeltaTime * 0.5f;
	}
}

void BackGroundMap::Start()
{
	{ 
		if (nullptr == GameEngineSprite::Find("Dark.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("BackGround");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}
			GameEngineSprite::CreateSingle("Dark.png");
		}
	}

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGround);
	DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGround);
	// 마스크기능
	//Renderer->SetMaskTexture("Mask.png");
	Renderer->On();
	DebugRenderer->Off();

	//DarkRenderer = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::Fade);
	//DarkRenderer->SetSprite("Dark.Png");
}

void BackGroundMap::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	FileName = _FileName;
	DebugFileName = _DebugFileName;

	GameEngineSprite::CreateSingle(FileName);
	BackTexture = GameEngineTexture::Find(FileName);
	BackColTexture = GameEngineTexture::Find(DebugFileName);
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
	
	//Fade in Fade Out 테스트
	{
		//DarkRenderer->GetColorData().MulColor.A = 1;
		//DarkRenderer->Transform.SetWorldPosition(0);
		//DarkRenderer->On();
	}

	if (FileName == "TownMap.png")
	{
		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("3.CrossLoadLevel");
		Potal->Transform.SetWorldPosition({ 180.0f, -1020.0f });

		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("5.PracticeLevel");
		Potal->Transform.SetWorldPosition({ 1500.0f, -1020.0f });
	}

	if (FileName == "CrossLoadMap.png")
	{
		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("2.TownLevel");
		Potal->Transform.SetWorldPosition({ 640.0f, -300.0f });


		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("3_1.HuntLevel");
		Potal->Transform.SetWorldPosition({ 630.0f, -800.0f });

		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("3_2_1.");
		Potal->Transform.SetWorldPosition({ 2100.0f, -800.0f });
	}

	if (FileName == "HuntMap.png")
	{
		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("4.FormerLevel");
		Potal->Transform.SetWorldPosition({ 180.0f, -1000.0f });


		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("3.CrossLoadLevel");
		Potal->Transform.SetWorldPosition({ 2780.0f, -1000.0f });

		//Potal = GetLevel()->CreateActor<PotalManager>();
		//Potal->SetLinkedMap("3_1.HuntLevel");
		//Potal->Transform.SetWorldPosition({ 2540.0f, -500.0f });
		//Player::GetMainPlayer()->Transform.SetWorldPosition({ 325.0f, -480.0f });

		//Potal = GetLevel()->CreateActor<PotalManager>();
		//Potal->SetLinkedMap("3_1.HuntLevel");
		//Potal->Transform.SetWorldPosition({ 325.0f, -480.0f });
		//Player::GetMainPlayer()->Transform.SetWorldPosition({ 2540.0f, -500.0f });
	}

	if (FileName == "6thMap.png")
	{
		RingPotal = GetLevel()->CreateActor<RingPotalManager>();
		RingPotal->SetLinkedMap("2.TownLevel");
		RingPotal->Transform.SetWorldPosition({ 120.0f, -950.0f });
	}

	if (FileName == "PracticeMap.png")
	{
		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("2.TownLevel");
		Potal->Transform.SetWorldPosition({ 180.0f, -850.0f });


		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("6.BossEntranceLevel");
		Potal->Transform.SetWorldPosition({ 1230.0f, -850.0f });
	}

	if (FileName == "EntranceMap.png")
	{
		Potal = GetLevel()->CreateActor<PotalManager>();
		Potal->SetLinkedMap("5.PracticeLevel");
		Potal->Transform.SetWorldPosition({ 110.0f, -740.0f });

		RingPotal = GetLevel()->CreateActor<RingPotalManager>();
		RingPotal->SetLinkedMap("7.BossEnterAniLevel");
		RingPotal->Transform.SetWorldPosition({ 785.0f, -740.0f });
	}

	if (FileName == "RewardMap.png")
	{
		RingPotal = GetLevel()->CreateActor<RingPotalManager>();
		RingPotal->SetLinkedMap("9_2.LiberationLevel");
		RingPotal->Transform.SetWorldPosition({ 95.0f, -740.0f });
	}
}