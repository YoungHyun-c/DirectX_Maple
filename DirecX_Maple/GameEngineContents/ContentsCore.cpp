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
		// ������ Ŭ����
		DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();
		float4 WinScale = GameEngineCore::MainWindow.GetScale();
		Rectangle(DC , 0, 0, WinScale.iX(), WinScale.iY());
	}

	{
		// ��ü�μ��� ũ�� ȸ�� ��ġ
		static float4 Scale = { 100, 100 }; //ũ��
		static float4 Rotation = { 0, 0, 0 }; // ȸ��
		// ������ ���ð� ���尡 �ְ�
		// �� ���ð� ���� ������� �ڽ��� ��ġ�� �ؼ��� �� �ִ�.
		static float4 Position = { 100, 100 }; // �̵�

		static float Dir = 1.0f;

		Scale -= float4(100.0f, 100.0f, 100.0f) * _Delta * Dir;

		if (100.0f <= abs(Scale.X))
		{
			Dir *= -1.0f;
		}

		Rotation.Z += 360.0f * _Delta;
		Position.X += 50.0f * _Delta;

		// ���ð� ������ �����̴�.
		// �簢���� ����� ���ؼ� ���� 4�� �������.
		// �ٷ� ����� �ٷθ��絡.
		// ������ �������� �ʴ´�.

		// ���û���
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
			// ��ġ�� �����������ؼ� ���� ���·� �������״ٰ� �Ѵ�.
			float4 WorldPoint = Vertex[i];

			// ��ġ ũ�� ȸ���� �����ų�� ���������� �����
			// �������� ������ �ֽ��ϴ�.
			// ũ�� ȸ�� ��ġ ������� ������Ѿ� �մϴ�.

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