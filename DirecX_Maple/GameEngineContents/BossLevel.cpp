#include "PreCompile.h"
#include "BossLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "JinHillaAnime.h"
#include "JinHillaEnterAnime.h"

#include "CravingMonster.h"
#include "GhostSwoo.h"
#include "GhostDamien.h"
#include "MonsterFunction.h"

BossLevel::BossLevel()
{

}

BossLevel::~BossLevel()
{

}

void BossLevel::Start()
{

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

		GameEngineSprite::CreateSingle("BossMap.png");
		GameEngineSprite::CreateSingle("BossDebugMap.png");
	}

	//std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	//float4 HScale = Tex->GetScale().Half();
	//GlobalValue::MapScale = Tex->GetScale();
	//HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("BossMap.png", "BossDebugMap.png");
	}

	{
		NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
		NewPlayer->SetDebugMap("BossDebugMap.png");
		NewPlayer->PlayerBind();
		NewPlayer->Transform.SetWorldPosition({ 900.0f, -500.0f });
	}

	// 진힐라 낫베기
	//{
	//	JinHillaAttackAni = CreateActor<JinHillaAnime>(ContentsObjectType::BackGround);
	//}


	//{
	//	std::shared_ptr<JinHillaEnterAnime> EnterAni = CreateActor<JinHillaEnterAnime>(ContentsObjectType::UI);
	//}


	// 욕망의 헌신 Craving Monster
	{
		CravingMob = CreateActor<CravingMonster>(ContentsObjectType::Monster);
		CravingMob->Transform.SetWorldPosition({ 700.0f, -770.0f, static_cast<float>(DeepBufferType::Monster) });
		CravingMob->SetDebugMap("BossDebugMap.Png");

		CravingMob = CreateActor<CravingMonster>(ContentsObjectType::Monster);
		CravingMob->Transform.SetWorldPosition({ 1200.0f, -770.0f, static_cast<float>(DeepBufferType::Monster) });
		CravingMob->SetDebugMap("BossDebugMap.Png");
	}

	// 사령 스우, 스우 구체
	//{
	//	GhostSwooMob = CreateActor<GhostSwoo>(ContentsObjectType::Monster);
	//	GhostSwooMob->Transform.SetWorldPosition({ 900.0f, -800.0f });
	//	GhostSwooMob->SetDebugMap("BossDebugMap.Png");


	//}

	//// 사령 데미안, 이펙트
	//{
	//	GhostDamienMob = CreateActor<GhostDamien>(ContentsObjectType::Monster);
	//	GhostDamienMob->Transform.SetWorldPosition({ 500.0f, -800.0f });
	//	GhostDamienMob->SetDebugMap("BossDebugMap.Png");

	//}

	GameEngineInput::AddInputObject(this);
}

void BossLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('4', this))
	{
		GameEngineCore::ChangeLevel("BossRewardLevel");
	}

	// 보스 타이머 만들어야됨 분, 초에 맞추도록
	//if (AniEnd == true)
	{
		CurTime -= _Delta * 0.01;
	}

	// 입장 컷신
	//if (true == JinHillaEnterAnime::EnterAnime->GetEnterAniEnd() && AniEnd == false)
	{
		NewPlayer->PlayerBindEnd();
		//AniEnd = true;
	}

	std::string BossTimer = "시간 타이머 : ";
	BossTimer += std::to_string(CurTime);
	BossTimer += "\n";
	OutputDebugStringA(BossTimer.c_str());

}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition(HScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}