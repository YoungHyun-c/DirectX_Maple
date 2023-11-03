#include "PreCompile.h"
#include "BossEntranceLevel.h"
#include "BackGroundMap.h"
#include "PracticeLevel.h"

#include "Player.h"
#include "AdeleSkill.h"
#include "SkillManager.h"

BossEntranceLevel::BossEntranceLevel()
{

}

BossEntranceLevel::~BossEntranceLevel()
{

}

void BossEntranceLevel::Start()
{

	//std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("EntranceMap.png");
	//float4 HScale = Tex->GetScale().Half();
	//GlobalValue::MapScale = Tex->GetScale();
	//HScale.Y *= -1.0f;
	//GetMainCamera()->Transform.SetLocalPosition({ HScale.X, HScale.Y, -500.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GameEngineInput::AddInputObject(this);
}

void BossEntranceLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('B', this))
	{
		Map->SwitchRenderer();
	}

	if (GameEngineInput::IsDown('3', this))
	{
		//GameEngineCore::ChangeLevel("BossLevel");
	}
}

void BossEntranceLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("EntranceMap.png"))
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

		GameEngineSprite::CreateSingle("EntranceMap.png");
		GameEngineSprite::CreateSingle("EntranceDebugMap.png");
	}

	if (nullptr == Map)
	{
		Map = CreateActor<BackGroundMap>(ContentsObjectType::BackGround);
		Map->Init("EntranceMap.png", "EntranceDebugMap.png");
	}

	if (nullptr == PlayerObject)
	{
		PlayerObject = CreateActor<Player>(ContentsObjectType::Player);
		PracticeLevel* Level = dynamic_cast<PracticeLevel*>(_PrevLevel);
		PlayerObject->SetDebugMap("EntranceDebugMap.png");
		PlayerObject->Transform.SetWorldPosition({ 100.0f, -750.0f });
	}

	if (nullptr == PlayerSkill)
	{
		PlayerSkill = CreateActor<AdeleSkill>();
	}
	if (nullptr == Skill)
	{
		Skill = CreateActor<SkillManager>();
	}


	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("EntranceMap.png");
	GlobalValue::MapScale = Tex->GetScale();
	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition(HScale);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	HScale.Z = 500.0f;
	Map->Transform.SetLocalPosition(HScale);
}

void BossEntranceLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("EntranceMap.png"))
	{
		GameEngineSprite::Release("EntranceMap.png");
		GameEngineSprite::Release("EntranceDebugMap.png");
	}

	if (nullptr != Map)
	{
		Map->Death();
		Map = nullptr;
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
}
