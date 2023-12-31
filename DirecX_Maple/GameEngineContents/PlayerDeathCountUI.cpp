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

	DeathUI = new std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();
	DeathUI->reserve(5);
	for (size_t i = 1; i < DeathUI->capacity()+1; i++)
	{
		DeathCountUI = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		DeathCountUI->CreateAnimation("DeathUIwhiteLoop", "DeathUIwhiteLoop");
		DeathCountUI->CreateAnimation("DeathUIWhiteToRed", "DeathUIWhiteToRed", 0.1f, -1, -1, false);
		DeathCountUI->CreateAnimation("DeathUIwhiteBreak", "DeathUIwhiteBreak", 0.1f, -1, -1, false);
		DeathCountUI->CreateAnimation("DeathUIRedLoop", "DeathUIRedLoop");
		DeathCountUI->CreateAnimation("DeathUIRedToWhite", "DeathUIRedToWhite", 0.1f, -1, -1, false);
		DeathCountUI->CreateAnimation("DeathUIredBreak", "DeathUIredBreak", 0.1f, -1, -1, false);
		DeathCountUI->Transform.SetLocalPosition({ 290.0f - i*30.0f, GlobalValue::WinScale.hY() - 70.0f });

		DeathCountUI->AutoSpriteSizeOn();
		DeathCountUI->ChangeAnimation("DeathUIwhiteLoop");

		DeathUI->insert(DeathUI->begin(), DeathCountUI);
	}


	(*DeathUI)[0]->SetEndEvent("DeathUIWhiteToRed", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[0]->ChangeAnimation("DeathUIRedLoop");
		});

	(*DeathUI)[1]->SetEndEvent("DeathUIWhiteToRed", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[1]->ChangeAnimation("DeathUIRedLoop");
		});
	(*DeathUI)[2]->SetEndEvent("DeathUIWhiteToRed", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[2]->ChangeAnimation("DeathUIRedLoop");
		});
	(*DeathUI)[3]->SetEndEvent("DeathUIWhiteToRed", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[3]->ChangeAnimation("DeathUIRedLoop");
		});
	(*DeathUI)[4]->SetEndEvent("DeathUIWhiteToRed", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[4]->ChangeAnimation("DeathUIRedLoop");
		});

	(*DeathUI)[0]->SetEndEvent("DeathUIRedToWhite", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[0]->ChangeAnimation("DeathUIwhiteLoop");
		});

	(*DeathUI)[1]->SetEndEvent("DeathUIRedToWhite", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[1]->ChangeAnimation("DeathUIwhiteLoop");
		});
	(*DeathUI)[2]->SetEndEvent("DeathUIRedToWhite", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[2]->ChangeAnimation("DeathUIwhiteLoop");
		});
	(*DeathUI)[3]->SetEndEvent("DeathUIRedToWhite", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[3]->ChangeAnimation("DeathUIwhiteLoop");
		});
	(*DeathUI)[4]->SetEndEvent("DeathUIRedToWhite", [&](GameEngineSpriteRenderer*)
		{
			(*DeathUI)[4]->ChangeAnimation("DeathUIwhiteLoop");
		});


	GameEngineInput::AddInputObject(this);
}

