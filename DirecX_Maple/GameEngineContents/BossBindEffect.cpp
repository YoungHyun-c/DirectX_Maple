#include "PreCompile.h"
#include "BossBindEffect.h"

BossBindEffect::BossBindEffect()
{

}

BossBindEffect::~BossBindEffect()
{

}

void BossBindEffect::Start()
{
	{
		if (nullptr == GameEngineSprite::Find("ScollEffect"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("FolderTexture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("ScollEffect");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}

		if (nullptr == GameEngineSprite::Find("FormerBindEffect"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("FolderTexture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("FormerBindEffect");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}

	}

	BindEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);
	BindEffect->CreateAnimation("SkillBind", "ScollMobEffect", 0.1f, -1, -1, true);
	BindEffect->CreateAnimation("SkillBindLoop", "ScollMobEffect", 0.1f, 21, 27, true);
	BindEffect->SetEndEvent("SkillBind", [&](GameEngineSpriteRenderer*)
		{
			BindEffect->ChangeAnimation("SkillBindLoop");
		});


	BindEffect->CreateAnimation("FormerBindStart", "FormerBindStart", 0.1f, -1, -1, true);
	BindEffect->CreateAnimation("FormerBindLoop", "FormerBindLoop", 0.1f, -1, -1, true);
	BindEffect->CreateAnimation("FormerBindEnd", "FormerBindEnd", 0.1f, -1, -1, true);
	BindEffect->SetEndEvent("FormerBindStart", [&](GameEngineSpriteRenderer*)
		{
			BindEffect->ChangeAnimation("FormerBindLoop");
		});

	BindEffect->SetEndEvent("FormerBindEnd", [&](GameEngineSpriteRenderer*)
		{
			BindEffect->Off();
		});


	BindEffect->ChangeAnimation("SkillBind");
	BindEffect->AutoSpriteSizeOn();
	BindEffect->Off();
}

void BossBindEffect::Update(float _Delta)
{

}

void BossBindEffect::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}