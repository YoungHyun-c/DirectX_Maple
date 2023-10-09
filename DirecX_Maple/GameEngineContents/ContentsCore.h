#pragma once
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineCore.h>

// Ό³Έν :
class ContentsCore : public GameEngineObject
{
public:
	static std::string GetWindowTitle()
	{
		return "MapleStory";
	}

	static float4 GetStartWindowSize()
	{
		return { 1366.0f, 768.0f };
	}

	static float4 GetStartWindowPos()
	{
		return { 150.0f, 150.0f };
	}

	// constructer destructer
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator = (const ContentsCore& _Other) = delete;
	ContentsCore& operator = (ContentsCore&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:

};