void PlayerDeathCountUI::Update(float _Delta)
{
	if (GameEngineInput::IsDown('4', this))
	{
		//(*DeathUI)[0]->ChangeAnimation("DeathUIwhiteLoop");
		//(*DeathUI)[1]->ChangeAnimation("DeathUIwhiteLoop");
		//(*DeathUI)[2]->ChangeAnimation("DeathUIwhiteLoop");
		//(*DeathUI)[3]->ChangeAnimation("DeathUIwhiteLoop");
		//(*DeathUI)[4]->ChangeAnimation("DeathUIwhiteLoop");
		//DeathCountUI1->ChangeAnimation("DeathUIwhiteLoop");
		//DeathCountUI2->ChangeAnimation("DeathUIwhiteLoop");
	}
	if (GameEngineInput::IsDown('5', this))
	{
		//(*DeathUI)[0]->ChangeAnimation("DeathUIWhiteToRed");
		//(*DeathUI)[1]->ChangeAnimation("DeathUIWhiteToRed");
		//(*DeathUI)[2]->ChangeAnimation("DeathUIWhiteToRed");
		//(*DeathUI)[3]->ChangeAnimation("DeathUIWhiteToRed");
		//(*DeathUI)[4]->ChangeAnimation("DeathUIWhiteToRed");
		//DeathCountUI1->ChangeAnimation("DeathUIWhiteToRed");
		//DeathCountUI2->ChangeAnimation("DeathUIWhiteToRed");
	}
	if (GlobalValue::GetNeedGlobalValue()->GetAltarValue() == false)
	{
		//for (int i = 0; i < PlayerValue::GetValue()->GetGreenDeathValue(); i++)
		//{
		//	(*DeathUI)[i]->ChangeAnimation("DeathUIwhiteLoop");
		//}
	}

	if (PlayerValue::GetValue()->GetGreenDeathValue() == 0)
	{
		FailTime += _Delta;
		if (FailTime >= ChangeTime)
		{
			GameEngineCore::ChangeLevel("6.BossEntranceLevel");
		}
	}

	if (PlayerValue::GetValue()->GetRedDeathValue() >= 1)
	{
		if (PlayerValue::GetValue()->GetGreenDeathValue() < 0)
		{
			// ����
			return;
		}
		if (RedDeathUI != PlayerValue::GetValue()->GetRedDeathValue())
		{
			for (int j = 0; j < PlayerValue::GetValue()->GetRedDeathValue(); j++)
			{
				if (RedDeathUI >= 5)
				{
					return;
				}
				//(*DeathUI)[PlayerValue::GetValue()->GetGreenDeathValue()]->ChangeAnimation("DeathUIWhiteToRed");
				(*DeathUI)[PlayerValue::GetValue()->GetGreenDeathValue() + PlayerValue::GetValue()->GetRedDeathValue() - 1 - j]->ChangeAnimation("DeathUIWhiteToRed");
				RedDeathUI = PlayerValue::GetValue()->GetRedDeathValue();
			}
		}
	}

	if (GlobalValue::GetNeedGlobalValue()->GetAltarValue() == true)
	{
		for (int j = 0; j < PlayerValue::GetValue()->GetRedDeathValue(); j++)
		{
			if (RedDeathUI >= 5)
			{
				return;
			}
			(*DeathUI)[PlayerValue::GetValue()->GetGreenDeathValue() + PlayerValue::GetValue()->GetRedDeathValue() - 1 - j]->ChangeAnimation("DeathUIRedToWhite");
		}
		RedDeathUI = 0;
	}

	if (GlobalValue::GetNeedGlobalValue()->GetSickleCutValue() == true)
	{
		if (PlayerValue::GetValue()->GetGreenDeathValue() < 0)
		{
			return;
		}
		for (int j = 0; j < PlayerValue::GetValue()->GetRedDeathValue(); j++)
		{
			if (PlayerValue::GetValue()->GetGreenDeathValue() + 1 > 5)
			{
				return;
			}
			(*DeathUI)[PlayerValue::GetValue()->GetGreenDeathValue()+PlayerValue::GetValue()->GetRedDeathValue()-1 - j]->ChangeAnimation("DeathUIredBreak");
		}
		PlayerValue::GetValue()->RedDelete();
		RedDeathUI = PlayerValue::GetValue()->GetRedDeathValue();
	}

	/*if (GameEngineInput::IsDown('0', this))
	{
		PlayerValue::GetValue()->AddRedDeathCount(1);
	}*/
}



void PlayerDeathCountUI::LevelStart(GameEngineLevel* _PreveLevel)
{
	GreenDeathUI = PlayerValue::GetValue()->GetGreenDeathValue();
	RedDeathUI = PlayerValue::GetValue()->GetRedDeathValue();
}