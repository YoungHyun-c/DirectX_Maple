#pragma once

#define DefaultGroundColor GameEngineColor(255, 0, 0, 255)
#define DefaultWallColor GameEngineColor(0, 0, 128, 255)
#define DefaultRopeColor GameEngineColor(0, 255, 0, 255)

#include "CraneMonster.h"
#include "DropItem.h"
#include "MainUIActor.h"

// ���� :
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

	bool GetAltarValue()
	{
		return Altar;
	}

	void SetAltarValue(bool _Value)
	{
		Altar = _Value;
	}

	float GetSickleCutTime()
	{
		return SickleCut;
	}

	void SetSickleCutTime(float _Time)
	{
		SickleCut = _Time;
	}

	void SetBossDeath(bool _Value)
	{
		BossDeath = _Value;
	}

	bool GetBossDeath()
	{
		return BossDeath;
	}

	void SetBgm(const std::string& _Name, int _LoopValue = 1)
	{
		MapBgm = GameEngineSound::SoundPlay(_Name, _LoopValue);
		MapBgmName = _Name;
	}

	void CurBgmStop()
	{
		MapBgm.Stop();
	}

	std::string GetCurBgmName()
	{
		return MapBgmName;
	}

	void CurBgmPause()
	{
		MapBgm.Pause();
	}

	void CurBgmResume()
	{
		MapBgm.Resume();
		MapBgm.IsPlaying();
	}

	unsigned long long GetSumDamage()
	{
		return AllSumDamage;
	}

	void AddSumDamage(unsigned long long _Value)
	{
		AllSumDamage += _Value;
	}

	void ClearDamage()
	{
		AllSumDamage = 0;
		HitCount = 0;
	}

	void AddHitCount(int _Value)
	{
		HitCount += _Value;
	}
	
	int GetHitCount()
	{
		return HitCount;
	}

protected:

private:
	int MonsterDefense = 10;
	int MugongDefense = 10;

	int HitCount = 0;
	unsigned long long AllSumDamage = 0;

	unsigned int MonsterCount = 0;
	float DropItemCount = 0;

	bool CurQuestValue = false;
	bool QuesetClearValue = false;

// ����
	bool SickleCutValue = false;
	bool Altar = false;

	float SickleCut = 0.0f;

	bool BossDeath = false;


// BGM
	GameEngineSoundPlayer MapBgm;
	std::string MapBgmName = "";
};

