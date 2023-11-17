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

	Candle2 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	Candle2->CreateAnimation("CandleStickAppear", "CandleStickAppear", 0.1f, -1, -1, false);
	Candle2->CreateAnimation("CandleStickBreak", "CandleStickBreak", 0.1f, -1, -1, false);
	Candle2->Transform.SetWorldPosition({ 900.0f, -437.0f });
	Candle2->AutoSpriteSizeOn();
	Candle2->ChangeAnimation("CandleStickAppear");
	Candle2->SetEndEvent("CandleStickBreak", [&](GameEngineSpriteRenderer*)
		{
			Candle2->Off();
		});

	Candle3 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	Candle3->CreateAnimation("CandleStickAppear", "CandleStickAppear", 0.1f, -1, -1, false);
	Candle3->CreateAnimation("CandleStickBreak", "CandleStickBreak", 0.1f, -1, -1, false);
	Candle3->Transform.SetWorldPosition({ 980.0f, -415.0f });
	Candle3->AutoSpriteSizeOn();
	Candle3->ChangeAnimation("CandleStickAppear");

	Candle1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	Candle1->CreateAnimation("CandleStickAppear", "CandleStickAppear", 0.1f, -1, -1, false);
	Candle1->CreateAnimation("CandleStickBreak", "CandleStickBreak", 0.1f, -1, -1, false);
	Candle1->Transform.SetWorldPosition({810.0f, -410.0f});
	Candle1->AutoSpriteSizeOn();
	Candle1->ChangeAnimation("CandleStickAppear");

	FireFrame = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	FireFrame->CreateAnimation("CandleFireAppear", "CandleFireAppear", 0.1f, -1, -1, false);
	FireFrame->CreateAnimation("CandleFireBreak", "CandleFireBreak", 0.1f, -1, -1, false);
	FireFrame->CreateAnimation("CandleFireLoop", "CandleFireAppear", 0.1f, 7, 14, true);
	FireFrame->SetEndEvent("CandleFireAppear", [&](GameEngineSpriteRenderer*)
		{
			FireFrame->ChangeAnimation("CandleFireLoop");
		});

	FireFrame->Transform.SetWorldPosition({ 828.0f, -340.0f });
	FireFrame->AutoSpriteSizeOn();
	FireFrame->ChangeAnimation("CandleFireAppear");

	GameEngineInput::AddInputObject(this);
}

void CandleUi::Update(float _Delta)
{
	if (GameEngineInput::IsDown('5', this))
	{
		Candle1->ChangeAnimation("CandleStickAppear");
		Candle2->ChangeAnimation("CandleStickAppear");
		Candle3->ChangeAnimation("CandleStickAppear");
		FireFrame->ChangeAnimation("CandleFireAppear");
	}
	if (GameEngineInput::IsDown('6', this))
	{
		Candle1->ChangeAnimation("CandleStickBreak");
		Candle2->ChangeAnimation("CandleStickBreak");
		Candle3->ChangeAnimation("CandleStickBreak");
		FireFrame->ChangeAnimation("CandleFireBreak");
	}

}

void CandleUi::LevelStart(GameEngineLevel* _PrevLevel)
{

}