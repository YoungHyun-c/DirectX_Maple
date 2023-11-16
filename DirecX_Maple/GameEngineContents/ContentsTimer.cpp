#include "PreCompile.h"
#include "ContentsTimer.h"

float ContentsTimer::TimeValue = 0.0f;

ContentsTimer::ContentsTimer()
{

}

ContentsTimer::~ContentsTimer()
{

}

void ContentsTimer::Start()
{
	if (nullptr == GameEngineSprite::Find("Timerbackgrnd.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\FolderTexture\\UITexture\\Timer");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	TimeFrame.TimerBack = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	TimeFrame.TimerNum1 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	TimeFrame.TimerNum2 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	TimeFrame.TimerNum3 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	TimeFrame.TimerNum4 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);

	TimeFrame.TimerBack->AutoSpriteSizeOn();

	TimeFrame.TimerBack->SetSprite("Timerbackgrnd.png");
	TimeFrame.TimerNum1->SetSprite("TimerNumber_3.png");
	TimeFrame.TimerNum2->SetSprite("TimerNumber_0.png");
	TimeFrame.TimerNum3->SetSprite("TimerNumber_0.png");
	TimeFrame.TimerNum4->SetSprite("TimerNumber_0.png");

	TimeFrame.TimerNum1->AutoSpriteSizeOn();
	TimeFrame.TimerNum2->AutoSpriteSizeOn();
	TimeFrame.TimerNum3->AutoSpriteSizeOn();
	TimeFrame.TimerNum4->AutoSpriteSizeOn();

	TimeFrame.TimerBack->Transform.SetLocalPosition({ -10.0f, GlobalValue::WinScale.hY() -75.0f});

	TimeFrame.TimerNum1->Transform.SetLocalPosition({ -28.0f, GlobalValue::WinScale.hY() -75.0f});
	TimeFrame.TimerNum2->Transform.SetLocalPosition({ -3.0f, GlobalValue::WinScale.hY() -75.0f});
	TimeFrame.TimerNum3->Transform.SetLocalPosition({ 39.0f, GlobalValue::WinScale.hY() -75.0f});
	TimeFrame.TimerNum4->Transform.SetLocalPosition({ 64.0f, GlobalValue::WinScale.hY() -75.0f});
}

void ContentsTimer::Update(float _Delta)
{
	if (0.0f == TimeValue)
	{
		return;
	}
	else if (0.0f > TimeValue)
	{
		TimeValue = 0.0f;
	}

	TimeValue -= _Delta;
	CalculateTime();
}

void ContentsTimer::CalculateTime()
{
	int Minute = static_cast<int>(TimeValue) / 60;
	int Second = static_cast<int>(TimeValue) % 60;

	if (PrevTenMinute != Minute / 10)
	{
		PrevTenMinute = Minute / 10;
		TimeFrame.TimerNum1->SetSprite("TimerNumber_" + std::to_string(PrevTenMinute) + ".png");
	}

	if (PrevOneMinute != Minute % 10)
	{
		PrevOneMinute = Minute % 10;
		TimeFrame.TimerNum2->SetSprite("TimerNumber_" + std::to_string(PrevOneMinute) + ".png");
	}

	if (PrevTenSecond != Second / 10)
	{
		PrevTenSecond = Second / 10;
		TimeFrame.TimerNum3->SetSprite("TimerNumber_" + std::to_string(PrevTenSecond) + ".png");
	}

	TimeFrame.TimerNum4->SetSprite("TimerNumber_" + std::to_string(Second % 10) + ".png");
}

void ContentsTimer::LevelEnd(GameEngineLevel* _NextLevel)
{

}