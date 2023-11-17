#include "PreCompile.h"
#include "PlayerDeathCountUI.h"

PlayerDeathCountUI::PlayerDeathCountUI()
{

}

PlayerDeathCountUI::~PlayerDeathCountUI()
{
	if (nullptr != DeathUI)
	{
		for (int i = 0; i < DeathUI->size(); i++)
		{
			(*DeathUI)[i]->Death();
			(*DeathUI)[i] = nullptr;
		}
		delete (DeathUI);
	}
}

void PlayerDeathCountUI::Start()
{
	if (nullptr == GameEngineSprite::Find("DeathUI"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaUI");
		Dir.MoveChild("DeathUI");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("JinHillahUIbackgrnd.png");

	DeathUIBack = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	DeathUIBack->SetSprite("JinHillahUIbackgrnd.png");
	DeathUIBack->AutoSpriteSizeOn();
	DeathUIBack->Transform.SetLocalPosition({ 200.0f, GlobalValue::WinScale.hY() - 75.0f });

	//DeathUI5 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	//DeathUI5->CreateAnimation("DeathUIwhiteLoop", "DeathUIwhiteLoop");
	//DeathUI5->CreateAnimation("DeathUIWhiteToRed", "DeathUIWhiteToRed");
	//DeathUI5->CreateAnimation("DeathUIwhiteBreak", "DeathUIwhiteBreak");
	//DeathUI5->CreateAnimation("DeathUIRedLoop", "DeathUIRedLoop");
	//DeathUI5->CreateAnimation("DeathUIRedToWhite", "DeathUIRedToWhite");
	//DeathUI5->CreateAnimation("DeathUIredBreak", "DeathUIredBreak");
	//DeathUI5->Transform.SetLocalPosition({260.0f, GlobalValue::WinScale.hY() - 70.0f });
	//DeathUI5->AutoSpriteSizeOn();
	//DeathUI5->ChangeAnimation("DeathUIwhiteLoop");

	//DeathUI4 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	//DeathUI4->CreateAnimation("DeathUIwhiteLoop", "DeathUIwhiteLoop");
	//DeathUI4->CreateAnimation("DeathUIWhiteToRed", "DeathUIWhiteToRed");
	//DeathUI4->CreateAnimation("DeathUIwhiteBreak", "DeathUIwhiteBreak");
	//DeathUI4->CreateAnimation("DeathUIRedLoop", "DeathUIRedLoop");
	//DeathUI4->CreateAnimation("DeathUIRedToWhite", "DeathUIRedToWhite");
	//DeathUI4->CreateAnimation("DeathUIredBreak", "DeathUIredBreak");
	//DeathUI4->Transform.SetLocalPosition({ 230.0f, GlobalValue::WinScale.hY() - 70.0f });
	//DeathUI4->AutoSpriteSizeOn();
	//DeathUI4->ChangeAnimation("DeathUIwhiteLoop");

	GameEngineInput::AddInputObject(this);


	DeathUI = new std::vector<std::shared_ptr<GameEngineUIRenderer>>();
	DeathUI->reserve(5);
	for (size_t i = 1; i < DeathUI->capacity()+1; i++)
	{
		DeathCountUI = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		DeathCountUI->CreateAnimation("DeathUIwhiteLoop", "DeathUIwhiteLoop");
		DeathCountUI->CreateAnimation("DeathUIWhiteToRed", "DeathUIWhiteToRed");
		DeathCountUI->CreateAnimation("DeathUIwhiteBreak", "DeathUIwhiteBreak");
		DeathCountUI->CreateAnimation("DeathUIRedLoop", "DeathUIRedLoop");
		DeathCountUI->CreateAnimation("DeathUIRedToWhite", "DeathUIRedToWhite");
		DeathCountUI->CreateAnimation("DeathUIredBreak", "DeathUIredBreak");
		DeathCountUI->Transform.SetLocalPosition({ 290.0f - i*30.0f, GlobalValue::WinScale.hY() - 70.0f });
		DeathCountUI->AutoSpriteSizeOn();
		DeathCountUI->ChangeAnimation("DeathUIwhiteLoop");
		DeathUI->insert(DeathUI->begin(), DeathCountUI);
	}
}

void PlayerDeathCountUI::Update(float _Delta)
{
	if (GameEngineInput::IsDown('4', this))
	{
		(*DeathUI)[0]->ChangeAnimation("DeathUIwhiteLoop");
		(*DeathUI)[1]->ChangeAnimation("DeathUIwhiteLoop");
		(*DeathUI)[2]->ChangeAnimation("DeathUIwhiteLoop");
		(*DeathUI)[3]->ChangeAnimation("DeathUIwhiteLoop");
		(*DeathUI)[4]->ChangeAnimation("DeathUIwhiteLoop");
	}
	if (GameEngineInput::IsDown('5', this))
	{
		(*DeathUI)[0]->ChangeAnimation("DeathUIWhiteToRed");
		(*DeathUI)[1]->ChangeAnimation("DeathUIWhiteToRed");
		(*DeathUI)[2]->ChangeAnimation("DeathUIWhiteToRed");
		(*DeathUI)[3]->ChangeAnimation("DeathUIWhiteToRed");
		(*DeathUI)[4]->ChangeAnimation("DeathUIWhiteToRed");
	}
	if (GameEngineInput::IsDown('6', this))
	{
		(*DeathUI)[0]->ChangeAnimation("DeathUIwhiteBreak");
		(*DeathUI)[1]->ChangeAnimation("DeathUIwhiteBreak");
		(*DeathUI)[2]->ChangeAnimation("DeathUIwhiteBreak");
		(*DeathUI)[3]->ChangeAnimation("DeathUIwhiteBreak");
		(*DeathUI)[4]->ChangeAnimation("DeathUIwhiteBreak");
	}

	if (GameEngineInput::IsDown('7', this))
	{
		(*DeathUI)[0]->ChangeAnimation("DeathUIRedLoop");
		(*DeathUI)[1]->ChangeAnimation("DeathUIRedLoop");
		(*DeathUI)[2]->ChangeAnimation("DeathUIRedLoop");
		(*DeathUI)[3]->ChangeAnimation("DeathUIRedLoop");
		(*DeathUI)[4]->ChangeAnimation("DeathUIRedLoop");
	}

	if (GameEngineInput::IsDown('8', this))
	{
		(*DeathUI)[0]->ChangeAnimation("DeathUIRedToWhite");
		(*DeathUI)[1]->ChangeAnimation("DeathUIRedToWhite");
		(*DeathUI)[2]->ChangeAnimation("DeathUIRedToWhite");
		(*DeathUI)[3]->ChangeAnimation("DeathUIRedToWhite");
		(*DeathUI)[4]->ChangeAnimation("DeathUIRedToWhite");
	}

	if (GameEngineInput::IsDown('9', this))
	{
		(*DeathUI)[0]->ChangeAnimation("DeathUIredBreak");
		(*DeathUI)[1]->ChangeAnimation("DeathUIredBreak");
		(*DeathUI)[2]->ChangeAnimation("DeathUIredBreak");
		(*DeathUI)[3]->ChangeAnimation("DeathUIredBreak");
		(*DeathUI)[4]->ChangeAnimation("DeathUIredBreak");
	}


}

void PlayerDeathCountUI::LevelStart(GameEngineLevel* _PreveLevel)
{

}