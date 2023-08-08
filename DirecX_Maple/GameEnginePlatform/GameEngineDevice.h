#pragma once

// ���̷�ƮX�� ������
// �׷��� ī�带 �̿��ؼ� 3D ������ ��� �ñ�� ��.
// �׷���ī��� 3D ������ ���� ������ ����ȭ�� ������ġ�̴�.
// �ȼ� ������ŭ�� ���ÿ����� �����ϴ�. ex) 1280 * 760

// ���� :
class GameEngineDevice
{
public:
	// constructer destructer
	GameEngineDevice();
	~GameEngineDevice();

	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator = (const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator = (GameEngineDevice&& _Other) noexcept = delete;

	// �����쿡�� ������� ������
	// �ٰ��� HWND�� ���� �䱸�Ѵ�.
	// WINDOW�� ���δ� ������ �����.
	void Initiallize(const class GameEngineWindow& _Window);

protected:

private:
	IDXGIAdapter* GetHighPerformanceAdapter();

	// �׷���ī���� �޸� ���� ���ٱ��� �������̽�
	// EX) �̹��� ������ ����� ���� �� �ִ� �����̴�.

	ID3D11Device* Device = nullptr;

	// �׷���ī���� ����(�׸���)���� ���ٱ��� �������̽�
	// �ε�� �̹����� ������� ������ ȭ�鿡 �׷���.

	ID3D11DeviceContext* Context = nullptr;

};

