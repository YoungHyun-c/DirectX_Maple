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
		if (DivideLevel == 1)
		{
			DivideSKillDam = 390;
			return;
		}
		DivideSKillDam = _Value + (DivideLevel * 12);
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

	void SetDivideSpecialSkillDam(int _Value)
	{
		if (DivideLevel == 1)
		{
			DivideSpecialDam = 300;
			return;
		}
		DivideSpecialDam = _Value + ((DivideLevel) * 9);
	}

	int GetDivideSpecialSkillDam()
	{
		return DivideSpecialDam;
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

	void SetMaestroSkillDam(int _Value , int _MulValue)
	{
		if (MaestroLevel == 1)
		{
			MaestroSkillDam = _Value;
			return;
		}
		MaestroSkillDam = _Value + (MaestroLevel * _MulValue);
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


	int GetCurOrderCount()
	{
		return OrderCount;
	}

	void AddOrderCount(int _Value)
	{
		OrderCount += _Value;

		if (OrderLimitCount < OrderCount)
		{
			OrderCount = OrderLimitCount;
		}
	}
	void SubOrderCount(int _Value)
	{
		OrderCount -= _Value;

		if (0 > OrderCount)
		{
			OrderCount = 0;
		}
	}

	void SetOrderCount(int _Value)
	{
		OrderCount = _Value;
	}

	int GetLimitOrderCount()
	{
		return OrderLimitCount;
	}
	void SetOrderLimitCount(int _Value)
	{
		OrderLimitCount = _Value;
	}

	void SetDivideLevel(int _Value)
	{
		DivideLevel = _Value;

		if (DivideLevel == 1)
		{
			DivideSKillDam = 390;
			DivideSpecialDam = 300;
			return;
		}

		DivideSKillDam = 390 + ((DivideLevel) * 12);
		DivideSpecialDam = 300 + ((DivideLevel) * 9);
	}

	int GetDivideLevel()
	{
		return DivideLevel;
	}

	void SetMaestroLevel(int _Value, int _MulValue)
	{
		MaestroLevel = _Value;

		if (MaestroLevel == 1)
		{
			MaestroSkillDam = 3410;
			return;
		}

		MaestroSkillDam = 3410 + ((MaestroLevel) * _MulValue);
	}

	int GetMaestroLevel()
	{
		return MaestroLevel;
	}

protected:

private:
	int DivideLevel = 1;
	int DivideSKillDam = 390;
	//int DivideSKillDam = 410;
	int DivideSpecialDam = 300;
	int DivideFinalDam = 220;

	int MaestroLevel = 1;
	int MaestroSkillDam = 3410;
	//int MaestroSkillDam = 6600; // 마스터
	//int MaestroSkillFinalDam = 65; // 마에스트로 스킬 뎀지 추가했음
	int MaestroSkillFinalDam = 100;

	int RuinSkillDam = 550;
	int RuinSkillFinalDam = 160;

	int ShardSkillDam = 720; // 마스터
	int ShardSkillFinalDam = 185;

	int GedderingSkillDam = 560;
	int GedderingSkilFinallDam = 185;

	int BlossomSkillDam = 650;
	int BlossomFSillFinalDam = 185;


	int OrderCount = 0;
	int OrderLimitCount = 6;

};

