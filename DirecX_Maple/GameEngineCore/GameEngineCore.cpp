#include "PreCompile.h"
#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineGUI.h"

std::shared_ptr<GameEngineObject> GameEngineCore::CoreObject;
GameEngineTime GameEngineCore::MainTime;
GameEngineWindow GameEngineCore::MainWindow;
GameEngineDevice GameEngineCore::MainDevice;

std::shared_ptr<GameEngineLevel> GameEngineCore::CurLevel;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel;
std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::AllLevel;


GameEngineCore::GameEngineCore()
{

}

GameEngineCore::~GameEngineCore()
{

}

void GameEngineCore::Start()
{
	GameEngineGUI::Start();
	CoreObject->Start();
}

void GameEngineCore::Update()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->AllLevelEnd(NextLevel.get());
			CurLevel->AllReleaseCheck();
		}

		NextLevel->AllLevelStart(CurLevel.get());

		// NextLevel->OverCheck(CurLevel);

		// NextLevel->LevelStart(CurLevel);
		// NextLevel->ActorLevelStart();

		CurLevel = NextLevel;

		NextLevel = nullptr;
		MainTime.Reset();
	}

	MainTime.Update();
	float DeltaTime = MainTime.GetDeltaTime();

	// 디버그중 화면이 내려갔어도 시간이 많이 흘러가 있지 않도록.
	if (DeltaTime > 1.0f / 60.0f)
	{
		DeltaTime = 1.0f / 60.0f;
	}

	GameEngineSound::Update();

	CoreObject->Update(DeltaTime);

	if (true == GameEngineWindow::IsFocus())
	{
		GameEngineInput::Update(DeltaTime);
	}
	else
	{
		GameEngineInput::Reset();
	}


	CurLevel->AddLiveTime(DeltaTime);
	CurLevel->AllUpdate(DeltaTime);

	//HDC DC;
	//{
	//	DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();
	//	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	//	Rectangle(DC, 0, 0, WinScale.iX(), WinScale.iY());
	//}

	MainDevice.RenderStart();

	CurLevel->Render(DeltaTime);

	GameEngineGUI::GUIRender(CurLevel.get(), DeltaTime);

	MainDevice.RenderEnd();

	CurLevel->AllReleaseCheck();

	//GameEngineCore::MainWindow.DoubleBuffering();

	// GameEngineWindow::MainWindow.ClearBackBuffer();
	// CurLevel->ActorRender(Delta);
	// CurLevel->Render(Delta);
	// GameEngineWindow::MainWindow.DoubleBuffering();
	// 프레임의 가장 마지막에 Release가 될것이다.
	// CurLevel->ActorRelease();
}

void GameEngineCore::Release()
{
	CoreObject->Release();
	GameEngineGUI::Release();
}

void GameEngineCore::EngineProcess(HINSTANCE _Inst, const std::string& _WindowName, float4 _Pos, float4 _Size)
{
	// 릭체크 해주고
	GameEngineDebug::LeakCheck();

	// 윈도우 만들고
	MainWindow.Open(_WindowName, _Inst);
	MainWindow.SetPosAndScale(_Pos, _Size);

	// 3D 디바이스를 그 윈도우를 기반으로 만든다.
	MainDevice.Initiallize(MainWindow);
	
	// 시간이나 타임
	GameEngineWindow::MessageLoop(_Inst, Start, Update, Release);
}

void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	_Level->Start();
}