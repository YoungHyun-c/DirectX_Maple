#include "PreCompile.h"
#include "BossFormerEffect.h"

BossFormerEffect::BossFormerEffect()
{

}

BossFormerEffect::~BossFormerEffect()
{

}

void BossFormerEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("FormerBindStart"))
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

	FormBindEffect = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::FrontSkill);

	FormBindEffect->CreateAnimation("FormerBindStart", "FormerBindStart", 0.1f, -1, -1, true);
	FormBindEffect->CreateAnimation("FormerBindLoop", "FormerBindLoop", 0.1f, -1, -1, true);
	FormBindEffect->CreateAnimation("FormerBindEnd", "FormerBindEnd", 0.1f, -1, -1, true);
	FormBindEffect->SetStartEvent("FormerBindStart", [&](GameEngineSpriteRenderer*)
		{
			FormBindEffect->On();
		});

	FormBindEffect->SetEndEvent("FormerBindStart", [&](GameEngineSpriteRenderer*)
		{
			FormBindEffect->ChangeAnimation("FormerBindLoop");
		});

	FormBindEffect->SetEndEvent("FormerBindEnd", [&](GameEngineSpriteRenderer*)
		{
			FormBindEffect->Off();
		});

	FormBindEffect->ChangeAnimation("FormerBindStart");
	FormBindEffect->AutoSpriteSizeOn();
	FormBindEffect->Off();
}

void BossFormerEffect::LevelEnd(GameEngineLevel* _PreveLevel)
{
	Death();
}