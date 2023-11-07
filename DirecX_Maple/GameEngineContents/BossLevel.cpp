#include "PreCompile.h"
#include "BossLevel.h"
#include "BackGroundMap.h"
#include "BossEntranceLevel.h"

#include "Player.h"
#include "JinHillaAnime.h"
#include "JinHillaEnterAnime.h"
#include "Mouse.h"
#include "MainUIActor.h"

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
	// ������ ������
	//{
	//	JinHillaAttackAni = CreateActor<JinHillaAnime>(ContentsObjectType::BackGround);
	//}


	// ���� �ƽ�
	/*{
		EnterAni = CreateActor<JinHillaEnterAnime>(ContentsObjectType::UI);
	}*/


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

	GameEngineInput::AddInputObject(this);
}

void BossLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('9', this))
	{
		GameEngineCore::ChangeLevel("9.BossRewardLevel");
	}

	// ���� Ÿ�̸� �����ߵ� ��, �ʿ� ���ߵ���
	if (AniEnd == true)
	{
		CurTime -= _Delta * 0.01f;
	}

	// ���� �ƽ�
	/*if (true == JinHillaEnterAnime::EnterAnime->GetEnterAniEnd() && AniEnd == false)
	{
		NewPlayer->PlayerEnterBindEnd();
		AniEnd = true;
		BossJin->CallRegen();
	}*/

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
	if (nullptr == GameEngineSprite::Find("BossMap.png"))
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

	if (nullptr == Map)
	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("BossMap.png", "BossDebugMap.png");
	}

	if (nullptr == GameEngineSprite::Find("Adele_Character"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Adele_Character");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("Adele_Battle_Character"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Adele_Battle_Character");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		BossEntranceLevel* Level = dynamic_cast<BossEntranceLevel*>(_PrevLevel);
		PlayerObject->SetDebugMap("BossDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 900.0f, -500.0f });
	}
	if (nullptr == GameEngineSprite::Find("Skill"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Skill");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == PlayerSkill)
	{
		PlayerSkill = CreateActor<AdeleSkill>();
	}
	if (nullptr == Skill)
	{
		Skill = CreateActor<SkillManager>();
	}

	if (nullptr == GameEngineSprite::Find("Craving"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("Craving");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("GhostDamienMob"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("GhostDamienMob");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("BossJin"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("BossJinHilla");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("JinHillaUI"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaUI");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}
	

	// ����
	if (nullptr == BossJin)
	{
		BossJin = CreateActor<JinHillaBoss>(ContentsObjectType::Monster);
		BossJin->Transform.SetWorldPosition({ 900.0f, -700.0f, static_cast<float>(DeepBufferType::Monster) });
		BossJin->SetDebugMap("BossDebugMap.Png");
		BossJin->CallRegen();
	}
	if (nullptr ==  BossJinSkill)
	{
		BossJinSkill = CreateActor<BossSkillManager>();
	}
	// �������� Ui
	if (nullptr == BossUi)
	{
		BossUi = CreateActor<BossLevelUi>(ContentsObjectType::UI);
	}

	if (nullptr == GameEngineSprite::Find("UITexture"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("UITexture");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	if (nullptr == GameEngineSprite::Find("LWGaugeUI_background.Png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("UITexture");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("LWGaugeUI_background.Png");
		GameEngineSprite::CreateSingle("LWGaugeUI.gauge.png");
	}

	if (nullptr == UIObject)
	{
		UIObject = CreateActor<MainUIActor>(ContentsObjectType::UI);
		BossEntranceLevel* Level = dynamic_cast<BossEntranceLevel*>(_PrevLevel);
	}
	if (nullptr == MouseObject)
	{
		MouseObject = CreateActor<Mouse>(ContentsObjectType::UI);
	}


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
	if (nullptr != GameEngineSprite::Find("BossMap.png"))
	{
		GameEngineSprite::Release("BossMap.png");
		GameEngineSprite::Release("BossDebugMap.png");
	}
	if (nullptr != GameEngineSprite::Find("BossJin"))
	{
		GameEngineSprite::Release("BossJin");
		GameEngineSprite::Release("JinHillaUI");
		GameEngineSprite::Release("Craving");
		GameEngineSprite::Release("GhostDamienMob");
	}
	if (nullptr != GameEngineSprite::Find("JinHillaAnime"))
	{
		GameEngineSprite::Release("JinHillaAnime");
	}

	if (nullptr != Map)
	{
		Map->Death();
		Map = nullptr;
	}

	if (nullptr != BossJin)
	{
		BossJin->Death();
		BossJin = nullptr;

		BossJinSkill->Death();
		BossJinSkill = nullptr;

	}
	if (nullptr != JinHillaAttackAni)
	{
		JinHillaAttackAni->Death();
		JinHillaAttackAni = nullptr;
	}

	if (nullptr != PlayerSkill)
	{
		PlayerSkill->Death();
		PlayerSkill = nullptr;
	}
	if (nullptr != Skill)
	{
		Skill->Death();
		Skill = nullptr;
	}
	if (nullptr != PlayerObject)
	{
		PlayerObject->Death();
		PlayerObject = nullptr;
	}
	if (nullptr != UIObject)
	{
		UIObject->Death();
		UIObject = nullptr;
	}
	if (nullptr != BossUi)
	{
		BossUi->Death();
		BossUi = nullptr;
	}
	if (nullptr != MouseObject)
	{
		MouseObject->Death();
		MouseObject = nullptr;
	}
}