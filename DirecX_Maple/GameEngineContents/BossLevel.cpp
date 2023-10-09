#include "PreCompile.h"
#include "BossLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "JinHillaAnime.h"
#include "JinHillaEnterAnime.h"

#include "CravingMonster.h"
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
		//NewPlayer->PlayerBind();
		NewPlayer->Transform.SetWorldPosition({ 900.0f, -500.0f });
	}

	// ÁøÈú¶ó ³´º£±â
	//{
	//	JinHillaAttackAni = CreateActor<JinHillaAnime>(ContentsObjectType::BackGround);
	//}


	{
		//std::shared_ptr<JinHillaEnterAnime> EnterAni = CreateActor<JinHillaEnterAnime>(ContentsObjectType::UI);
	}


	// ¿å¸ÁÀÇ Çå½Å Craving Monster
	{
		CravingMob = CreateActor<CravingMonster>(ContentsObjectType::Monster);
		CravingMob->Transform.SetWorldPosition({ 700.0f, -750.0f });
		CravingMob->SetDebugMap("BossDebugMap.png");

		CravingMob = CreateActor<CravingMonster>(ContentsObjectType::Monster);
		CravingMob->Transform.SetWorldPosition({ 1200.0f, -750.0f });
		CravingMob->SetDebugMap("BossDebugMap.png");
	}
}

void BossLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B'))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('4'))
	{
		GameEngineCore::ChangeLevel("BossRewardLevel");
	}


	int a = 0;

	CurTime -= _Delta * 0.01;

	//if (true == JinHillaEnterAnime::EnterAnime->GetEnterAniEnd() && AniEnd == false)
	//{
	//	NewPlayer->PlayerBindEnd();
	//	AniEnd = true;
	//}

}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("BossMap.png");
	float4 HScale = Tex->GetScale().Half();
	GlobalValue::MapScale = Tex->GetScale();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);;


}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}