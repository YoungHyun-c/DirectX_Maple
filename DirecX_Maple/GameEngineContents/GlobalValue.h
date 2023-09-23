#pragma once

#define GroundColor GameEngineColor(255, 0, 0, 255)

// ���� :
class GlobalValue
{
public:
	// constructer destructer
	GlobalValue();
	~GlobalValue();

	// delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator = (const GlobalValue& _Other) = delete;
	GlobalValue& operator = (GlobalValue&& _Other) noexcept = delete;

	static float4 WinScale;

	static float4 MapScale;

protected:

private:

};

