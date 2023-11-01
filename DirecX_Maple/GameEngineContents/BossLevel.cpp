#include "PreCompile.h"
#include "BossLevel.h"
#include "BackGroundMap.h"

#include "Player.h"
#include "JinHillaAnime.h"
#include "JinHillaEnterAnime.h"
#include "Mouse.h"

#include "JinHillaBoss.h"
#include "CravingMonster.h"
#include "GhostSwoo.h"
#include "GhostDamien.h"
#include "MonsterFunction.h"
#include "BossLevelUi.h"

#include "SkillManager.h"
#include "BossSkillManager.h"

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

	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("BossMap.png", "BossDebugMap.png");
	}

	{
		NewPlayer = CreateActor<Player>(ContentsObjectType::Player);
		NewPlayer->SetDebugMap("BossDebugMap.png");
		NewPlayer->PlayerEnterBind();
		NewPlayer->Transform.SetWorldPosition({ 900.0f, -500.0f });
	}
	{
		CreateActor<SkillManager>();
	}

	// ������ ������
	//{
	//	JinHillaAttackAni = CreateActor<JinHillaAnime>(ContentsObjectType::BackGround);
	//}


	// ���� �ƽ�
	{
		//std::shared_ptr<JinHillaEnterAnime> EnterAni = CreateActor<JinHillaEnterAnime>(ContentsObjectType::UI);
	}


	//{
	//	CravingMob = CreateActor<CravingMonster>(ContentsObjectType::Monster);
	//	CravingMob->Transform.SetWorldPosition({ 900.0f, -800.0f });
	//	CravingMob->SetDebugMap("BOssDebugMap.Png");
	//}

	// ��� ����, ���� ��ü
	{
		//GhostSwooMob = CreateActor<GhostSwoo>(ContentsObjectType::Monster);
		//GhostSwooMob->Transform.SetWorldPosition({ 900.0f, -800.0f });
		//GhostSwooMob->SetDebugMap("BossDebugMap.Png");


	}

	//// ��� ���̾�, ����Ʈ
	//{
		/*GhostDamienMob = CreateActor<GhostDamien>(ContentsObjectType::Monster);
		GhostDamienMob->Transform.SetWorldPosition({ 500.0f, -650.0f, static_cast<float>(DeepBufferType::Monster) });
		GhostDamienMob->SetDebugMap("BossDebugMap.Png");*/

	//}

	// ����
	{
		BossJin = CreateActor<JinHillaBoss>(ContentsObjectType::Monster);
		BossJin->Transform.SetWorldPosition({ 900.0f, -700.0f, static_cast<float>(DeepBufferType::Monster) });
		BossJin->SetDebugMap("BossDebugMap.Png");
	}

	{
		CreateActor<BossSkillManager>();
	}

	{
		MouseObject = CreateActor<Mouse>(ContentsObjectType::UI);
	}

	// �������� Ui
	{
		BossUi = CreateActor<BossLevelUi>(ContentsObjectType::UI);
	}

	GameEngineInput::AddInputObject(this);
}

void BossLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	//if (GameEngineInput::IsDown('4', this))
	//{
	//	GameEngineCore::ChangeLevel("BossRewardLevel");
	//}

	// ���� Ÿ�̸� �����ߵ� ��, �ʿ� ���ߵ���
	//if (AniEnd == true)
	{
		CurTime -= _Delta * 0.01f;
	}

	// ���� �ƽ�
	//if (true == JinHillaEnterAnime::EnterAnime->GetEnterAniEnd() && AniEnd == false)
	{
		NewPlayer->PlayerEnterBindEnd();
		//AniEnd = true;
		//BossJin->CallRegen();
	}

	std::string BossTimer = "�ð� Ÿ�̸� : ";
	BossTimer += std::to_string(CurTime);
	BossTimer += "\n";

	//OutputDebugStringA(BossTimer.c_str());
	/*long long MonsterHp = Monster::Monsters->GetMonsterHp();
	std::string CurMonsterHp = "MonsterHp : ";
	CurMonsterHp += std::to_string(MonsterHp);
	CurMonsterHp += "\n";
	OutputDebugStringA(CurMonsterHp.c_str());*/

	/*long long MainBossHp = JinHillaBoss::GetMainBoss()->GetCurBossHp();
	std::string CurMainBossHp = "MainBossHp : ";
	CurMainBossHp += std::to_string(MainBossHp);
	CurMainBossHp += "\n";
	OutputDebugStringA(CurMainBossHp.c_str());*/
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