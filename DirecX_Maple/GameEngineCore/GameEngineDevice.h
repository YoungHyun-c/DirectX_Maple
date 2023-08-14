#pragma once

// 다이렉트X의 목적은
// 그래픽 카드를 이용해서 3D 연산을 대신 맡기는 것.
// 그래픽카드란 3D 연산을 위한 완전히 최적화된 연산장치이다.
// 픽셀 갯수만큼의 동시연산이 가능하다. ex) 1280 * 760

// 설명 :
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

	// 윈도우에서 만들었기 때문에
	// 근간인 HWND를 많이 요구한다.
	// WINDOW를 감싸는 구조로 만든다.
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

	// 그래픽카드의 메모리 관련 접근권한 인터페이스
	// EX) 이미지 정점을 만들고 지울 수 있는 권한이다.
	// 뭔가를 만들려면 디바이스
	ID3D11Device* Device = nullptr;

	// 그래픽카드의 연산(그린다)관련 점근권한 인터페이스
	// 로드된 이미지나 만들어진 정점을 화면에 그려라.
	// 뭔가를 그리려면 컨텍스트
	ID3D11DeviceContext* Context = nullptr;

	// 화면 출력 처리용 인터페이스
	IDXGISwapChain* SwapChain = nullptr;

	std::shared_ptr<class GameEngineTexture> BackBufferTexture;

	std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget;

	void RenderStart();
	void RenderEnd();

	void CreateSwapChain();

	void ResourcesInit();
};

