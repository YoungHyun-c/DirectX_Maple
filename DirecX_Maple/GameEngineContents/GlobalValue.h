#pragma once

#define DefaultGroundColor GameEngineColor(255, 0, 0, 255)
#define DefaultWallColor GameEngineColor(0, 0, 128, 255)

#include "CraneMonster.h"
#include "DropItem.h"
#include "MainUIActor.h"

// Ό³Έν :
class GlobalValue
{
	friend CraneMonster;
	friend DropItem;
private:
	static GlobalValue MonsterValue;
	static GlobalValue DropValue;
public:
	static GlobalValue* GetMonsterValue()
	{
		return &MonsterValue;
	}

	static GlobalValue* GetDropValue()
	{
		return &DropValue;
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

	void AddMonsterCatchCount(int _Value)
	{
		MonsterCount += _Value;
	}

	unsigned int GetCurMonsterValue()
	{
		return MonsterCount;
	}

	void AddDropItemCount(int _Value)
	{
		if (DropItemCount >= 100)
		{
			DropItemCount = 100;
			return;
		}

		DropItemCount += _Value;
	}

	unsigned int GetDropItemValue()
	{
		return DropItemCount;
	}

protected:

private:
	int MonsterDefense = 10;
	int MugongDefense = 10;

	unsigned int MonsterCount = 0;
	unsigned int DropItemCount = 0;
};

