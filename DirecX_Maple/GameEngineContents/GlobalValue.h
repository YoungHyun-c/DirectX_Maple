#pragma once

#define DefaultGroundColor GameEngineColor(255, 0, 0, 255)
#define DefaultWallColor GameEngineColor(0, 0, 128, 255)

// Ό³Έν :
class GlobalValue
{
private:
	static GlobalValue MonsterValue;
public:
	static GlobalValue* GetMonsterValue()
	{
		return &MonsterValue;
	}
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

	static float4 CurMonsterPos;

	int GetMugongDefenseValue()
	{
		return MugongDefense;
	}

	void SetMugongDefenseValue(int _Value)
	{
		MugongDefense = _Value;
	}

protected:

private:
	int MonsterDefense = 10;
	int MugongDefense = 10;
};

