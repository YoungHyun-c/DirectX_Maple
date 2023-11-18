#include "PreCompile.h"
#include "CandleUi.h"

CandleUi::CandleUi()
{

}

CandleUi::~CandleUi()
{

}

void CandleUi::Start()
{
	if (nullptr == GameEngineSprite::Find("Candle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaUI");
		Dir.MoveChild("Candle");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	//Candle2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	//Candle2->CreateAnimation("CandleStickAppear", "CandleStickAppear", 0.1f, -1, -1, false);
	//Candle2->CreateAnimation("CandleStickBreak", "CandleStickBreak", 0.1f, -1, -1, false);
	//Candle2->Transform.SetWorldPosition({ 900.0f, -437.0f });
	//Candle2->AutoSpriteSizeOn();
	//Candle2->ChangeAnimation("CandleStickAppear");
	//Candle2->SetEndEvent("CandleStickBreak", [&](GameEngineSpriteRenderer*)
	//	{
	//		Candle2->Off();
	//	});

	//FireFrame2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	//FireFrame2->CreateAnimation("CandleFireAppear", "CandleFireAppear", 0.1f, -1, -1, false);
	//FireFrame2->CreateAnimation("CandleFireBreak", "CandleFireBreak", 0.1f, -1, -1, false);
	//FireFrame2->CreateAnimation("CandleFireLoop", "CandleFireAppear", 0.1f, 7, 14, true);
	//FireFrame2->SetEndEvent("CandleFireAppear", [&](GameEngineSpriteRenderer*)
	//	{
	//		FireFrame2->ChangeAnimation("CandleFireLoop");
	//	});

	//FireFrame2->Transform.SetWorldPosition({ 918.0f, -367.0f });
	//FireFrame2->AutoSpriteSizeOn();
	//FireFrame2->ChangeAnimation("CandleFireAppear");
	//FireFrame2->Off();

	//Candle3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	//Candle3->CreateAnimation("CandleStickAppear", "CandleStickAppear", 0.1f, -1, -1, false);
	//Candle3->CreateAnimation("CandleStickBreak", "CandleStickBreak", 0.1f, -1, -1, false);
	//Candle3->Transform.SetWorldPosition({ 980.0f, -415.0f });
	//Candle3->AutoSpriteSizeOn();
	//Candle3->ChangeAnimation("CandleStickAppear");

	//FireFrame3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	//FireFrame3->CreateAnimation("CandleFireAppear", "CandleFireAppear", 0.1f, -1, -1, false);
	//FireFrame3->CreateAnimation("CandleFireBreak", "CandleFireBreak", 0.1f, -1, -1, false);
	//FireFrame3->CreateAnimation("CandleFireLoop", "CandleFireAppear", 0.1f, 7, 14, true);
	//FireFrame3->SetEndEvent("CandleFireAppear", [&](GameEngineSpriteRenderer*)
	//	{
	//		FireFrame3->ChangeAnimation("CandleFireLoop");
	//	});

	//FireFrame3->Transform.SetWorldPosition({ 998.0f, -345.0f });
	//FireFrame3->AutoSpriteSizeOn();
	//FireFrame3->ChangeAnimation("CandleFireAppear");
	//FireFrame3->Off();

	Candle1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	Candle1->CreateAnimation("CandleStickAppear", "CandleStickAppear", 0.1f, -1, -1, false);
	Candle1->CreateAnimation("CandleStickBreak", "CandleStickBreak", 0.1f, -1, -1, false);
	Candle1->SetEndEvent("CandleStickBreak", [&](GameEngineSpriteRenderer*)
		{
			Candle1->Off();
		});
	//Candle1->Transform.SetWorldPosition({810.0f, -410.0f});
	Candle1->AutoSpriteSizeOn();
	Candle1->ChangeAnimation("CandleStickAppear");

	FireFrame1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	FireFrame1->CreateAnimation("CandleFireAppear", "CandleFireAppear", 0.1f, -1, -1, false);
	FireFrame1->CreateAnimation("CandleFireBreak", "CandleFireBreak", 0.1f, -1, -1, false);
	FireFrame1->CreateAnimation("CandleFireLoop", "CandleFireAppear", 0.1f, 7, 14, true);
	FireFrame1->SetEndEvent("CandleFireAppear", [&](GameEngineSpriteRenderer*)
		{
			FireFrame1->ChangeAnimation("CandleFireLoop");
		});

	FireFrame1->Transform.SetWorldPosition({ 18.0f, 70.0f });
	//FireFrame1->Transform.SetWorldPosition({ 828.0f, -340.0f });
	FireFrame1->AutoSpriteSizeOn();
	FireFrame1->ChangeAnimation("CandleFireAppear");
	FireFrame1->Off();

	GameEngineInput::AddInputObject(this);
}

void CandleUi::Update(float _Delta)
{
	//if (GameEngineInput::IsDown('5', this))
	//{
	//	Candle1->ChangeAnimation("CandleStickAppear");
	//	/*Candle2->ChangeAnimation("CandleStickAppear");
	//	Candle3->ChangeAnimation("CandleStickAppear");*/
	//	FireFrame1->ChangeAnimation("CandleFireAppear");
	//	/*FireFrame2->ChangeAnimation("CandleFireAppear");
	//	FireFrame3->ChangeAnimation("CandleFireAppear");*/
	//}

	//if (GlobalValue::GetNeedGlobalValue()->GetAltarValue() == true)
	//{
	//	FireFrame1->ChangeAnimation("CandleFireBreak");
	//	//FireFrame2->ChangeAnimation("CandleFireBreak");
	//	//FireFrame3->ChangeAnimation("CandleFireBreak");
	//	Fire1 = false;
	//	Fire2 = false;
	//	Fire3 = false;
	//}

	/*if (PlayerValue::GetValue()->GetRedDeathValue() >= 1 && Fire1 == false)
	{
		FireFrame1->ChangeAnimation("CandleFireAppear");
		FireFrame1->On();
		Fire1 = true;
	}*/


}

void CandleUi::FrameChangeAni(std::string_view _AnimationName)
{
	FireFrame1->ChangeAnimation(_AnimationName);
	FireFrame1->On();
}

void CandleUi::CandleChangeAni(std::string_view _AnimationName)
{
	Candle1->ChangeAnimation(_AnimationName);
}

void CandleUi::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void CandleUi::LevelEnd(GameEngineLevel* _PrevLevel)
{
	Death();
}