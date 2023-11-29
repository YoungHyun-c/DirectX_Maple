#pragma once
#include "SkillFunction.h"

// Ό³Έν :
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

	int GetMaestrokillDam()
	{
		return MaestroSkillDam;
	}

	int GetMaestroFinalDam()
	{
		return MaestroSkillFinalDam;
	}


protected:

private:
	int DivideSKillDam = 402;
	int DivideFinalDam = 220;

	int RuinSkillDam = 550;
	int RuinSkillFinalDam = 160;

	int MaestroSkillDam = 6600;
	int MaestroSkillFinalDam = 100;
};

