#pragma once
#include "Player.h"
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class PlayerValue : public GameEngineActor
{
	friend Player;
private:
	static PlayerValue Value;
public:
	static PlayerValue* GetValue()
	{
		return &Value;
	}
public:
	// constructer destructer
	PlayerValue();
	~PlayerValue();

	// delete Function
	PlayerValue(const PlayerValue& _Other) = delete;
	PlayerValue(PlayerValue&& _Other) noexcept = delete;
	PlayerValue& operator = (const PlayerValue& _Other) = delete;
	PlayerValue& operator = (PlayerValue&& _Other) noexcept = delete;

	////// 플레이어 스텟관련함수
	int GetPlayerStr()
	{
		return Str;
	}
	int GetPlayerDex()
	{
		return Dex;
	}
	int GetPlayerDamPer()
	{
		return DamagePer;
	}
	int GetPlayerBossDamPer()
	{
		return BossDamagePer;
	}
	float GetPlayerDefenseIgnore()
	{
		return DefenseIgnore;
	}
	float GetPlayerCriticalDam()
	{
		return CriticalDam;
	}
	int GetPlayerAllAttack()
	{
		return AllAttack;
	}
	int GetPlayerAttackPer()
	{
		return AttackPer;
	}
	int GetPlayerProPertyIgnore()
	{
		return ProPertyIgnorePer;
	}


	void SetPlayerStr(int _Value)
	{
		Str = _Value;
	}
	void SetPlayerDex(int _Value)
	{
		Dex = _Value;
	}
	void SetPlayerDamPer(int _Value)
	{
		DamagePer = _Value;
	}
	void SetPlayerBossDamPer(int _Value)
	{
		BossDamagePer = _Value;
	}
	void SetPlayerDefenseIgnore(float _Value)
	{
		DefenseIgnore = _Value;
	}
	void SetPlayerCriticalDam(float _Value)
	{
		CriticalDam = _Value;
	}
	void SetPlayerAllAttack(int _Value)
	{
		AllAttack = _Value;
	}
	void SetPlayerAttackPer(int _Value)
	{
		AttackPer = _Value;
	}
	void SetPlayerProPertyIgnore(int _Value)
	{
		ProPertyIgnorePer = _Value;
	}

	int GetLevel()
	{
		return Level;
	}

	void SetLevel(int _Level)
	{
		Level = _Level;
	}

	void LevelUp()
	{
		++Level;
		Exp -= MaxExp;
		MaxExp = static_cast<int>(MaxExp * 1.05f);
		MaxHp = static_cast<int>(MaxHp * 1.03f);
		MaxMp = static_cast<int>(MaxMp * 1.03f);
		MainHp = MaxHp;
		MainMp = MaxMp;

		Player::GetMainPlayer()->Level_Up();
		Str += 5;
	}

	void AddLevel(int _Value)
	{
		Level += _Value;
	}

	void SetMaxExp(int _MaxExp)
	{
		MaxExp = _MaxExp;
	}

	void AddExp(int _Exp)
	{
		if (Level == MaxLevel)
		{
			return;
		}

		Exp += _Exp;

		while (Exp >= MaxExp)
		{
			LevelUp();
		}
	}

	void AddHp(int _Hp)
	{
		MainHp += _Hp;

		if (MainHp >= MaxHp)
		{
			MainHp = MaxHp;
		}
	}

	void AddMp(int _Hp)
	{
		MainMp += _Hp;

		if (MainMp >= MaxMp)
		{
			MainMp = MaxMp;
		}
	}

	void SubHp(int _Hp)
	{
		MainHp -= _Hp;

		if (MainHp <= MinHp)
		{
			MainHp = MinHp;
		}
	}

	void SubMp(int _Mp)
	{
		MainMp -= _Mp;

		if (MainMp <= MinMp)
		{
			MainMp = MinMp;
		}
	}

	int GetHp()
	{
		return MainHp;
	}

	int GetMaxHp()
	{
		return MaxHp;
	}

	int GetMp()
	{
		return MainMp;
	}

	int GetMinMp()
	{
		return MinMp;
	}

	int GetMaxMp()
	{
		return MaxMp;
	}

	int GetMaxExp()
	{
		return MaxExp;
	}

	int GetExp()
	{
		return Exp;
	}

	void UpGradeClass()
	{
		if (Grade == 5)
		{
			return;
		}

		if (Class == "HighAtere" && Level >= 260)
		{
			Class = "Maestro";
		}
	}

	int GetGrade()
	{
		return Grade;
	}

	const std::string& GetClass()
	{
		return Class;
	}

	void SetGrade(int _Grade)
	{
		Grade = _Grade;

		UpGradeClass();
	}

	void AddRedDeathCount(int _Value)
	{
		RedDeathCount += _Value;
		GreenDeathCount -= _Value;
	}

	void RedToGreen()
	{
		GreenDeathCount += RedDeathCount;
		RedDeathCount = 0;
	}

	void RedDelete()
	{
		RedDeathCount = 0;
	}

	int GetGreenDeathValue()
	{
		return GreenDeathCount;
	}

	int GetRedDeathValue()
	{
		return RedDeathCount;
	}

	bool GetDivide6Use()
	{
		return Divide6Use;
	}

	void SetDivideUse(bool _Value)
	{
		Divide6Use = _Value;
	}

protected:

private:
	std::string Class = "HighAtere";
	int Grade = 5;
	int Level = 259;
	int MaxLevel = 300;

	int MinHp = 0;
	int MainHp = 100;
	int MaxHp = 100;

	int MinMp = 0;
	int MainMp = 100;
	int MaxMp = 100;

	int Exp = 0;
	int MaxExp = 100;

// 플레이어 정보
private:
	////// 플레이어 스텟
	int Str = 40182;
	int Dex = 4354;
	int DamagePer = 74;
	int BossDamagePer = 100;
	float DefenseIgnore = 90.0f;
	float CriticalDam = 70.0f;
	int AllAttack = 5772;
	int AttackPer = 102;
	int ProPertyIgnorePer = 5;

	bool Divide6Use = false;


// 보스전
private:
	int GreenDeathCount = 5;
	int RedDeathCount = 0;


};

