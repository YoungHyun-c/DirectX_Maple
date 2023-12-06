#pragma once
#include "SkillFunction.h"

// 설명 :
class SkillValue : public SkillFunction
{
	friend SkillFunction;
private:
	static SkillValue SkillSValue;
public:
	static SkillValue* GetValue()
	{
		return &SkillSValue;
	}
	// constructer destructer
	SkillValue();
	~SkillValue();

	// delete Function
	SkillValue(const SkillValue& _Other) = delete;
	SkillValue(SkillValue&& _Other) noexcept = delete;
	SkillValue& operator = (const SkillValue& _Other) = delete;
	SkillValue& operator = (SkillValue&& _Other) noexcept = delete;

	void SetDivideSkillDam(int _Value)
	{
		DivideSKillDam = _Value;
	}

	void SetDivideFinalDam(int _Value)
	{
		DivideFinalDam = _Value;
	}

	int GetDivideSkillDam()
	{
		return DivideSKillDam;
	}

	int GetDivideFinalDam()
	{
		return DivideFinalDam;
	}

	void SetRuinSkillDam(int _Value)
	{
		RuinSkillDam = _Value;
	}

	void SetRuinFinalDam(int _Value)
	{
		RuinSkillFinalDam = _Value;
	}

	int GetRuinSkillDam()
	{
		return RuinSkillDam;
	}

	int GetRuinFinalDam()
	{
		return RuinSkillFinalDam;
	}

	void SetMaestroSkillDam(int _Value)
	{
		MaestroSkillDam = _Value;
	}

	void SetMaestroFinalDam(int _Value)
	{
		MaestroSkillFinalDam = _Value;
	}

	int GetMaestroSkillDam()
	{
		return MaestroSkillDam;
	}

	int GetMaestroFinalDam()
	{
		return MaestroSkillFinalDam;
	}

	void SetShardSkillDam(int _Value)
	{
		ShardSkillDam = _Value;
	}

	void SetShardFinalDam(int _Value)
	{
		ShardSkillFinalDam = _Value;
	}

	int GetShardSkillDam()
	{
		return ShardSkillDam;
	}

	int GetShardFinalDam()
	{
		return ShardSkillFinalDam;
	}

	void SetGedderingSkillDam(int _Value)
	{
		GedderingSkillDam = _Value;
	}
	void SetGedderingFinalDam(int _Value)
	{
		GedderingSkilFinallDam = _Value;
	}
	int GetGedderingSkillDam()
	{
		return GedderingSkillDam;
	}
	int GetGedderingFinalDam()
	{
		return GedderingSkilFinallDam;
	}


	void SetBlossomSkillDam(int _Value)
	{
		BlossomSkillDam = _Value;
	}
	void SetBlossomFinalDam(int _Value)
	{
		BlossomFSillFinalDam = _Value;
	}
	int GetBlossomSkillDam()
	{
		return BlossomSkillDam;
	}
	int GetBlossomFinalDam()
	{
		return BlossomFSillFinalDam;
	}


protected:

private:
	int DivideSKillDam = 402;
	int DivideFinalDam = 220;

	int RuinSkillDam = 550;
	int RuinSkillFinalDam = 160;

	int MaestroSkillDam = 6600; // 마스터
	int MaestroSkillFinalDam = 100;

	int ShardSkillDam = 720; // 마스터
	int ShardSkillFinalDam = 220;

	int GedderingSkillDam = 560;
	int GedderingSkilFinallDam = 220;

	int BlossomSkillDam = 650;
	int BlossomFSillFinalDam = 220;


};

