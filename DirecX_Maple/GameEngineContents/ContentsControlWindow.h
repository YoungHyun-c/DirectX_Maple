#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class Tab
{
public:
	std::string Name;
	int Index;

	virtual void Start() {}
	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) = 0;

	Tab(std::string_view _Name)
	{
		Name = _Name;
	}
};

class TestTab : public Tab
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<class GameEngineObject> SelectObject = nullptr;
	std::shared_ptr<class ContentsTimer> ContentsTime = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

	float CurTime = 0;
	float SickleCutTime = 0.0f;
	float CalCulTime = 0.0f;

public:
	TestTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};

#include "PlayerValue.h"
#include "GlobalValue.h"
class CharEditorTab : public Tab
{
public:
	std::string DefSavePath;
	std::string SavePath;
	std::string LoadPath;
	std::string InputPath;

	int HpInput = 0;

	std::shared_ptr<class PlayerValue> PlayerStat;
	std::shared_ptr<class GlobalValue> MugongStat;
	int Str = 0;
	int Dex = 0;
	int DamagePer = 0;
	int BossDamagePer = 0;
	float DefenseIgnore = 0;
	float CritialDam = 0;
	int AllAttack = 0;
	int AttackPer = 0;
	int MugongDefense = 0;

	char BackGroundName[256] = { 0, };

	void Start();
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	CharEditorTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};


class LevelChangeTab : public Tab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	LevelChangeTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};


// Ό³Έν :
class ContentsControlWindow : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	std::shared_ptr<Tab> CurTab = nullptr;
	std::vector<std::shared_ptr<Tab>> Tabs;
};

