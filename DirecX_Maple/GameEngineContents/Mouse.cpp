#include "PreCompile.h"
#include "Mouse.h"
#include "GlobalValue.h"

#include <GameEngineCore/GameEngineCore.h>

Mouse* Mouse::MainMouse;

Mouse::Mouse()
{

}

Mouse::~Mouse()
{

}

void Mouse::Start()
{

	GameEngineSprite::CreateSingle("Cursor.png");
	Cursor = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::Mouse);
	Cursor->SetSprite("Cursor.png");

	CursorCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Mouse);
	CursorCollision->Transform.SetLocalScale({ 5.0f, 5.0f });
	CursorCollision->Transform.SetLocalPosition({ -10.0f, 15.0f });
	CursorCollision->SetCollisionType(ColType::AABBBOX2D);

	TransformData Data = CursorCollision->Transform.GetConstTransformDataRef();
	ShowCursor(false);
	GameEngineInput::AddInputObject(this);
}

void Mouse::Update(float _Delta)
{
	PosUpdate();
	ClickUpdate();
}

void Mouse::PosUpdate()
{
	float4 WindowScale = GlobalValue::WinScale;
	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();

	MousePos = { MousePos.X - WindowScale.hX() , -MousePos.Y + WindowScale.hY(), -500.0f};
	Cursor->Transform.SetLocalPosition(MousePos);
	CursorCollision->Transform.SetLocalPosition(GetLevel()->GetMainCamera()->Transform.GetWorldPosition() + MousePos +float4{ -8, 10 });
}

void Mouse::ClickUpdate()
{
	TimeCounting();

	if (IsDoubleClick == true)
	{
		IsDoubleClick = false;
	}

	if (GameEngineInput::IsDown(VK_LBUTTON, this) == true)
	{
		if (IsClick == true)
		{
			IsDoubleClick = true;
			IsClick = false;
			ClickCount = 0.0f;
		}
		else
		{
			IsClick = true;
			ClickCount = 0.0f;
		}
	}

	if (IsClick == true)
	{
		ClickCount += TimeCount;
		if (ClickCount > 0.5f)
		{
			IsClick = false;
		}
	}

	if (IsDoubleClick == true)
	{
		int a = 0;
	}
}

void Mouse::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainMouse = this;
}