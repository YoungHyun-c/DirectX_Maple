#include "PreCompile.h"
#include "ContentsCore.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::Start()
{

}

void ContentsCore::Update(float _Delta)
{
	HDC DC;
	{
		// 윈도우 클리어
		DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();
		float4 WinScale = GameEngineCore::MainWindow.GetScale();
		Rectangle(DC , 0, 0, WinScale.iX(), WinScale.iY());
	}

	{
		// 물체로서의 크기 회전 위치
		static float4 Scale = { 100, 100 }; //크기
		static float4 Rotation = { 0, 0, 0 }; // 회전
		// 누구가 로컬과 월드가 있고
		// 이 로컬과 월드 기반으로 자신의 위치를 해석할 수 있다.
		static float4 Position = { 100, 100 }; // 이동

		static float Dir = 1.0f;

		Scale -= float4(100.0f, 100.0f, 100.0f) * _Delta * Dir;

		if (100.0f <= abs(Scale.X))
		{
			Dir *= -1.0f;
		}

		Rotation.Z += 360.0f * _Delta;
		Position.X += 50.0f * _Delta;

		// 로컬과 월드의 차이이다.
		// 사각형을 만들기 위해서 점을 4개 만들었다.
		// 바로 월드로 바로만든덧.
		// 로컬이 존재하지 않는다.

		// 로컬상태
		std::vector<float4> Vertex;
		Vertex.resize(4);
		Vertex[0] = { -0.5f, -0.5f };
		Vertex[1] = { 0.5f, -0.5f };
		Vertex[2] = { 0.5f, 0.5f };
		Vertex[3] = { -0.5f, 0.5f };
		//Vertex[0] = { -50.0f, -50.0f };
		//Vertex[1] = { 50.0f, -50.0f };
		//Vertex[2] = { 50.0f, 50.0f };
		//Vertex[3] = { -50.0f, 50.0f };

		std::vector<POINT> WinPoint;
		WinPoint.resize(4);
		for (size_t i = 0; i < Vertex.size(); i++)
		{
			// 위치를 더해줌으로해서 월드 상태로 이전시켰다고 한다.
			float4 WorldPoint = Vertex[i];

			// 위치 크기 회전을 적용시킬때 수학적으로 증명된
			// 절대적인 기준이 있습니다.
			// 크기 회전 위치 순서대로 적용시켜야 합니다.

			WorldPoint *= Scale;
			WorldPoint = WorldPoint.GetRotationToDegZ(Rotation.Z);
			WorldPoint += Position;
			WinPoint[i] = WorldPoint.WindowPOINT();
		}

		Polygon(DC, &WinPoint[0], Vertex.size());

		GameEngineCore::MainWindow.DoubleBuffering();

	}
}

void ContentsCore::Release()
{

}