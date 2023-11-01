#pragma once
#include "Player.h"
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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

	////// �÷��̾� ���ݰ����Լ�
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


protected:

private:


// �÷��̾� ����
private:
	////// �÷��̾� ����
	int Str = 50000;
	int Dex = 4354;
	int DamagePer = 74;
	int BossDamagePer = 100;
	float DefenseIgnore = 90.0f;
	float CriticalDam = 70.0f;
	int AllAttack = 5772;
	int AttackPer = 102;
	int ProPertyIgnorePer = 5;
};
