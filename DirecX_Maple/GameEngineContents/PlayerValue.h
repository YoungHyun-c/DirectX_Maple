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
		/*MaxHp = static_cast<int>(Hp * 1.035f);
		MaxMp = static_cast<int>(Mp * 1.02f);
		Hp = MaxHp;
		Mp = MaxMp;*/

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
		Exp += _Exp;

		while (Exp >= MaxExp)
		{
			LevelUp();
		}
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

	void RedToGreen(int _Value)
	{
		GreenDeathCount += _Value;
	}

	int GetGreenDeathValue()
	{
		return GreenDeathCount;
	}

	int GetRedDeathValue()
	{
		return RedDeathCount;
	}

protected:

private:
	std::string Class = "HighAtere";
	int Grade = 5;
	int Level = 259;

	int Exp = 0;
	int MaxExp = 100;

// 플레이어 정보
private:
	////// 플레이어 스텟
	int Str = 50000;
	int Dex = 4354;
	int DamagePer = 74;
	int BossDamagePer = 100;
	float DefenseIgnore = 90.0f;
	float CriticalDam = 70.0f;
	int AllAttack = 5772;
	int AttackPer = 102;
	int ProPertyIgnorePer = 5;


// 보스전
private:
	int GreenDeathCount = 5;
	int RedDeathCount = 0;


};

