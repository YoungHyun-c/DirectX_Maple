#pragma once

#define DefaultGroundColor GameEngineColor(255, 0, 0, 255)
#define DefaultWallColor GameEngineColor(0, 0, 128, 255)

#include "CraneMonster.h"
#include "DropItem.h"
#include "MainUIActor.h"

// 설명 :
class GlobalValue
{
	friend CraneMonster;
	friend DropItem;
private:
	static GlobalValue NeedGlobalValue;
public:
	static GlobalValue* GetNeedGlobalValue()
	{
		return &NeedGlobalValue;
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

	void AddDropItemCount(float _Value)
	{
		if (DropItemCount >= 100)
		{
			DropItemCount = 100;
			return;
		}

		DropItemCount += _Value;
	}

	float GetDropItemValue()
	{
		return DropItemCount;
	}

	bool GetCurQuestValue()
	{
		return CurQuestValue;
	}

	void SetCurQuestValue(bool _Value)
	{
		CurQuestValue = _Value;
	}

	void SetClearQuestValue(bool _Value)
	{
		QuesetClearValue = _Value;
	}

	bool GetClearQuestValue()
	{
		return QuesetClearValue;
	}

	bool GetSickleCutValue()
	{
		return SickleCutValue;
	}

	void SetSickleCutValue(bool _Value)
	{
		SickleCutValue = _Value;
	}

protected:

private:
	int MonsterDefense = 10;
	int MugongDefense = 10;

	unsigned int MonsterCount = 0;
	float DropItemCount = 0;

	bool CurQuestValue = false;
	bool QuesetClearValue = false;

// 보스
	bool SickleCutValue = false;
};

