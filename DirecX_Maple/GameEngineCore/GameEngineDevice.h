#pragma once

// ���̷�ƮX�� ������
// �׷��� ī�带 �̿��ؼ� 3D ������ ��� �ñ�� ��.
// �׷���ī��� 3D ������ ���� ������ ����ȭ�� ������ġ�̴�.
// �ȼ� ������ŭ�� ���ÿ����� �����ϴ�. ex) 1280 * 760

// ���� :
class GameEngineDevice
{
	friend class GameEngineCore;

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

	ID3D11Device* GetDevice()
	{
		return Device;
	}

	ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

protected:

private:
	const GameEngineWindow* Window;

	IDXGIAdapter* GetHighPerformanceAdapter();

	// �׷���ī���� �޸� ���� ���ٱ��� �������̽�
	// EX) �̹��� ������ ����� ���� �� �ִ� �����̴�.
	// ������ ������� ����̽�
	ID3D11Device* Device = nullptr;

	// �׷���ī���� ����(�׸���)���� ���ٱ��� �������̽�
	// �ε�� �̹����� ������� ������ ȭ�鿡 �׷���.
	// ������ �׸����� ���ؽ�Ʈ
	ID3D11DeviceContext* Context = nullptr;

	// ȭ�� ��� ó���� �������̽�
	IDXGISwapChain* SwapChain = nullptr;

	std::shared_ptr<class GameEngineTexture> BackBufferTexture;

	std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget;

	void RenderStart();
	void RenderEnd();

	void CreateSwapChain();

	void ResourcesInit();
};

